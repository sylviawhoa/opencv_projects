#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;


//get a square camera frame

//split into 4 


void splitFour(Mat outFrame, Mat frame){

	for(int x=0;x<240;x++){
		for(int y=0; y<240;y++){
			outFrame.at<Vec3b>(y,x) = frame.at<Vec3b>(2*y,2*x);
		}
		for(int y=240; y<480; y++){
			outFrame.at<Vec3b>(y,x) = frame.at<Vec3b>(2*x, 2*(480-y)-1);
		}
	}
	
	for(int x=240;x<480;x++){
                for(int y=0; y<240;y++){
                        outFrame.at<Vec3b>(y,x) = frame.at<Vec3b>(2*(480-x)-1,2*y);  
               }
                for(int y=240; y<480; y++){
                        outFrame.at<Vec3b>(y,x) = frame.at<Vec3b>(2*(480-y)-1,2*(480-x)-1);
                }
	}


}


void centerFrame(Mat frame1,Mat frame){
	for(int x=0; x<480;x++){
                for(int y=0; y<480;y++){
                        frame1.at<Vec3b>(y,x) = frame.at<Vec3b>(y,x+120);
                }
        }
}



int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

   Mat out;
   Mat out2;
   Mat out3;
   Mat frame;
   cap >> frame; // get a new frame from camera
   out = frame.clone();
   out2 = out.clone();
   out3 = out2.clone();
	// resizeWindow("Kaleidoscope", 480, 480);
   for(;;)
    {
	cap >> frame; // get a new frame from camera
//	centerFrame(frame,frame);
     	splitFour(out,frame);
	splitFour(out2,out);
	splitFour(out3,out2);
	namedWindow("Kaleidoscope",WINDOW_NORMAL);
    	resizeWindow("Kaleidoscope", 480, 480);
	imshow("Kaleidoscope", out3);
        if(waitKey(30) >= 0) break;
    }
	return 0;
}
