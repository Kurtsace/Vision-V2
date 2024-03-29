#include <iostream>
#include <functional>
#include "Vision.h"

using namespace cv;
using namespace std;

//Variables

//Focal length --Camera dependent
static const int focalLength = 593;

//How many Threshold objects are created
static int objects = 0;

static int msg = 0;

//Is an object detected
static bool objectCentered;


//Constructor
//Parameter is a Mat image of the original frame and the final frame, a string identifying the color
Vision::Vision(Mat *src, string c, Mat *fin) {

    if(c.empty()){

        cout << "String parameter cannot be empty!" << endl;
        initialized = false;
        return;

    }

    //Copy the src frame into source
    source = src;
    final = fin;

    //Uppercase color
    uColor = c;

    //Make text all lowercase
    transform(c.begin(), c.end(), c.begin(), ::tolower);
    color = c;

    //Initialise parameters
    initializeDefaultParameters();

    //Set the HSV and Scalar colors
    setColor();

}


//Default constructor
Vision::Vision(){

    color = "";
    initialized = false;
    setColor();
}

void Vision::sportMode(Sport event){


}

//Begins thresholding the source image, finds contours, draws contours, and draws bounding boxes
void Vision::start(){

    msg++;

    if(initialized){

        //Clone source into a separate Mat called src

        //Resize source to 480 x 360
        resize(*source, *source, Size(480, 360));

        source->copyTo(src);

        src.copyTo(*final);

        //Create a gray scale copy of source
        cvtColor(src, gray, COLOR_BGR2GRAY);

        //Apply a size 3 median blur to src
        medianBlur(src, src, 3);

        // /Convert source material into HSV
        cvtColor(src, hsv, COLOR_BGR2HSV);

        equalizeHist(gray, gray);

        //Threshold the image
        //inRange(hsv, Scalar(minHue, minSat, minVal), Scalar(maxHue, maxSat, maxVal), threshold);
        threshold(gray, binary, min, max, THRESH_BINARY);

        //--ERROR checking-- values cannot be even or 0
        if(kernelX % 2 == 0 && kernelX <= 20)
            kernelX++;
        if(kernelY % 2 == 0 && kernelY <= 20)
            kernelY++;
        if(morphSize == 0)
            morphSize++;
        if(edgeThresh % 2 == 0 && edgeThresh > 3 && edgeThresh <= 7)
            edgeThresh++;
        if(edgeThresh < 3)
            edgeThresh++;

        //Morphological opening
        morphologyEx(binary, binary, MORPH_OPEN, getStructuringElement(MORPH_CROSS, Size(5, 5)), Point(-1, -1), passes);

        //Morphological closing
        morphologyEx(binary, binary, MORPH_CLOSE, getStructuringElement(MORPH_CROSS, Size(5 ,5)), Point(-1, -1), passes);

        //Clone threshold into a separate Mat object
        Mat threshClone(binary.clone());

        //Find the contours from the thresholded image
        findContours(threshClone, cont, hierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

//        //Initialize line segment detector with standard refinement
//        lineSeg = createLineSegmentDetector(LSD_REFINE_ADV);
//
//        //Find line segments from the source frame
//        lineSeg->detect(gray, lines);
//
//        //Draw the detected line segments
//        lineSeg->drawSegments(*final, lines);

        //Find and draw the largest contours
        //largestContours(filterNoise(cont));
        roundestContour(filterNoise(cont));

        min = minHue;
        max = maxHue;

        //Draw the display
        drawHUD();

    } else if(!initialized && msg <= 1) {

        cout << "Object has not been initialized properly" << endl;
        return;
    }
}


//Kill the object --Use stop() once you are finished using the object to free memory
void Vision::stop(){

    if(initialized) {
        //Delete all windows
        destroyAllWindows();

        //Delete the pointers and free memory
        delete source;
        delete final;

        source = NULL;
        final = NULL;
    }
}


//Find the largest contours of the thresholded image
// --Minimum largest area is always 1000 to avoid detecting very small objects and noise when there is
//   no very large object detected
// --NOTE--
//      If you run into problems trying to detect small objects or far away objects set it to a smaller value or 0
void Vision::largestContours(vector<vector<Point>> inputArray){

    //Determine the largest contour area to draw
    largestArea = 500;
    double circularity;
    int largestIndex = -1;

    for (int i = 0; i < inputArray.size(); i++) {

        double area = contourArea(inputArray[i]);

        if (area > largestArea) {
            largestArea = area;
            largestIndex = i;
        }
    }

    //Make sure there is a largest contour before drawing
    if(circularity >= .3){

        draw(largestIndex, inputArray);
    }
}

void Vision::roundestContour(vector<vector<Point>> inputArray){

    double circularity;
    double roundest = .1;
    double index;

    for(int i = 0; i < inputArray.size(); i++){

        circularity = (4 * M_PI) * (contourArea(inputArray[i]) / pow(arcLength(inputArray[i], true), 2.0));

        if(circularity >= roundest){
            roundest = circularity;
            index = i;
        }
    }

    if(circularity >= .25 && contourArea(inputArray[index]) > 800)
        draw(index, inputArray);
}

//This method will draw the following:
//  Text indicating distance, shape, and color
//  Largest contour with its bounding box / circle
//  This method will only draw the contents of whats inside the contour, everything else will be black --Mask
void Vision::draw(int index, vector<vector<Point>> cont){

    Point2f points[4];
    Point2f center;
    float radius;
    Rect rect;
    RotatedRect bounding_rect;

    //Calculate polygon approximation
    approxPolyDP(Mat(cont[index]), approxPoly, arcLength(cont[index], true) * 0.015, true);

    //Compute the bounding rect, minimum enclosing circle
    rect = boundingRect(cont[index]);
    bounding_rect = minAreaRect(cont[index]);
    minEnclosingCircle(cont[index], center, radius);

    //Calculate rectangle width
    double rectWidth = rect.br().x - rect.tl().x;

    //Calculate center points of rectangle
    rectCenterX = rect.x + rect.width / 2;
    rectCenterY = rect.y + rect.height / 2;
    Point s_center;

    //Store points for the bounding rectangle
    bounding_rect.points(points);
    vector< vector<Point> > poly;
    poly.resize(1);
    for (int j = 0; j < 4; ++j)
        poly[0].push_back(points[j]);

    //Check to see what shape it is
    //Camera dependent -- Test first before using these values
    //Calculate the x and y coordinates of the object
    string coordinates = "(" + to_string(rectCenterX) + " , " + to_string(rectCenterY) + ")";

    //Draw the corresponding bounding boxes and contours with the indexed contour

    if(detectRectangle) {

        isRect = approxPoly.size() >= 4 && approxPoly.size() <= 8;

        //If its a rectangle draw the contours and a rectangular bounding with text saying the shape, color, and distance
        if (isRect) {


            detected = true;

            //Draw the contour outline and text
            drawContours(*final, filteredContour, index, color0, 2);
            line(*final, Point(rectCenterX, rectCenterY), Point(final->size().width / 2, final->size().height / 2),
                 color0, 2);
            circle(*final, Point(rectCenterX, rectCenterY), 5, WHITE, 2);
            polylines(*final, poly, true, color0, 2);

            putText(*final, color + " Rectangle", Point(rectCenterX + 10, rectCenterY),
                    FONT_HERSHEY_SIMPLEX, .5, WHITE, 2);
            putText(*final, coordinates, Point(rectCenterX + 10, rectCenterY + 20),
                    FONT_HERSHEY_SIMPLEX, .40, WHITE, 1);

            //Print out "OBJECT DETECTED"
            s_center = Point(final->size().width * 0.01, final->size().height * .05 * id);
            putText(*final, uColor + " OBJECT DETECTED", s_center, FONT_HERSHEY_SIMPLEX, .3, WHITE, 1);

            //Set current object position
            objPos = Point(rectCenterX, rectCenterY);
        }

    }

    if(detectCirc) {

        isCircle = approxPoly.size() >= 6 && approxPoly.size() <= 18;

        //If its a circle draw the contours and a circular bounding with text saying the shape, color, and distance
        if (isCircle) {

            //Set detected to true
            detected = true;

            //Draw the contour outline and text
            //drawContours(*final, filteredContour, index, color0, 2);
            line(*final, Point(rectCenterX, rectCenterY), Point(final->size().width / 2, final->size().height / 2),
                 color0, 2);
            circle(*final, Point(rectCenterX, rectCenterY), 5, WHITE, 2);
            circle(*final, center, radius, color0, 2);

            putText(*final, color + " Circle", Point(rectCenterX + 10, rectCenterY),
                    FONT_HERSHEY_SIMPLEX, .5, WHITE, 2);
            putText(*final, coordinates, Point(rectCenterX + 10, rectCenterY + 20),
                    FONT_HERSHEY_SIMPLEX, .40, WHITE, 1);

            //Print out "OBJECT DETECTED"
            s_center = Point(final->size().width * 0.01, final->size().height * .05 * id);
            putText(*final, uColor + " OBJECT DETECTED", s_center, FONT_HERSHEY_SIMPLEX, .3, WHITE, 1);

            //Set the current object position
            objPos = Point(rectCenterX, rectCenterY);

        }
    }

}



//Draw a HUD -- WILL BE USED FOR ACCURATE TRACKING OF BALL POSITION USING A VIRTUAL HUD
void Vision::drawHUD(){

    //Coordinates for the rectangle on the center of the screen

    //Size of the screen
    int screenX = source->size().width;
    int screenY = source->size().height;

    //Center of the screen
    int centerX = screenX / 2;
    int centerY = screenY / 2;

    //Top left coordinate
    int topLeftX = centerX - (centerX * .20);
    int topLeftY = centerY - (centerY * .20);

    //Bottom right coordinate
    int bottomRightX = centerX + (centerX * .20);
    int bottomRightY = centerY + (centerY * .20);

    //Final points
    Point topLeft = Point(topLeftX, topLeftY);
    Point bottomRight = Point(bottomRightX, bottomRightY);

    //Draw a white rectangle in the center of the screen
    // --Turns green if the object center is within the rectangles bounds

    if(!objectCentered)
        rectangle(*final, topLeft, bottomRight, WHITE, 2);

    if(rectCenterX <= bottomRightX && rectCenterX >= topLeftX
       && rectCenterY <= bottomRightY && rectCenterY >= topLeftY && (isRect || isCircle)) {

        objectCentered = true;
        rectangle(*final, topLeft, bottomRight, GREEN, 2);

    } else { objectCentered = false; }

    //Draw crosshairs
    line(*final, Point(centerX, 0), Point(centerX, screenY), WHITE, 1);
    line(*final, Point(0, centerY), Point(screenX, centerY), WHITE, 1);

    //If there is no object print out text on the screen
    if(!(isRect) && !(isCircle)) {

        //Detected is false
        detected = false;

        //Print out "NO OBJECT DETECTED"
        Point s_center = Point(final->size().width * 0.01, final->size().height * .05 * id);
        putText(*final, "NO " + uColor + " OBJECT DETECTED", s_center, FONT_HERSHEY_SIMPLEX, .3, WHITE, 1);

    }

}


//Sets the current color (color0) to the color specified in the string value and also sets the corresponding estimated HSV values
//--Can be manually set using setHSV()
/* Currently only supports the colors:
 *
 *      Red
 *      Blue
 *      Green
 *      Yellow
 *      White -- Buggy thresholding sometimes, use setThreshold() to correct --CAMERA DEPENDENT--
 *
 *  Unsupported colors:
 *
 *      Orange -- Basically the same as red but brighter, detect by creating red and using setThreshold()
 *      Black -- No reason to threshold and detect black unless you really wanted to, use setThreshold()
 */
void Vision::setColor() {

    //Initialize colors
    initializeColors();

    //Check the color and then set the HSV values and draw color
    if (color == "red") {

        color0 = RED;
        setMinHSV(160, 70, 60);
        setMaxHSV(255, 255, 255);

    } else if (color == "blue") {

        color0 = BLUE;
        setMinHSV(80, 70, 35);
        setMaxHSV(125, 255, 255);

    } else if (color == "green") {

        color0 = GREEN;
        setMinHSV(50, 50, 50);
        setMaxHSV(80, 255, 255);

    } else if (color == "yellow") {

        color0 = YELLOW;
        setMinHSV(30, 60, 100);
        setMaxHSV(50, 255, 255);

    } else if (color == "white") {

        color0 = WHITE;
        setMinHSV(0, 0, 255);
        setMaxHSV(0, 0, 255);

    } else if(color == "" && !initialized){

        cout << "Object was not initialized correctly and/or was initialized using the default constructor" << endl;
        return;

    } else {

        cout << color + " Is not a supported color" << endl;
        return;
    }
}


//Filters small contours that were not removed by Morphological operations
vector<vector<Point>> Vision::filterNoise(vector<vector<Point>> contour){

    vector<vector<Point>> filter;

    binary.setTo(BLACK);

    for(int i = 0; i < contour.size(); i++){

        if(contourArea(contour[i]) > 200){

            filter.push_back(contour[i]);

            drawContours(binary, contour, i, WHITE, -1, 8);
        }
    }


    //Morphological opening
    morphologyEx(binary, binary, MORPH_OPEN, getStructuringElement(MORPH_CROSS, Size(3 ,3)), Point(-1, -1), passes);

    //Morphological closing
    morphologyEx(binary, binary, MORPH_CLOSE, getStructuringElement(MORPH_CROSS, Size(3 ,3)), Point(-1, -1), passes);

    //Blur the thresholded image
    GaussianBlur(binary, binary, Size(kernelX, kernelY), sigmaX, sigmaY);

    filtered = true;

    return filter;
}

void Vision::determineShape(vector<vector<Point>> contour, int index){

    Mat shape;
    shape.create(binary.size(), binary.type());
    shape.setTo(BLACK);

    drawContours(shape, contour, index, WHITE, -1, 8);
}


//Override default Threshold presets for the current image with a manually controlled one
void Vision::setThreshold(){

    if(initialized){

        createThreshControl();
    }
}


//Create the control windows and track bars for thresholding upon calling this function
void Vision::createThreshControl(){

    //Create track bars in "Control" window
    string name = uColor + " Control";
    namedWindow(name ,CV_WINDOW_FREERATIO); //create a window called "Control"
    resizeWindow(name, 360, (360 * 3) / 4);

    //Hue, Saturation, and Value
    createTrackbar("LowH", name, &minHue, 179); //Hue (0-179)
    createTrackbar("HighH", name, &maxHue, 179);

    createTrackbar("LowS", name, &minSat, 255); //Saturation (0 - 255)
    createTrackbar("HighS", name, &maxSat, 255);

    createTrackbar("LowV", name, &minVal, 255); //Value (0-255)
    createTrackbar("HighV", name, &maxVal, 255);

    //Morphological operator

    //Create a track bar for the amount of Morphological passes to apply, max value is 10
    createTrackbar("Passes", name, &passes, 10);

    //Create a track bar for the size of the MORPH_SHAPE, max value is 25
    createTrackbar("Shape Size", name, &morphSize, 25);


    if(initialized) {
    }
}


//Override for the default values of the Gaussian blur, size of the Morph shape, and also the Morphological passes
void Vision::setBlur(){

    if(initialized) {
        //Create a window of the color name + blur
        namedWindow(uColor + "Blur", CV_WINDOW_AUTOSIZE);

        //Create a track bar for kernel X and Y, max value is 20 --Value cannot be even
        createTrackbar("Kernel X", uColor + "Blur", &kernelX, 20);
        createTrackbar("Kernel Y", uColor + "Blur", &kernelY, 20);

        //Create a track bar for sigma X and Y, max value is 10
        createTrackbar("Sigma X", uColor + "Blur", &sigmaX, 20);
        createTrackbar("Sigma Y", uColor + "Blur", &sigmaY, 20);
    }
}


//--NOTE FOR HSV VALUES--
/*
 *  HSV VALUES ARE CAMERA DEPENDENT. CHECK TO SEE WHAT THE DEFAULT HSV VALUES ARE SET TO IN setColor()
 *  BEFORE RUNNING THE PROGRAM.
 *
 *  IT IS RECOMMENDED TO SET YOUR OWN HSV VALUES EITHER THROUGH setMinHSV(), setMaxHSV(), OR THROUGH
 *  setThreshold().
 */

//Override for minimum HSV values if you do not want to use a track bar or if you know what your HSV values will be ahead of time
void Vision::setMinHSV(int hue, int sat, int val){

    minHue = hue;
    minSat = sat;
    minVal = val;
}


//Override for maximum HSV values
void Vision::setMaxHSV(int hue, int sat, int val) {

    maxHue = hue;
    maxSat = sat;
    maxVal = val;
}

void Vision::setSingleThreshold() {

    imshow("Binary", binary);

    createTrackbar("min", "Binary", &minHue, 255);
    createTrackbar("max", "Binary", &maxHue, 255);
}


//Initialize all the color values, HSV values, Morphological values, and blur values
void Vision::initializeColors(){

    //Set initial blur values
    kernelX = 3;
    kernelY = 3;
    sigmaX = 1;
    sigmaY = 1;

    //Morphological values
    passes = 2;
    morphSize = 5;

    //Initialize Scalar values
    //B, G, R
    RED = Scalar(0, 0, 255);
    GREEN = Scalar(0, 255, 0);
    BLUE = Scalar(255, 0 ,0);
    WHITE = Scalar(255, 255, 255);
    YELLOW = Scalar(0, 215, 255);
    BLACK = Scalar(0, 0, 0);

    //Set initial HSV values
    setMaxHSV(255, 255, 255);
    setMinHSV(0, 0, 0);
}

//Initialize default parameters
void Vision::initializeDefaultParameters(){

    //Set initialized to true
    initialized = true;

    //Increment objects
    objects++;

    //Add an object id
    id = objects;

    //Shape detect
    detectRectangle = false;
    detectCirc = false;

    //Set initialized to true
    initialized = true;

    //Increment objects
    objects++;

    //Add an object id
    id = objects;

    //Set Canny initial parameters
    ratio = 3;
    lowThresh = 100;
    edgeThresh = 3;

    //Threshold values;
    max = 255;
    min = 210;

    //Set filtered to false initially
    filtered = false;
}

void Vision::detectRect(bool condition){

    detectRectangle = condition;
}

void Vision::detectCircle(bool condition) {

    detectCirc = condition;
}

//Returns a Point containing the position of the ball --CENTER POINT OF THE BALL
Point Vision::getPos(){

    return objPos;
}

