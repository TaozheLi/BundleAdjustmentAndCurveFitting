//
// Created by simmons on 6/1/23.
//

#include "BundleAdjustmentCostFunction.h"

#define PRINT(x) std::cout<<x<<std::endl


BundleAdjustmentCostFunction::BundleAdjustmentCostFunction(double observation_x, double observation_y): obj_x(observation_x), obj_y(observation_y){

}


void BundleAdjustmentCostFunction::set_static_member(double fx, double fy, double cx, double cy) {
    mfx = fx;
    mfy = fy;
    mcx = cx;
    mcy = cy;
    mfx_inv = 1.0/fx;
    mfy_inv = 1.0/fy;
}


double BundleAdjustmentCostFunction::mfx = 0;
double BundleAdjustmentCostFunction::mfy = 0;
double BundleAdjustmentCostFunction::mfx_inv = 1;
double BundleAdjustmentCostFunction::mfy_inv = 1;
double BundleAdjustmentCostFunction::mcx = 0;
double BundleAdjustmentCostFunction::mcy = 0;


