#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

void plaidImage(Mat plaidFrame, Mat frame) {

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

// red plaid with white stripes - avg rbg with red or white 
// height = 480, width = 640
// 

int wideband = 45;
int smallband = 9;
int medband = 15;


//draw widebands  - horizontal for now

int r= wideband;
while(r < (height)){
	for(int i = 0; i < width; i++){
		for(int j=0; j<wideband;j++){
			        pixel = frame.at<Vec3b>(j+r,i);
				pixel2[0]= .5*(pixel[0] +200);
                                pixel2[1]= .5*pixel[1];
                                pixel2[2] = .5*(pixel[2]+0);
                                plaidFrame.at<Vec3b>(j+r,i) = pixel2;
		}
 	}
        r = r+2*wideband;
}

//vertical

int c= wideband;
while(c < (width - wideband)){
        for(int i = 0; i < height; i++){
                for(int j=0; j<wideband;j++){
                                pixel = plaidFrame.at<Vec3b>(i,j+c);
                                pixel2[0]= .5*(pixel[0]+200);
                                pixel2[1]= .5*pixel[1];
                                pixel2[2] = .5*(pixel[2]+0);
                                plaidFrame.at<Vec3b>(i,j+c) = pixel2;
                }
        }
        c = c+2*wideband;
}


//draw smallband
int r2= wideband +.5*(wideband-smallband);
while(r2 < (height)){
        for(int i = 0; i < width; i++){
                for(int j=0; j<smallband;j++){
                                pixel = plaidFrame.at<Vec3b>(j+r2,i);
                                pixel2[0]= .5*(pixel[0]+255);
                                pixel2[1]= .5*(pixel[1]+255);
                                pixel2[2] = .5*(pixel[2]+255);
                                plaidFrame.at<Vec3b>(j+r2,i) = pixel2;
                }
        }
        r2 = r2+4*wideband;
}

//vertical

int c2= wideband +.5*(wideband-smallband);;
while(c2 < (width)){
        for(int i = 0; i < height; i++){
                for(int j=0; j<smallband;j++){
                                pixel = plaidFrame.at<Vec3b>(i,j+c2);
                                pixel2[0]= .5*(pixel[0]+255);
                                pixel2[1]= .5*(pixel[1]+255);
                                pixel2[2] = .5*(pixel[2]+255);
                                plaidFrame.at<Vec3b>(i,j+c2) = pixel2;
                }
        }
        c2 = c2+4*wideband;
}


//draw medband
int r3 = 3*wideband +.5*(wideband-medband);
while(r3 < (height)){
        for(int i = 0; i < width; i++){
                for(int j=0; j<medband;j++){
                                pixel = plaidFrame.at<Vec3b>(j+r3,i);
                                pixel2[0]= .5*(pixel[0]+100);
                                pixel2[1]= .5*(pixel[1]+200);
                                pixel2[2] = .5*(pixel[2]+0);
                                plaidFrame.at<Vec3b>(j+r3,i) = pixel2;
                }
        }
        r3 = r3+4*wideband;
}

//vertical

int c3= 3*wideband +.5*(wideband-medband);;
while(c3 < (width)){
        for(int i = 0; i < height; i++){
                for(int j=0; j<medband;j++){
                                pixel = plaidFrame.at<Vec3b>(i,j+c3);
                                pixel2[0]= .5*(pixel[0]+100);
                                pixel2[1]= .5*(pixel[1]+200);
                                pixel2[2] = .5*(pixel[2]+0);
                                plaidFrame.at<Vec3b>(i,j+c3) = pixel2;
                }
        }
        c3 = c3+4*wideband;
}

/*
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

*/

}


int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat frame;
    Mat plaidFrame;
    cap >> frame; // get a new frame from camera
  //  plaidFrame = frame.clone();
    namedWindow("plaid",1);
 
   for(;;)
    {
        cap >> frame; // get a new frame from camera
//	GaussianBlur(frame, frame, Size(11,11), 5.5, 5.5); 
        plaidFrame = frame.clone();
	plaidImage(plaidFrame, frame);
        imshow("plaid", plaidFrame);
        if(waitKey(30) >= 0) break;
    }
	return 0;
}
