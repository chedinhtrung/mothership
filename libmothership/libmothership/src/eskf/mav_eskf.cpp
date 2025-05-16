#include "mav_eskf.h"
#include "BasicLinearAlgebra/BasicLinearAlgebra.h"
/*

Based on Joan Sola Quaternion Kinematics for the error-state Kalman filter

*/ 

typedef struct State {
    Vector3D p; 
    Vector3D v; 
    Vector3D ab;    // Accelerometer bias
    Vector3D gb;    // Gyroscope bias
    Quaternion q;   // Drone orientation
    Vector3D g;     // gravity vector
};

typedef struct StateVec {
    BLA::Matrix<3,3> mat;
}; 
