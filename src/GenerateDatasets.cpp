//
// Created by simmons on 5/31/23.
//

#include<ctime>
#include <iostream>
#include <GenerateDataests.h>
#include <fstream>
#include <random>
#include <chrono>
Datasets::Datasets(int nums, double m, double c, bool save): miDataNums(nums), mFunction(m, c), bSave(save) {
    Generate();
    if (bSave){
        std::cout<<"starting to save generated datasets\n";
        SaveDatasets();
        std::cout<<"generated successfully\n";
    }
};

void Datasets::GetDatasets(std::vector<double> &datasets){
    for(int i=0; i<miDataNums; i++){
        datasets.push_back(mXDatasets[i]);
        datasets.push_back(mYDatasets[i]);
    }
};
double Datasets::getX(int index) {
    return mXDatasets[index];
}

double Datasets::getY(int index){
    return mYDatasets[index];
}

bool Datasets::Generate() {
    for(int i=0; i<miDataNums; i++){
        double x = i*xtics - 15;
//        std::cout<<"x ===> "<<x<<std::endl;
        double y = 0;
        if(mFunction(x, y)) {
            mXDatasets.push_back(x+noise());
            mYDatasets.push_back(y+noise());
//            std::cout<<"input _x ===> "<<x<<" input _y ===> "<<y<<std::endl;
        }
    }
    return true;
}

double Datasets::generate_random_number() {
    std::random_device e;
    std::uniform_real_distribution<double> n(0, 100);
    return double(n(e));
}

bool Datasets::SaveDatasets() {
    std::ofstream File;
    File.open("datasets.txt", std::ios::out |std::ios::trunc);
    if(File.is_open()){
        File<<"# generated datasets\n"<<"# x   y"<<"\n";
        for(int i=0;i<miDataNums;i++){
            File<<mXDatasets[i]<<"    "<<mYDatasets[i]<<"\n";
        }
        File.close();
        return true;
    }
    std::cout<<"build file failed"<<std::endl;
    return false;
}

bool Datasets::SaveResult(double m, double c){
    std::ofstream File;
    File.open("parameter.txt", std::ios::out |std::ios::trunc);
    if(File.is_open()){
        File<<"m="<<m<<"\n";
        File<<"c="<<c<<"\n";
        std::cout<<"save optimization result successfully"<<std::endl;
        return true;
    }
    std::cout<<"save optimization result failed"<<std::endl;
    return false;
}


double Datasets::noise() {
    std::random_device d;
    std::normal_distribution<double> n(0, 0.1);
    return double(n(d));
}
