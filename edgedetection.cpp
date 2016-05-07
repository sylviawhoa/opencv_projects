#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

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
	cap >> frame; // get a new frame from camera
//        bilateralFilter(edges, edges, 3, 18,18);
	cvtColor(frame, edges, COLOR_BGR2GRAY);
//	Mat acc = Mat::zeros(frame.size(),CV_64FC1);
	GaussianBlur(edges, edges, Size(17,17), 1.5, 1.5);
  //      bilateralFilter(edges, edges, 3, 18,18); 
        Canny(edges, edges, 0, 30, 3);
//      accumulateWeighted(edges, acc,0.95);
//	accumulateWeighted(acc, acc,0.5);
//      imshow("edges", acc);
	imshow("edges", edges);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
