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


    //Variables

    //Hue, Saturation, Value
    int minHue, maxHue, minSat, maxSat, minVal, maxVal;

    //For the Morphological operator
    int passes, morphSize;

    //Gaussian values
    int kernelX, kernelY, sigmaX, sigmaY;

    //Initialize
    bool initialized;

    //Scalar values for color
    //B, G, R
    const Scalar RED = Scalar(0, 0, 255);
    const Scalar GREEN = Scalar(0, 255, 0);
    const Scalar BLUE = Scalar(255, 0 ,0);
    const Scalar WHITE = Scalar(255, 255, 255);
    const Scalar YELLOW = Scalar(0, 215, 255);
    const Scalar BLACK = Scalar(0, 0, 0);

    //For contours and shape recognition
    vector< vector<Point> > cont;
    vector< Point > approxPoly;

    //Private methods
    void createThreshControl();
    void setColor();
    void largestContours();
    void draw(int index);
    int getFocalLength(int pixWidth);
    int getDistance(double pixWidth);

};

#endif //VISION_THRESHOLD_H
