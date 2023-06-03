cmake_minimum_required(VERSION 2.8)
project(BundleAdjustmentWithVisualization)

set(CMAKE_CXX_STANDARD 17)
find_package(Pangolin REQUIRED)

include_directories(include)

find_package(Ceres REQUIRED)

find_package(OpenCV REQUIRED)

find_package(CUDA REQUIRED)

include_directories(${Pangolin_INCLUDE_DIRS} ${OpenCV_DIRS})

add_library(${PROJECT_NAME} SHARED
src/BundleAdjustmentCostFunction.cpp
src/GenerateDatasets.cpp
src/Convert.cpp
include/BundleAdjustmentCostFunction.h
include/ExponentialResidual.h
include/GenerateDataests.h
include/Convert.h)

target_link_libraries(
${PROJECT_NAME}
${OpenCV_LIBS}
${Pangolin_LIBRARIES}
${Ceres_LIBRARIES}
Ceres::ceres
)

add_executable(curve_fitting Examples/curve_fitting.cpp)
#target_link_libraries(curve_fitting ${Pangolin_LIBRARIES} ${Ceres_LIBRARIES} Ceres::ceres ${OpenCV_LIBRARIES})
target_link_libraries(curve_fitting ${PROJECT_NAME})

add_executable(BundleAdjustment Examples/BundleAdjustmentOnBALDataset.cpp)
#target_link_libraries(BundleAdjustment ${Pangolin_LIBRARIES} ${Ceres_LIBRARIES} Ceres::ceres ${OpenCV_LIBRARIES})
target_link_libraries(BundleAdjustment ${PROJECT_NAME})
