/*
 *
 *
 *
 *
 *
 *
 */


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

#ifndef VISION_THRESHOLD_H
#define VISION_THRESHOLD_H

using namespace cv;
using namespace std;

class Threshold{

public:

    //Public methods
    Threshold(Mat *src, string c, Mat *fin);
    Threshold();
    void stop();
    void setMinHSV(int hue, int sat, int val);
    void setMaxHSV(int hue, int sat, int val);
    void setThreshold();
    void start();
    void showThresh();
    void setBlur();

private:

    //Variables

    //Mat frames
    Mat *source, hsv, threshold, selectiveThresh, inverse, invertedThresh, *final;

    //Color identifiers
    string color, uColor;
    Scalar color0;

    //Object #
    int id;

    //HSV values
    int minHue, minSat, minVal;
    int maxHue, maxSat, maxVal;

    //For the Morphological operator
    int passes, morphSize;

    //Gaussian values
    int kernelX, kernelY, sigmaX, sigmaY;

    //Initialize
    bool initialized;

    //What shape is it
    bool isRect, isCircle;

    //Is an object detected
    bool detected;

    //Center coordinates for object
    int rectCenterX, rectCenterY;

    //Contour size
    double largestArea;

    //Position of the ball --CENTER POINT
    Point objPos;
    string quadrant;

    //Scalar values for color
    //B, G, R
    Scalar RED, GREEN, BLUE, WHITE, YELLOW, BLACK;

    //For contours and shape recognition
    vector< vector<Point> > cont;
    vector< Vec4i > hierarchy;
    vector< Point > approxPoly;

    //Private methods
    void createThreshControl();
    void setColor();
    void largestContours();
    void drawHUD();
    void draw(int index);
    void initializeColors();
    void regionOfInterest(int index);
    int getFocalLength(int pixWidth);
    int getDistance(double pixWidth);
    Point getObjPos();

};

#endif //VISION_THRESHOLD_H
