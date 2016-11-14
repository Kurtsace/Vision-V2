#include "Threshold.h"

using namespace std;
using namespace cv;

//Create 2 Mat objects, source and final
Mat source, final;

//Initialize object after creating source and final
Threshold red(&source, "RED", &final);
Threshold yellow(&source, "YELLOW", &final);

int main() {

    VideoCapture cap(0);

    //Check to see if opening the camera worked
    if(!cap.isOpened()){

        cout << "Error opening camera" << endl;
        return -1;
    }

    //Infinite while loop
    while(1){

        //Store the frame into source
        bool success = cap.read(source);

        //Copy source image into final
        source.copyTo(final);

        //Check to see if reading frame was successful
        if(!success){

            cout << "Error reading frame from camera" << endl;
            break;
        }

        //Call start for the object in the while loop
        yellow.start();
        red.start();

        red.showThresh();
        yellow.showThresh();

        //Create a single imshow window containing only final
        namedWindow("Output", CV_WINDOW_AUTOSIZE);
        imshow("Output", final);

        //Break out of the loop if ESC key is pressed
        if(waitKey(30) == 27){

            cout << "ESC key was pressed" << endl;

            //Kill the initialized object and destroy all existing windows
            red.stop();
            destroyAllWindows();

            break;
        }
    }

    return 0;
}