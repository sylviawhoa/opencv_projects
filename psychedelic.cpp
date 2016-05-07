#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

void redImage(Mat redFrame, Mat frame) {
 
//  Mat lens;
//  cvtColor(frame, lens, COLOR_BGR2GRAY);
//  GaussianBlur(lens, lens, Size(17,17), 1.5, 1.5);
//  Canny(lens, lens, 0, 30, 3);
 Vec3b pixel, pixel2; 
//  uchar spixel;
/* 
     for (int i = 0; i < lens.rows-10; ++i) {
        for (int j = 0; j < lens.cols-10; ++j) {

               if(lens.at<uchar>(i+10,j+10)>100){
		for(int k =0; k<10; k++){
		   for(int n=0; n<10; n++){
                lens.at<uchar>(i+n,j+k) = 255;
			}
                }
  		}    
 }}
    GaussianBlur(lens, lens, Size(31,31), 1.5, 1.5);

*/
// 480 x 640
  
  GaussianBlur(frame, frame, Size(11,11), 5.5, 5.5);




     for (int i = 0; i < frame.rows; ++i) {
        for (int j = 0; j < frame.cols; ++j) {
       
                pixel = frame.at<Vec3b>(i,j);
 //		spixel = lens.at<uchar>(i,j);

            	double B = pixel[0];
            	double G = pixel[1];
            	double R = pixel[2];
			
		double B2 = B*.2*(1-B);
		double G2 = G*.2*(1-G);
		double R2 = R*.2*(1-R);
			

             	pixel2[0] = B2;
		pixel2[1] = G2;
		pixel2[2] = R2;

//		pixel2[0] = B2*(spixel/255);
  //          	pixel2[1] = G2*(spixel/255);
    //       	pixel2[2] = R2*(spixel/255);
         //       pixel2[0] = B2;
         //      pixel2[1] = G2;
         //     pixel2[2] = R2;

		redFrame.at<Vec3b>(i,j) = pixel2;
        }
    }
}

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat frame;
    Mat redFrame;
    cap >> frame; // get a new frame from camera
    redFrame = frame.clone();
    namedWindow("thered",1);

//	Mat lens;
//	cvtColor(frame, lens, COLOR_BGR2GRAY);
//	GaussianBlur(lens, lens, Size(17,17), 1.5, 1.5);
//	Canny(lens, lens, 0, 30, 3);
//	std::cout << "lens size = " << lens.rows << " x " << lens.cols << std::endl << std::endl;
//	std::cout << "frame size = " << frame.rows << " x " << frame.cols << std::endl << std::endl;
 
   for(;;)
    {
        cap >> frame; // get a new frame from camera
//	GaussianBlur(frame, frame, Size(11,11), 5.5, 5.5); 
       redImage(redFrame, frame);
        imshow("thered", redFrame);
        if(waitKey(30) >= 0) break;
    }
	return 0;
}
