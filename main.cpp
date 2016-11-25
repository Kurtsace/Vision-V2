#include "Threshold.h"

using namespace std;
using namespace cv;

//Create 2 Mat objects, source and final
Mat source, final;

//Screen size
int width = 640;
int height = (width / 4) * 3;

//Initialize object after creating source and final
Threshold red(&source, "RED", &final);

//Create imshow windows
void createWindows();

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

        //Check to see if reading frame was successful
        if(!success){

            cout << "Error reading frame from camera" << endl;
            break;
        }

        //Call start for the objects in the while loop
        red.start();

        //Show output
        createWindows();

        //Break out of the loop if ESC key is pressed
        if(waitKey(30) == 27){

            cout << "ESC key was pressed" << endl;

            //Kill the initialized objects and destroy all existing windows
            red.stop();
            destroyAllWindows();

            break;
        }
    }

    return 0;
}

//Create imshow windows
void createWindows(){

    //Create a single imshow window containing only final
    namedWindow("Output", CV_WINDOW_FREERATIO);
    resizeWindow("Output", width, height);
    imshow("Output", final);

    //Create a small imshow window containing the source frame
    namedWindow("Source", CV_WINDOW_FREERATIO);
    resizeWindow("Source", 480, (480 / 4) * 3);
    imshow("Source", source);
}