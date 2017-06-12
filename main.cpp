#include <iostream>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui.hpp>
#include "Vision.h"

using namespace std;
using namespace cv;


Mat source, final;

Vision v(&source, "RED", &final);

int main(){

    v.detectCircle(true);
    v.detectRect(true);

    VideoCapture cap(1);

    if(!cap.isOpened()){

        cout << " ERROR OPENING CAMERA " << endl;
        return -1;
    }

    while(1){

        if(!cap.read(source)){

            cout << "Error reading frame" << endl;
            break;
        }

        v.start();
        v.setSingleThreshold();

        namedWindow("Final", CV_WINDOW_AUTOSIZE);
        imshow("Final", final);


        if(waitKey(30) == 27){

            v.stop();
            cout << "ESC was pressed" << endl;
            break;
        }
    }

    return 0;
}

