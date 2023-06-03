//
// Created by simmons on 6/1/23.
//


#include <opencv2/opencv.hpp>
#include <ceres/ceres.h>
#include <ceres/rotation.h>
class BundleAdjustmentCostFunction{
public:
    BundleAdjustmentCostFunction(double observation_x, double observation_y);
    template<typename DataType>
    bool operator()(const DataType * const camera,  const DataType * const point,
                    DataType * e) const{
        /**Pinhole Model
         *
         */

        DataType p[3];
        ceres::AngleAxisRotatePoint(camera, point, p);
        p[0] += camera[3]; p[1]+=camera[4]; p[2]+=camera[5];
        DataType x = p[0] / p[2];
        DataType y = p[1] / p[2];
        const DataType prediction_x = x * DataType(mfx) + DataType(mcx);
        const DataType prediction_y = y * DataType(mfy) + DataType(mcy);
        e[0] = DataType(obj_x) - prediction_x;
        e[1] = DataType(obj_y) - prediction_y;
        return true;
    }

    void static set_static_member(double fx, double fy, double cx, double cy);

    inline double static get_fx(){
        return mfx;
    }
    inline double static get_fy(){
        return mfy;
    }
    inline double static get_cx(){
        return mcx;
    }
    inline double static get_cy(){
        return mcy;
    }
    inline double static get_fx_inv(){
        return mfx_inv;
    }
    inline double static get_fy_inv(){
        return mfy_inv;
    }
private:
    static double mfx, mfy,  mcx, mcy, mfx_inv, mfy_inv;
    double obj_x, obj_y;
};





