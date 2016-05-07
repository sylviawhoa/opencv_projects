#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;


void MirrorX(Mat MirrorOut, Mat FrameIn)
{

// Mirrors across central row
Vec3b pixel;
int midpt = cvFloor(FrameIn.rows/2);
for(int i=0; i<midpt; i++){
	FrameIn.row(i).copyTo(MirrorOut.row(i));
    }

// Blurs the reflection - this part is optional & can be commented out
Mat FrameIn2; 
GaussianBlur(FrameIn, FrameIn2, Size(11,11), 8.5, 8.5);
for(int i=midpt; i<FrameIn2.rows; i++){
        FrameIn2.row(FrameIn2.rows-i).copyTo(MirrorOut.row(i));
    } 	
}

void MirrorY(Mat MirrorOut, Mat FrameIn)
// Mirrors across central column
{
Vec3b pixel;
int midpt = cvFloor(FrameIn.cols/2);
for(int i=0; i<midpt; i++){
        FrameIn.col(i).copyTo(MirrorOut.col(i));
    }

for(int i=midpt; i<FrameIn.cols; i++){
        FrameIn.col(FrameIn.cols-i).copyTo(MirrorOut.col(i));
    }

}


int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> edges; // get a new frame from camera
        MirrorX(edges,edges);  //mirror across x-axis
        //MirrorY(edges,edges); //mirror across y-axis
        imshow("edges",edges);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
