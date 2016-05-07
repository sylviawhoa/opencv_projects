#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

void splitBGR(Mat blueFrame, Mat greenFrame, Mat redFrame, Mat frame) {

    int height = frame.rows;
    int width = frame.cols;

    Vec3b pixel;
    Vec3b pixelb;
    Vec3b pixelg;
    Vec3b pixelr;
    
    for (int i = 0; i< height; i++){
        for(int j = 0; j < width; j++){
            pixel = frame.at<Vec3b>(i,j);

            // blue = {255,0,0}; RED
                pixelb[0]= 0;
                pixelb[1]= 0;
                pixelb[2] = pixel[2];

            // green = {0,255,0};
                pixelg[0]= pixel[0];
                pixelg[1]= pixel[1];
                pixelg[2] = pixel[2];

            // red = {0,0,255}; 
                pixelr[0]= .8*pixel[0];
                pixelr[1]= .8*pixel[1];
                pixelr[2] = 0;

                blueFrame.at<Vec3b>(i,j) = pixelb;       
                greenFrame.at<Vec3b>(i,j) = pixelg;
                redFrame.at<Vec3b>(i,j) = pixelr;
        }
    }
}

void combineBGR(Mat outFrame, Mat blueFrame, Mat greenFrame, Mat redFrame) {

    int height = redFrame.rows;
    int width = redFrame.cols;

    // Vec3b pixel;
    Vec3b pixelb;
    Vec3b pixelg;
    Vec3b pixelr;

    for (int i = 0; i< height; i++){
        for(int j = 10; j < width-10; j++){
            pixelb = blueFrame.at<Vec3b>(i,j-10);
            pixelg = greenFrame.at<Vec3b>(i,j);
            pixelr = redFrame.at<Vec3b>(i,j+10);
            outFrame.at<Vec3b>(i,j) = .33*pixelb + .33*pixelg + .33*pixelr;
        }
    }

            // without gaussian
    // for (int i = 0; i< height; i++){
    //     for(int j = 0; j < 10; j++){
    //         outFrame.at<Vec3b>(i,j) = redFrame.at<Vec3b>(i,j);
    //         // .33*pixelb + .33*pixelg + .33*pixelr;
    //         // outFrame.at<Vec3b>(i,j) = pixelb;
    //     }
    // }

}

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat frame;
    Mat outFrame;
    Mat blueFrame;
    Mat greenFrame;
    Mat redFrame;

    cap >> frame; // get a new frame from camera

    blueFrame = frame.clone();
    greenFrame = frame.clone();
    redFrame = frame.clone();
    outFrame = frame.clone();
    namedWindow("3DWebCam",1);
 
   for(;;)
    {
        cap >> frame; // get a new frame from camera
        blueFrame = frame.clone();
        greenFrame = frame.clone();
        redFrame = frame.clone();
        outFrame = frame.clone();
//  GaussianBlur(frame, frame, Size(11,11), 5.5, 5.5); 
        splitBGR(blueFrame, greenFrame, redFrame, frame);
        combineBGR(outFrame, blueFrame, greenFrame, redFrame);
        imshow("3DWebCam", outFrame);
        if(waitKey(30) >= 0) break;
    }
    return 0;
}
