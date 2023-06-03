//
// Created by simmons on 6/2/23.
//


#include "Convert.h"
#include "BundleAdjustmentCostFunction.h"
Convert::Convert(){}

bool Convert::ConvertMatToArray(cv::Mat &matrix, double *p) {
    if(matrix.type()!=6){
        std::cout<<"Mat type should be cv::CV_64F when your input type pointer is double\n";
        return false;
    }
    else{
        for(int i=0;i<matrix.rows;i++)
            for(int j=0; j<matrix.cols; j++)
                p[i*matrix.cols + j] = matrix.at<double>(i, j);

    }
    return true;
}

bool Convert::ConvertMatToArray(cv::Mat &matrix, float *p) {
    if(matrix.type()!=5){
        std::cout<<"Mat type should be cv::CV_32F when your input type pointer is float\n";
        return false;
    }
    else{
        for(int i=0;i<matrix.rows;i++)
            for(int j=0; j<matrix.cols; j++)
                p[i*matrix.cols + j] = matrix.at<float>(i, j);
    }
    return true;
}

bool Convert::DecomposeT(cv::Mat &matrix, double *R, double *t) {
    if(!initialize) {
        std::cout<<"please initialize LastFrameTcw and CurrentFrameTcw"<<std::endl;
        return false;
    }
    cv::Mat RotationMatrix(3, 3, CV_64F);
    cv::Mat translation(3, 1, CV_64F);
    if(matrix.type() != RotationMatrix.type()) return false;
    matrix.rowRange(0, 3).colRange(0, 3).copyTo(RotationMatrix);
    if (matrix.type() != translation.type()) return false;
    matrix.rowRange(0, 3).col(3).copyTo(translation);
    ConvertMatToArray(RotationMatrix, R);
    ConvertMatToArray(translation, t);
    return true;
}

bool Convert::GetR_t_Last(double *camera, double *t) {
    if(!initialize) return false;
    if(Convert::ConvertMatToArray(LastFrameR, camera))
        if(Convert::ConvertMatToArray(LastFramet, t)) return true;
    return false;
}

bool Convert::GetR_t_Current(double *camera, double *t) {
    if(!initialize) return false;
    if(Convert::ConvertMatToArray(CurrentFrameR, camera))
        if(Convert::ConvertMatToArray(CurrentFramet, t)) return true;
    return false;
}

//template<typename DataType>
//bool Convert::Convert2Dto3D(cv::KeyPoint &p, DataType *P, DataType &depth) {
//    const DataType u = p.pt.x, v = p.pt.y;
//    DataType x, y, z=depth;
//    x = (u-BundleAdjustmentCostFunction::get_cx()) * z * BundleAdjustmentCostFunction::get_fx_inv();
//    y = (v - BundleAdjustmentCostFunction::get_cy()) * z * BundleAdjustmentCostFunction::get_fy_inv();
//    cv::Mat_<DataType> _(3, 1);
//    _.at(0, 0) = x;_.at(1,0)=y;_.at(2,0)=z;
//    std::cout<<"_.type ===>"<<_.type()<<std::endl;
//    if(_.type()!= LastFrameR.type()) return false;
//    cv::Mat temp = LastFrameR.t() * (_ - LastFramet);
//    if(Convert::ConvertMatToArray(temp, P))
//        return true;
//    return false;
//
//}

bool Convert::Convert2Dto3D(cv::KeyPoint &p, double *P, double &depth) {
    const double u = p.pt.x, v = p.pt.y;
    double x, y, z=depth;
    x = (u-BundleAdjustmentCostFunction::get_cx()) * z * BundleAdjustmentCostFunction::get_fx_inv();
    y = (v - BundleAdjustmentCostFunction::get_cy()) * z * BundleAdjustmentCostFunction::get_fy_inv();
    cv::Mat _(3, 1, CV_64F);
    _.at<double>(0, 0) = x;_.at<double>(1,0)=y;_.at<double>(2,0)=z;
    if(_.type()!= LastFrameR.type()) return false;
    cv::Mat temp = LastFrameR.t() * (_ - LastFramet);
    if(Convert::ConvertMatToArray(temp, P)) return true;
    return false;

}

bool Convert::SetStaticMatrix(cv::Mat &LTcw, cv::Mat &CTcw) {
    LTcw.copyTo(LastFrameTcw);
    CTcw.copyTo(CurrentFrameTcw);
    LTcw.rowRange(0, 3).colRange(0,3).copyTo(LastFrameR);
    LTcw.rowRange(0, 3).col(3).copyTo(LastFramet);
    CTcw.rowRange(0, 3).colRange(0, 3).copyTo(CurrentFrameR);
    CTcw.rowRange(0, 3).col(3).copyTo(CurrentFramet);
    initialize = true;
}


cv::Mat Convert::LastFrameTcw = cv::Mat::zeros(4, 4, CV_64F);
cv::Mat Convert::LastFrameR = cv::Mat::zeros(3, 3, CV_64F);
cv::Mat Convert::LastFramet = cv::Mat::zeros(3, 1, CV_64F);

cv::Mat Convert::CurrentFrameTcw = cv::Mat::zeros(4, 4, CV_64F);
cv::Mat Convert::CurrentFrameR = cv::Mat::zeros(3, 3, CV_64F);
cv::Mat Convert::CurrentFramet = cv::Mat::zeros(3, 1, CV_64F);
bool Convert::initialize=false;