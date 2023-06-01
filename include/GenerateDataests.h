//
// Created by simmons on 5/31/23.
//

#ifndef BUNDLEADJUSTMENTWITHVISUALIZATION_GENERATEDATAESTS_H
#define BUNDLEADJUSTMENTWITHVISUALIZATION_GENERATEDATAESTS_H

#endif //BUNDLEADJUSTMENTWITHVISUALIZATION_GENERATEDATAESTS_H
#include <math.h>
#include <vector>
/** exponential function
 *
 */
struct function_exponential{
public:
    function_exponential(double m, double c):m_(m), c_(c){}

    bool operator()(double &x, double &y){
        y = exp(x*m_ + c_);
        return true;
    }

private:
    double m_, c_;
};

class Datasets{
public:
    Datasets(int nums, double m, double c, bool save=false);
    bool Generate();
    void GetDatasets(std::vector<double> &datasets);
    double getX(int index);
    double getY(int index);
    bool SaveResult(double m, double c);

private:
    bool bSave;
    int miDataNums;
    double xtics=0.01;
    struct function_exponential mFunction;
    std::vector<double> mXDatasets;
    std::vector<double> mYDatasets;

    /** function for generating noise
     *
     * @return Noise
     */
    double noise();

    double generate_random_number();

    bool SaveDatasets();

};