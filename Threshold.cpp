#include <iostream>
#include "Threshold.h"

using namespace cv;
using namespace std;

//Variables

//Focal length --Camera dependent
static const int focalLength = 593;

//How many Threshold objects are created
static int objects = 0;

//Constructor
//Parameter is a Mat image of the original frame and the final frame, a string identifying the color
Threshold::Threshold(Mat *src, string c, Mat *fin) {

    //Copy the src frame into source
    source = src;
    final = fin;

    final->create(src->size(), src->type());

    //Make text all lowercase
    transform(c.begin(), c.end(), c.begin(), ::tolower);
    color = c;

    //Set initialized to true
    initialized = true;

    //Increment objects
    objects++;

    //Set the HSV and Scalar colors
    setColor();
}

//Default constructor
Threshold::Threshold(){

    color = "";
    initialized = false;
    setColor();
}

//Begins thresholding the source image, finds contours, draws contours, and draws bounding boxes
void Threshold::start(){

    if(initialized){

        //Clone source into a separate Mat called src
        Mat src(source->clone());

        //Apply a size 5 median blur to the source image
        medianBlur(src, src, 5);

        //Convert source material into HSV
        cvtColor(src, hsv, COLOR_BGR2HSV);

        //Threshold the image
        inRange(hsv, Scalar(minHue, minSat, minVal), Scalar(maxHue, maxSat, maxVal), threshold);

        //--ERROR checking-- values cannot be even or 0
        if(kernelX % 2 == 0 && kernelX <= 20)
            kernelX++;
        if(kernelY % 2 == 0 && kernelY <= 20)
            kernelY++;
        if(morphSize == 0)
            morphSize++;

        //Apply a slight Gaussian blur of default size 3x3 with a 0x0 sigma to the thresholded image
        //Values of kernels X and Y & sigma X and Y, can be changed manually using setBlur() --passes value can also be changed
        GaussianBlur(threshold, threshold, Size(kernelX, kernelY), sigmaX, sigmaY);

        //Morphological opening
        morphologyEx(threshold, threshold, MORPH_OPEN, getStructuringElement(MORPH_CROSS, Size(3, 3)), Point(-1, -1), passes);

        //Morphological closing
        morphologyEx(threshold, threshold, MORPH_CLOSE, getStructuringElement(MORPH_CROSS, Size(3 ,3)), Point(-1, -1), passes);

        //Create a selective threshold
        selectiveThresh.create(source->size(), source->type());
        //selectiveThresh.setTo(BLACK);

        //Blur the selective threshold for smoother ROI (Region of Interest)
        GaussianBlur(selectiveThresh, selectiveThresh, Size(9, 9), 3, 3);

        //Copy selectiveThresh into final
        selectiveThresh.copyTo(*final);

        //Clone threshold into a separate Mat object
        Mat threshClone(threshold.clone());

        //Find the contours from the thresholded image
        findContours(threshClone, cont, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        //Find and draw the largest contours
        largestContours();
    }
}

//Kill the object --Use stop() once you are finished using the object to free memory
void Threshold::stop(){

    //Delete all windows
    destroyAllWindows();

    //Delete the pointers and free memory
    delete source;
    delete final;

    source = NULL;
    final = NULL;
}

//This method will draw the following:
//  Text indicating distance, shape, and color
//  Largest contour with its bounding box / circle
//  This method will only draw the contents of whats inside the contour, everything else will be black
void Threshold::draw(int index){

    Point2f points[4];
    Point2f center;
    float radius;
    Rect rect;
    RotatedRect bounding_rect;

    //Calculate polygon approximation
    approxPolyDP(Mat(cont[index]), approxPoly, arcLength(cont[index], true) * 0.01, true);

    //Compute the bounding rect, minimum enclosing circle
    rect = boundingRect(cont[index]);
    bounding_rect = minAreaRect(cont[index]);
    minEnclosingCircle(cont[index], center, radius);

    //Calculate rectangle width
    double rectWidth = rect.br().x - rect.tl().x;

    //Calculate center points of rectangle
    int rectCenterX = rect.x + rect.width / 2;
    int rectCenterY = rect.y + rect.height / 2;

    //Store points for the bounding rectangle
    bounding_rect.points(points);
    vector< vector<Point> > poly;
    poly.resize(1);
    for (int j = 0; j < 4; ++j)
        poly[0].push_back(points[j]);

    //Check to see what shape it is
    bool isRect = approxPoly.size() >= 4 && approxPoly.size() <= 8;
    bool isCircle = approxPoly.size() >= 9 && approxPoly.size() <= 16;

    //Calculate focal length for the basket
    //cout << getFocalLength(rectWidth) << endl;

    //Distance to the object in CM
    //int dist = getDistance(rectWidth);
    //string distance = to_string(dist) + " CM";
    string distance = "";

    //Draw the corresponding bounding boxes and contours with the indexed contour

    //If its a rectangle draw the contours and a rectangular bounding with text saying the shape, color, and distance
    if(isRect){

        //This will ONLY draw whats inside the contours and bounding box
        fillConvexPoly(selectiveThresh, approxPoly, WHITE, 8);
        source->copyTo(*final, selectiveThresh);

        //Draw the contour outline and text
        drawContours(*final, cont, index, color0, 2);
        circle(*final, Point(rectCenterX, rectCenterY), 5, WHITE, 2);
        putText(*final, color + " Rectangle", Point(rectCenterX + 10, rectCenterY),
                FONT_HERSHEY_SIMPLEX, .5, WHITE, 2);
        putText(*final, distance, Point(rectCenterX + 10, rectCenterY + 20),
                FONT_HERSHEY_SIMPLEX, .40, BLACK, 1);
        polylines(*final, poly, true, color0, 2);
    }

    //If its a circle draw the contours and a circular bounding with text saying the shape, color, and distance
    else if(isCircle){

        //This will only draw whats inside the contour and bounding circle
        fillConvexPoly(selectiveThresh, approxPoly, WHITE, 8);
        source->copyTo(*final, selectiveThresh);

        //Draw the contour outline and text
        drawContours(*final, cont, index, color0, 2);
        circle(*final, Point(rectCenterX, rectCenterY), 5, WHITE, 2);
        putText(*final, color + " Circle", Point(rectCenterX + 10, rectCenterY),
                FONT_HERSHEY_SIMPLEX, .5, WHITE, 2);
        putText(*final, distance, Point(rectCenterX + 10, rectCenterY + 20),
                FONT_HERSHEY_SIMPLEX, .40, WHITE, 1);
        circle(*final, center, radius, color0, 2);

    }

    //If there is no object print out text on the screen
    else {

        //Print out "NO OBJECT DETECTED"
        Point s_center = Point(final->size().height * .4, final->size().width * .4);
        putText(*final, "NO OBJECT DETECTED", s_center, FONT_HERSHEY_SIMPLEX, .8, WHITE, 2);
    }

    //Clear frame to black
    selectiveThresh.setTo(BLACK);
}

//Find the largest contours of the thresholded image
// --Minimum largest area is always 1000 to avoid detecting very small objects and noise when there is
//   no very large object detected
// --NOTE--
//      If you run into problems trying to detect small objects or far away objects set it to a smaller value or 0
void Threshold::largestContours(){

    //Determine the largest contour area to draw
    double largestArea = 1000;
    int largestIndex = -1;

    for (int i = 0; i < cont.size(); i++) {

        double area = contourArea(cont[i]);

        if (area > largestArea) {
            largestArea = area;
            largestIndex = i;
        }
    }

    //Make sure there is a largest contour before drawing
    if(largestIndex != -1){

        draw(largestIndex);
    }
}

//Sets the current color (color0) to the color specified in the string value and also sets the corresponding HSV values
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
void Threshold::setColor() {

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
    } else if(color == "" && !initialized){

        cout << "Object was not initialized correctly and/or was initialized using the default constructor" << endl;
        return;

    } else {

        cout << color + " Is not a supported color" << endl;
        return;
    }
}

//Override default Threshold presets for the current image with a manually controlled one
void Threshold::setThreshold(){

    createThreshControl();
    showThresh();
}

//Create the control windows and track bars for thresholding upon calling this function
void Threshold::createThreshControl(){

    //Create track bars in "Control" window
    namedWindow("Control" ,CV_WINDOW_AUTOSIZE); //create a window called "Control"

    //Hue, Saturation, and Value
    cvCreateTrackbar("LowH", "Control", &minHue, 179); //Hue (0-179)
    cvCreateTrackbar("HighH", "Control", &maxHue, 179);

    cvCreateTrackbar("LowS", "Control", &minSat, 255); //Saturation (0 - 255)
    cvCreateTrackbar("HighS", "Control", &maxSat, 255);

    cvCreateTrackbar("LowV", "Control", &minVal, 255); //Value (0-255)
    cvCreateTrackbar("HighV", "Control", &maxVal, 255);

    //Morphological operator

    //Create a track bar for the amount of Morphological passes to apply, max value is 10
    cvCreateTrackbar("Passes", "Blur", &passes, 10);

    //Create a track bar for the size of the MORPH_SHAPE, max value is 25
    cvCreateTrackbar("Shape Size", "Blur",&morphSize, 25);

}

//Shows the threshold window
void Threshold::showThresh(){

    namedWindow(color + " Threshold", CV_WINDOW_FREERATIO);
    resizeWindow(color + " Threshold", 480, 360);
    imshow(color + " Threshold", threshold);
}

//Override for the default values of the Gaussian blur, size of the Morph shape, and also the Morphological passes
void Threshold::setBlur(){

    //Create a window of the color name + blur
    namedWindow("Blur", CV_WINDOW_AUTOSIZE);

    //Create a track bar for kernel X and Y, max value is 20 --Value cannot be even
    cvCreateTrackbar("Kernel X", "Blur", &kernelX, 20);
    cvCreateTrackbar("Kernel Y", "Blur", &kernelY, 20);

    //Create a track bar for sigma X and Y, max value is 10
    cvCreateTrackbar("Sigma X", "Blur", &sigmaX, 20);
    cvCreateTrackbar("Sigma Y", "Blur", &sigmaY, 20);

    //Show the threshold
    showThresh();
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
void Threshold::setMinHSV(int hue, int sat, int val){

    minHue = hue;
    minSat = sat;
    minVal = val;
}

//Override for maximum HSV values
void Threshold::setMaxHSV(int hue, int sat, int val) {

    maxHue = hue;
    maxSat = sat;
    maxVal = val;
}

//Initialize all the color values, HSV values, Morphological values, and blur values
void Threshold::initializeColors(){

    //Set initial blur values
    kernelX = 7;
    kernelY = 7;
    sigmaX = 3;
    sigmaY = 3;

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

//Return calculated focal length
int Threshold::getFocalLength(int pixWidth){

    return (pixWidth * 30) / 9;
}

//Return calculate distance
int Threshold::getDistance(double pixWidth){

    return (9 * focalLength) / pixWidth;
}


