//
// Created by simmons on 5/31/23.
//
#include <thread>
#include <iostream>
#include <ceres/ceres.h>
#include <vector>
#include "ExponentialResidual.h"
#include "GenerateDataests.h"


/** make a solution for a curve-fitting problem
 * */

int main(){
    int N = 2000;
    double answer_m=1.0, answer_c=0.0;
    Datasets Datasets(N, answer_m , answer_c, true);
    double initial_m=0, initial_c=0;
    double m = initial_m, c = initial_c;
    std::vector<double>datasets;
    Datasets.GetDatasets(datasets);
    ceres::Problem problem;
    for(int i=0; i<datasets.size()/2; i++){
        double x = Datasets.getX(i);
        double y = Datasets.getY(i);
//        std::cout<<"x: "<<x<<" y: "<<y<<std::endl;
        ceres::CostFunction * costFunction = new ceres::AutoDiffCostFunction<ExponentialResidual, 1, 1, 1>(new ExponentialResidual(x, y));
        problem.AddResidualBlock(costFunction, nullptr, &m, &c);
    }
    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);
    std::cout<< summary.BriefReport();
    std::cout<<"\nAfter Optimization:\nm "<<initial_m<<" ===> "<<m<<"\n"<<"c "<<initial_c<<" ===> "<<c<<std::endl;
    Datasets.SaveResult(m, c);
    return 0;
}