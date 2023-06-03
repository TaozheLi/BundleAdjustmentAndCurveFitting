//
// Created by simmons on 6/1/23.
//

#include "BundleAdjustmentCostFunction.h"

#define PRINT(x) std::cout<<x<<std::endl

template<typename DataType, typename DataType2>
BundleAdjustmentCostFunction<DataType, DataType2>::BundleAdjustmentCostFunction(DataType observation_x, DataType observation_y): obj_x(observation_x), obj_y(observation_y){

}

//BundleAdjustmentCostFunction::BundleAdjustmentCostFunction(double observation_x, double observation_y): obj_x(observation_x), obj_y(observation_y){
//
//}
template<typename DataType, typename DataType2>
void BundleAdjustmentCostFunction<DataType, DataType2>::set_static_member(DataType fx, DataType fy, DataType cx, DataType cy) {
    mfx = fx;
    mfy = fy;
    mcx = cx;
    mcy = cy;
    mfx_inv = 1.0/fx;
    mfy_inv = 1.0/fy;
}

//void BundleAdjustmentCostFunction<DataType>::set_static_member(double fx, double fy, double cx, double cy) {
//    mfx = fx;
//    mfy = fy;
//    mcx = cx;
//    mcy = cy;
//    mfx_inv = 1.0/fx;
//    mfy_inv = 1.0/fy;
//}


//double BundleAdjustmentCostFunction::mfx = 0;
//double BundleAdjustmentCostFunction::mfy = 0;
//double BundleAdjustmentCostFunction::mfx_inv = 1;
//double BundleAdjustmentCostFunction::mfy_inv = 1;
//double BundleAdjustmentCostFunction::mcx = 0;
//double BundleAdjustmentCostFunction::mcy = 0;

template<typename DataType, typename DataType2>
DataType BundleAdjustmentCostFunction<DataType, DataType2>::mfx = 0;
template<typename DataType, typename DataType2>
DataType BundleAdjustmentCostFunction<DataType, DataType2>::mfy = 0;
template<typename DataType, typename DataType2>
DataType BundleAdjustmentCostFunction<DataType, DataType2>::mfx_inv = 1;
template<typename DataType, typename DataType2>
DataType BundleAdjustmentCostFunction<DataType, DataType2>::mfy_inv = 1;
template<typename DataType, typename DataType2>
DataType BundleAdjustmentCostFunction<DataType, DataType2>::mcx = 1;
template<typename DataType, typename DataType2>
DataType BundleAdjustmentCostFunction<DataType, DataType2>::mcy = 1;

