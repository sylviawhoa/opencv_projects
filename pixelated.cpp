#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;


// function to take 10x10 square and set every pixel to the avg color 

//get avg color
Vec3b getAvgColor(Mat frame,int x,int y, int square){
		int avgB = 0;
		int avgG = 0;
		int avgR = 0;
		Vec3b pixel;
		for(int m=0; m<square; m++){
			for(int n=0; n<square; n++){
				pixel = frame.at<Vec3b>(square*x+m,square*y+n);
				avgB += pixel[0];
				avgG += pixel[1];
				avgR += pixel[2];	
			}
		}
		int B = avgB/(square*square);
		int G = avgG/(square*square);
		int R = avgR/(square*square);
		Vec3b A;
		A[0] = B;
		A[1] = G;
		A[2] = R;
		return A;
		
}


//set avg color
void setAvgColor(Mat frame,int x,int y, int square, Vec3b A){
		for(int m=0; m<square; m++){
			for(int n=0; n<square; n++){
				frame.at<Vec3b>(square*x+m,square*y+n) = A;	
            		}
		}  
}



int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
	Mat frame;
 	cap >> frame; // get a new frame from camera
		
    for(;;)
    {
        cap >> frame; // get a new frame from camera
        int square = 10;
	int length = frame.rows/square;
        int width = frame.cols/square;       
		for(int x=0; x < length; x++){
 		for(int y=0; y<width; y++){
			Vec3b AV = getAvgColor(frame, x,y,square);
			setAvgColor(frame, x,y,square, AV);
		}
	}

        imshow("Pixelated", frame);
        if(waitKey(30) >= 0) break;
    }
        return 0;
}
