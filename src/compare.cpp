// opencv stuff
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/contrib/contrib.hpp>

#include "openCVHelpers.h"

#include <iostream>

using namespace vdff;
using namespace std;
using namespace Utils;

int main(int argc, char **argv) {

        string im1,im2,imdiff;
        getParam("im1", im1, argc, argv);
        getParam("im2", im2, argc, argv);
        getParam("diff", imdiff, argc, argv);




        cv::Mat depthFromGray = cv::imread(im1,CV_LOAD_IMAGE_UNCHANGED);
        cv::Mat depthFromColor = cv::imread(im2,CV_LOAD_IMAGE_UNCHANGED);

        cout<<"im1: ";
        openCVHelpers::imgInfo(depthFromGray,true);
        cout<<endl<<"im2: ";
        openCVHelpers::imgInfo(depthFromColor,true);

        cv::Mat diff = abs(depthFromColor-depthFromGray);
        cout<<endl<<"diff: ";
        openCVHelpers::imgInfo(diff,true);

        double min,max;
        cv::minMaxLoc(diff,&min,&max);
        float scale = 255.0f / (max - min);
        cv::Mat depthMap;
        diff.convertTo(depthMap, CV_8UC1, scale, -min*scale);


        cv::imshow("diff",depthMap);
        imwrite(imdiff+".png",depthMap);
        imwrite(imdiff+".exr",diff);

        cv::waitKey(0);

}
