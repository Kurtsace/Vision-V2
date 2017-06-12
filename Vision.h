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
#include <opencv2/features2d.hpp>
#include <opencv2/core/core.hpp>
#include "Sport.h"
#include <iostream>

#ifndef VISION_THRESHOLD_H
#define VISION_THRESHOLD_H

using namespace cv;
using namespace std;

class Vision{

public:

    //Public methods
    Vision(Mat *src, string c, Mat *fin);
    Vision();
    void stop();
    void setMinHSV(int hue, int sat, int val);
    void setMaxHSV(int hue, int sat, int val);
    void setThreshold();
    void setSingleThreshold();
    void start();
    void setBlur();
    void detectRect(bool condition);
    void detectCircle(bool condition);
    void mode(int sport, int robot);
    Point getPos();
    int getDistance();


private:

    //Variables

    //Mat frames
    Mat *source, src, tempOutFrame, *final;

    //Vectors
    vector < vector<Point> > contour;
    vector< Point > approx;

    //Color identifiers
    string color, uColor;
    Scalar color0;

    //Sport/Events to process
    bool ROBOCUP, SPRINT, MARATHON, BASKETBALL, WEIGHTLIFTING, SOCCER, ARCHERY;

    //Object #
    int id;

    //Focal length
    int focalLength;

    //Real world distance -- In CM
    int distance;

    //HSV values
    int minHue, minSat, minVal;
    int maxHue, maxSat, maxVal;

    //Single channel values
    int minRGB, maxRGB;

    //For the Morphological operator
    int passes, morphSize;

    //Gaussian values
    int kernelX, kernelY, sigmaX, sigmaY;

    //Initialize
    bool initialized;

    //What shape is it
    bool isRect, isCircle;

    //What shape to detect
    bool detectRectangle, detectCirc;

    //Is an object detected
    bool detected;

    //Center coordinates for object
    int rectCenterX, rectCenterY;

    //Contour size
    double largestArea;

    //Position of the ball --CENTER POINT
    Point objPos;

    //Scalar values for color
    //B, G, R
    Scalar RED, GREEN, BLUE, WHITE, YELLOW, BLACK;

    //For contours and shape recognition
    bool filtered = false;

    double min;
    double max;

    //For line segment detection
    Ptr<LineSegmentDetector> lineSeg;
    vector<Vec4f> lines;

    //For circle detection
    int minDist;
    int param1, param2;
    vector<Vec3f> circles;

    //For Canny
    int edgeThresh, lowThresh;
    int kernel;
    int ratio;
    Mat detect, out;

    Mat binary_copy;

    //Private methods
    void createThreshControl();
    void setColor();
    void largestContour(vector<vector<Point>> inputArray);
    void drawHUD();
    void draw(int index, vector<vector<Point>> cont, vector<Point> approx);
    void createThresh(vector<vector<Point>> contour, bool singleChannel, int method);
    void initializeColors();
    void initializeDefaultParameters();
    void determineShape(vector<vector<Point>> contour, int index);
    void roundestContour(vector<vector<Point>> inputArray);
    vector<vector<Point>> filterNoise(vector<vector<Point>> contour);
    void regionOfInterest(int index);
    void setDistance(vector<Point> object, int focalLength);


};

#endif //VISION_THRESHOLD_H
