#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

//get avg color in square
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


//get dist between 3d avg vectors
int getDist(Vec3b left, Vec3b right){
	return ceil(sqrt((left[0]-right[0])*(left[0]-right[0]) + (left[1]-right[1])*(left[1]-right[1]) + (left[2]-right[2])*(left[2]-right[2])
	));
}


double getStandardDev(Mat frame,int x,int y, int square, Vec3b avg){
	double sum = 0;
	Vec3b pixel;
 	for(int m=0; m<square; m++){
	        for(int n=0; n<square; n++){
			pixel = frame.at<Vec3b>(square*x+m,square*y+n);
			sum += (pixel[0]-avg[0])*(pixel[0]-avg[0]) + (pixel[1]-avg[1])*(pixel[1]-avg[1]) + 								   (pixel[2]-avg[2])*(pixel[2]-avg[2]);
		}
	}
	double dev = sqrt(sum)*square; 
	return dev;
}

//get max of 4 elements
double getmax(double a, double b, double c, double d){
	if((a >= b)&&(a >=c)&&(a>=d)){	
		return a;
	}
	else  if((b >=c)&&(b >=d)&&(b>=a)){  
                return b;
        }
	else  if((c>=d)&&(c >=a)&&(c>=b)){  
                return c;
        }
	else {
	return d;
	}
}




		


//draw a black pixel or square if the dist between left and right or top and bottom squares exceeds threshold parameter
Mat showedges(Mat copy, Mat frame) {
	int square = 2;
	int length = frame.rows/square;
        int width = frame.cols/square;
	Vec3b B = frame.at<Vec3b>(10,10);
        for(int x=1; x < length-1; x++){
            for(int y=1; y<width-1; y++){
	    	Vec3b L = getAvgColor(frame, x-1,y,square);
		Vec3b R = getAvgColor(frame, x+1,y,square);
		Vec3b T = getAvgColor(frame, x,y-1,square);
		Vec3b B = getAvgColor(frame, x,y+1,square);
                int thresh = 10;
		double DL = getStandardDev(frame,x,y,square,L);
		double DR = getStandardDev(frame,x,y,square,R);
		double DT = getStandardDev(frame,x,y,square,T);
		double DB = getStandardDev(frame,x,y,square,B);
               	double M = getmax(DL,DR,DT,DB);
		if (M > 3){
                   thresh += 2*log(M);
                }
		if((getDist(L,R)>thresh)||(getDist(T,B)>thresh)){ 
		// for(int m=0; m<square; m++){
                  //    for(int n=0; n<square; n++){
		int m = 0; int n = 0;	
		copy.at<Vec3b>(square*x+m,square*y+n) = 0*B;
                   //  }
                 //  }                
		}

	//	if((getDist(L,R)>thresh)&&(getDist(T,B)>thresh)){
	//		copy.at<Vec3b>(square*x-1,square*y) = 0*B;
	//		copy.at<Vec3b>(square*x,square*y) = 0*B;
		//	copy.at<Vec3b>(square*x+1,square*y) = 0*B;
	//		copy.at<Vec3b>(square*x,square*y-1) = 0*B;
	//		copy.at<Vec3b>(square*x,square*y) = 0*B;
		//	copy.at<Vec3b>(square*x,square*y+1) = 0*B;
	//		}
	//	else if(getDist(L,R)>thresh) {
	//		copy.at<Vec3b>(square*x-1,square*y) = 0*B;
	//		copy.at<Vec3b>(square*x,square*y) = 0*B;
		//	copy.at<Vec3b>(square*x+1,square*y) = 0*B;
	//		}
	//	else if(getDist(T,B)>thresh){
	//		copy.at<Vec3b>(square*x,square*y-1) = 0*B;
	//		copy.at<Vec3b>(square*x,square*y) = 0*B;
		//	copy.at<Vec3b>(square*x,square*y+1) = 0*B;
	//		}		


	    } 
         } 	
	return copy;
}

// connect the dots
Mat dconnect(Mat copy){
	Vec3b black = {0,0,0};
	for(int x = 1; x< copy.rows-1; x++){
		for(int y =1; y<copy.cols-1; y++){
			if((copy.at<Vec3b>(x-1,y)==black)&&(copy.at<Vec3b>(x+1,y)==black)){
				copy.at<Vec3b>(x,y) = black;
			}
			else if((copy.at<Vec3b>(x-1,y+1) ==black)&&(copy.at<Vec3b>(x+1,y-1)==black)){
                                copy.at<Vec3b>(x,y) = black;
                        }
		
                        else if((copy.at<Vec3b>(x,y-1) ==black)&&(copy.at<Vec3b>(x,y+1)==black)){
                                copy.at<Vec3b>(x,y) = black;
                        }
                        else if((copy.at<Vec3b>(x-1,y-1)==black)&&(copy.at<Vec3b>(x+1,y+1)==black)){
                                copy.at<Vec3b>(x,y) = black;
                        }
		}
	}
	return copy;
}


Mat blackandwhite(Mat copy){
	Vec3b white = {255,255,255};
	Vec3b black = {0,0,0};
	        for(int x = 1; x< copy.rows; x++){
                	for(int y =1; y<copy.cols; y++){
				if(copy.at<Vec3b>(x,y)!=black){
					copy.at<Vec3b>(x,y)= white;
				}
			}
		}
	return copy;
}


int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat frame;
    Mat copy;
    cap >> frame; // get a new frame from camera
    namedWindow("edgeprogram",1);


   for(;;)
    {
        cap >> frame; // get a new frame from camera
        GaussianBlur(frame, frame, Size(11,11), 5.5,5.5);
	copy = frame.clone();       
	Mat final = showedges(copy, frame);
	final =	blackandwhite(dconnect(final));
        imshow("edgeprogram", final);
        if(waitKey(30) >= 0) break;
    }
        return 0;
}







