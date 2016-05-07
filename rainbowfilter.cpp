#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

void rainbowImage(Mat rainbowFrame, Mat frame) {


// split the frame into 6 horizontal rows

int height = frame.rows;
int width = frame.cols;

// BGR  values for red,orange,yellow, green, blue, purple
// red = {0,0,255}; 
//orange = {0,122,255};
// yellow = {0,255,255};
// green = {0,255,0};
// blue = {255,0,0};
// purple = {255,0,255};
	
Vec3b pixel;
Vec3b pixel2;

for (int n = 1; n <= 6; n++){
	for (int i = (n-1)* height/6; i< n* height/6 ; i++){
		for(int j = 0; j < width; j++){
			pixel = frame.at<Vec3b>(i,j);
			if(n==1){
				pixel2[0]= 0;
				pixel2[1]= 0;
				pixel2[2] = pixel[2];
				rainbowFrame.at<Vec3b>(i,j) = pixel2;		
			}
			else if (n==2){
                                pixel2[0]= 0;
                                pixel2[1]= ceil(.5*pixel[1]);
                                pixel2[2] = pixel[2];
                                rainbowFrame.at<Vec3b>(i,j) = pixel2;
                        }
                        
			else if (n==3){
                                pixel2[0]= 0;
                                pixel2[1]= pixel[1];
                                pixel2[2] = pixel[2];
                                rainbowFrame.at<Vec3b>(i,j) = pixel2;
                        }
                        else if (n==4){
                                pixel2[0]= 0;
                                pixel2[1]= pixel[1];
                                pixel2[2] = 0;
                                rainbowFrame.at<Vec3b>(i,j) = pixel2;
                        }

                        else if (n==5){
                                pixel2[0]= pixel[0];
                                pixel2[1]= 0;
                                pixel2[2] = 0;
                                rainbowFrame.at<Vec3b>(i,j) = pixel2;
                        }

                        else if (n==6){
                                pixel2[0]= pixel[0];
                                pixel2[1]= 0;
                                pixel2[2] = pixel[2];
                                rainbowFrame.at<Vec3b>(i,j) = pixel2;
                        }

		}
	}
}

}


int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat frame;
    Mat rainbowFrame;
    cap >> frame; // get a new frame from camera
    rainbowFrame = frame.clone();
    namedWindow("June26",1);
 
   for(;;)
    {
        cap >> frame; // get a new frame from camera
//	GaussianBlur(frame, frame, Size(11,11), 5.5, 5.5); 
       rainbowImage(rainbowFrame, frame);
        imshow("June26", rainbowFrame);
        if(waitKey(30) >= 0) break;
    }
	return 0;
}
