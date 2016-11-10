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

    Mat *source, hsv, threshold, *final;
    string color;
    Scalar color0;

    //Scalar values for color
    //B, G, R
    Scalar RED = Scalar(0, 0, 255);
    Scalar GREEN = Scalar(0, 255, 0);
    Scalar BLUE = Scalar(255, 0 ,0);
    Scalar WHITE = Scalar(255, 255, 255);
    Scalar YELLOW = Scalar(0, 215, 255);
    Scalar BLACK = Scalar(0, 0, 0);

    //For contours and shape recognition
    vector< vector<Point> > cont;
    vector< Point > approxPoly;

    //Private methods
    void createThreshControl();
    void setColor();
    void largestContours();
    void draw(int index);

};

#endif //VISION_THRESHOLD_H
