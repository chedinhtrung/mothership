#include "mav_eskf.h"
#include "BasicLinearAlgebra/BasicLinearAlgebra.h"
#include "msvector.h"
/*

Based on Joan Sola Quaternion Kinematics for the error-state Kalman filter

*/ 
struct State {
    MSVector3 p; 
    MSVector3 v; 
    MSVector3 ab;    // Accelerometer bias
    MSVector3 gb;    // Gyroscope bias
    Quaternion q;   // Drone orientation
    MSVector3 g;     // gravity vector
};

struct StateVec {
    BLA::Matrix<3,3> mat;
}; 
