//
// Created by simmons on 6/1/23.
//
#include "BundleAdjustmentCostFunction.h"
#include "opencv2/opencv.hpp"
#include <vector>
#include "ceres/ceres.h"
#include "Convert.h"
#include <chrono>
#include "ceres/rotation.h"

#define DataType double
#define PRINT(x) std::cout<<"x===>"<<x<<std::endl
int main() {
    std::vector<DataType> observationX;
    std::vector<DataType> observationY;
    int DSize = 2000;
    cv::KeyPoint m;
    std::vector<cv::KeyPoint> S;
    for(int i=0; i<DSize; i++){
        m.pt.x = i;
        m.pt.y = i;
        S.push_back(m);
    }


    DataType fx = 1.5, fy = 20, cx = 11, cy = 15;
    BundleAdjustmentCostFunction::set_static_member(fx, fy, cx, cy);

//    cv::Mat C(3, 3, CV_64F);
    cv::Mat C = (cv::Mat_<double>(3,3)<<-0.036255, 0.978364, -0.203692, 0.998304, 0.026169, -0.051994, -0.045539, -0.205232, -0.97753);
    cv::Mat test_point_cv = (cv::Mat_<double>(3,1)<<1.5, 20, 67);
    std::cout<<test_point_cv<<std::endl;
    auto tr = cv::trace(C);
    double theta = acos((tr.val[0] - 1)/2);
    cv::Mat_<DataType> B(4,4);
//    cv::randn(C, 0, 1);
    cv::randn(B, 0, 1);
//    Convert::SetStaticMatrix(C, B);
    double mm[9], ll[3], changed_ll[3];
    Convert::ConvertMatToArray(C, mm);
    cv::Mat fnnn(3, 1, CV_64F);
    double cv_camera[6];

    std::chrono::steady_clock::time_point t_s_1 = std::chrono::steady_clock::now();
    for(int i=0; i<10000; i++) {
        Convert::ConvertMatToArray(C, mm);
        ceres::RotationMatrixToAngleAxis(mm, ll);
        for(int x=0; x<3; x++)
            changed_ll[x] = -ll[x];
    }
    std::chrono::steady_clock::time_point t_e_1 = std::chrono::steady_clock::now();
    std::cout<<"time of ceres: "<<std::chrono::duration_cast<std::chrono::duration<double>>(t_e_1 - t_s_1).count()*1000<<" ms"<<std::endl;

    std::chrono::steady_clock::time_point t_s_2 = std::chrono::steady_clock::now();
    double whole_time=0;
    for(int i=0; i<10000; i++){
        std::chrono::steady_clock::time_point t_s_3 = std::chrono::steady_clock::now();
        cv::Rodrigues(C, fnnn);
        std::chrono::steady_clock::time_point t_e_3 = std::chrono::steady_clock::now();
        whole_time += std::chrono::duration_cast<std::chrono::duration<double>>(t_e_3 - t_s_3).count()*1000;
        Convert::ConvertMatToArray(fnnn, cv_camera);
    }
    std::chrono::steady_clock::time_point t_e_2 = std::chrono::steady_clock::now();
    std::cout<<"time of rodrigues: "<<whole_time<<"ms \n";
    std::cout<<"time of cv: "<<std::chrono::duration_cast<std::chrono::duration<double>>(t_e_2 - t_s_2).count()*1000<<" ms"<<std::endl;
//    std::cout<<fnnn<<std::endl;
    // need a minus

    double test_point[3] = {1.5, 20, 67};
    double result[3];


    ceres::AngleAxisRotatePoint(changed_ll, test_point, result);
    for(int i=0; i<3; i++) std::cout<<result[i]<<std::endl;
    cv::Rodrigues(fnnn, C);
//    std::cout<<C*test_point_cv<<std::endl;
//    for(int i=0; i<3; i++) std::cout<<-ll[i]<<std::endl;
//    for(int i=0; i<3; i++) std::cout<<ll[i]<<std::endl;
    exit(-1);
    double points[DSize][3];

    double camera[6]={0.87, 0.56, 0.31, 0.5, 0.7, 0.8};
//    DataType t[3]= {1, 0.5, 2};
//    Convert::GetR_t_Last(camera, t);
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    ceres::Problem problem;
    for (int i = 0; i < DSize; i++) {
        double depth = 30;
        assert(Convert::Convert2Dto3D(S[i], points[i], depth));
        ceres::CostFunction * costFunction = new ceres::AutoDiffCostFunction<BundleAdjustmentCostFunction, 2, 6, 3>
                (new BundleAdjustmentCostFunction(DataType(S[i].pt.x), DataType(S[i].pt.y)));
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
