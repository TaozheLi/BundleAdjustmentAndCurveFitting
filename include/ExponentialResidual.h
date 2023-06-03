//
// Created by simmons on 5/31/23.
//

#ifndef BUNDLEADJUSTMENTWITHVISUALIZATION_EXPONENTIALRESIDUAL_H
#define BUNDLEADJUSTMENTWITHVISUALIZATION_EXPONENTIALRESIDUAL_H



class ExponentialResidual{
public:
    template<typename DataType>
    ExponentialResidual(DataType x, DataType y):x_(x), y_(y){
    }

    template<typename DataType>
    bool operator()(const DataType * const m, const DataType * const c, DataType * residual) const{
        residual[0] = y_ - exp(x_ * m[0] + c[0]);
        return true;
    }
private:
    double x_;
    double y_;
};

#endif //BUNDLEADJUSTMENTWITHVISUALIZATION_EXPONENTIALRESIDUAL_H