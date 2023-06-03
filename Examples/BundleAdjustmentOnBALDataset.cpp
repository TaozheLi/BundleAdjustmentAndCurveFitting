//
// Created by simmons on 6/1/23.
//
#include "BundleAdjustmentCostFunction.h"
#include "opencv2/opencv.hpp"
#include <vector>
#include "ceres/ceres.h"
#include "Convert.h"
#include <chrono>

#define DataType float
#define PRINT(x) std::cout<<"x===>"<<x<<std::endl
int main() {
    std::vector<DataType> observationX;
    std::vector<DataType> observationY;
    int DSize = 2;
    cv::KeyPoint m;
    std::vector<cv::KeyPoint> S;
    for(int i=0; i<DSize; i++){
        m.pt.x = i;
        m.pt.y = i;
        S.push_back(m);
    }


    DataType fx = 1.5, fy = 20, cx = 11, cy = 15;
    BundleAdjustmentCostFunction<DataType, double>::set_static_member(fx, fy, cx, cy);

    cv::Mat_<DataType> C(4, 4);
    cv::Mat_<DataType> B(4,4);
    cv::randn(C, 0, 1);
    cv::randn(B, 0, 1);
    Convert::SetStaticMatrix(C, B);

    double points[2][3] = {{1, 10, 3}, {1, 20, 100}};

    double camera[6]={0.87, 0.56, 0.31, 0.5, 0.7, 0.8};
//    DataType t[3]= {1, 0.5, 2};
//    Convert::GetR_t_Last(camera, t);
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    ceres::Problem problem;
    for (int i = 0; i < 2; i++) {
        DataType depth = 30;
//        Convert::Convert2Dto3D(S[i], points[i], depth);
        ceres::CostFunction * costFunction = new ceres::AutoDiffCostFunction<BundleAdjustmentCostFunction<DataType, double>, 2, 6, 3>
                (new BundleAdjustmentCostFunction<DataType, double>(DataType(S[i].pt.x), DataType(S[i].pt.y)));
       problem.AddResidualBlock(costFunction, nullptr, camera, points[i]);
    }
    ceres::Solver::Options options;
    options.max_num_iterations = 10;
    options.linear_solver_type = ceres::DENSE_SCHUR;
    options.minimizer_progress_to_stdout = false;
//    options.dense_linear_algebra_library_type=ceres::CUDA;
    ceres::Solver::Summary summary;
    std::chrono::steady_clock::time_point t3 = std::chrono::steady_clock::now();
    ceres::Solve(options, &problem, &summary);
    std::chrono::steady_clock::time_point t4 = std::chrono::steady_clock::now();
    std::cout<<"time of optimize: "<<std::chrono::duration_cast<std::chrono::duration<double>>(t4 -t3).count()*1000<<std::endl;
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    DataType time = std::chrono::duration_cast<std::chrono::duration<DataType>>(t2 -t1).count();
    std::cout<<"process time ===>"<<time*1000<<std::endl;
//    std::cout << summary.BriefReport()<<std::endl;
   for(int i=0; i<3; i++){
        std::cout<<"camera:"<<i<<" ===> "<<camera[i]<<std::endl;
    }
//    for(int i=0; i<3; i++){
//        std::cout<<"translation:"<<i<<" ===> "<<t[i]<<"\n";
//   }
    for(int i=0; i<observationX.size(); i++){
        std::cout<<"point:"<<i<<"===>("<<points[i][0]<<", "<<points[i][1]<<", "<<points[i][2]<<")"<<std::endl;
    }
    return 0;
}
