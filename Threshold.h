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

struct ColorValue{

    //B, G, R
    Scalar RED = Scalar(0, 0, 255);
    Scalar GREEN = Scalar(0, 255, 0);
    Scalar BLUE = Scalar(255, 0 ,0);
    Scalar WHITE = Scalar(255, 255, 255);
    Scalar YELLOW = Scalar(0, 215, 255);
    Scalar BLACK = Scalar(0, 0, 0);

};
struct BlurValues{

    int kernelX = 5;
    int kernelY = 5;

    int sigmaX = 3;
    int sigmaY = 3;

};
struct HSV {

    //Hue, Saturation, Value
    int minHue = 0;
    int maxHue = 179;

    int minSat = 0;
    int maxSat = 255;

    int minVal = 0;
    int maxVal = 255;

    //For the Morphological operator
    int passes = 2;

    int morphSize = 1;
};

class Threshold{

public:

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

    Mat *source, hsv, threshold, *final;
    string color;
    Scalar color0;

    HSV preset;
    ColorValue color1;
    BlurValues blur0;

    vector< vector<Point> > cont;
    vector< Point > approxPoly;

    bool initialized = false;

    void createThreshControl();
    void setColor();
    void largestContours();
    void draw(int index);

};

#endif //VISION_THRESHOLD_H
