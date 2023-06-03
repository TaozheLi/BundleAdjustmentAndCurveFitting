//
// Created by simmons on 6/2/23.
//
#include "opencv2/opencv.hpp"
#include "BundleAdjustmentCostFunction.h"
class Convert{
public:
    Convert();
//    bool Convert2Dto3D(cv::KeyPoint &p, cv::Vec3f P);
    bool static Convert2Dto3D(cv::KeyPoint &p, double* P, double &depth);
//    bool Convert2Dto3D(double *p, double * P);
    bool static ConvertMatToArray(cv::Mat &matrix, double * p);
    bool static ConvertMatToArray(cv::Mat &matrix, float * p);
    bool static DecomposeT(cv::Mat &matrix, double *R, double *t);
    bool static SetStaticMatrix(cv::Mat &LTcw, cv::Mat &CTcw);
    bool static GetR_t_Last(double * camera, double *t);
    bool static GetR_t_Current(double * camera, double *t);

public:
    static bool initialize;
    static cv::Mat LastFrameTcw;
    static cv::Mat LastFrameR;
    static cv::Mat LastFramet;

    static cv::Mat CurrentFrameTcw;
    static cv::Mat CurrentFrameR;
    static cv::Mat CurrentFramet;
    double mdepth;
};
