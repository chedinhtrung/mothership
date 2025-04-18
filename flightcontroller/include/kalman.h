#ifndef KALMAN
#define KALMAN

#include <BasicLinearAlgebra.h>
#include "imu.h"

using namespace BLA;

#define GPS_UPDATE_RATE 10

/*
    Reference: Dan Simon Optimal State Estimations, p.409

    Q: Covariance of process noise 
    R: Covariance of measurement noise
    P: Covariance of estimation error

*/

class AttitudeKalman {
    public:
        BLA::Matrix<3,1,float> x = {0.0, 0.0, 0.0}; // Yaw, Pitch, Roll in that order
        BLA::Matrix<3,3,float> Q = {     // rotation rate integration accurate to 0.005 degrees
            1e-8, 0.0f, 0.0f,
            0.0f, 1e-8, 0.0f,
            0.0f, 0.0f, 1e-8
        }; 
        BLA::Matrix<3,3,float> R = {     // Covariance of 0.1g ^ 2
            0.01f, 0.0f, 0.0f,
            0.0f, 0.01f, 0.0f,
            0.0f, 0.0f, 0.01f
        };
        BLA::Matrix<3,3,float> P = {    // Covariance of 2 degrees^2, to radian 
            1.22e-3, 0.0f, 0.0f,
            0.0f, 1.22e-3, 0.0f,
            0.0f, 0.0f, 1.22e-3
        };
        BLA::Matrix<3,3,float> K;
        //BLA::Matrix<3,3,float> F;  F is unnecessary, since F = Identity
        //BLA::Matrix<3,3,float> L;  L = Identity (not sure, could be beneficial to model)
        BLA::Matrix<3,3,float> H = {
            0.0, 0.0, 0.0,
            0.0, 0.0, 0.0,
            0.0, 0.0, 0.0
        };
        //BLA::Matrix<3,3,float> M;      // M = Identity
        BLA::Matrix<3,1,float> h = {0, 0, 0};
        AttitudeKalman();
        void predict(ConvertedImuData gyros);
        void update_roll_pitch(ConvertedImuData accels);
        void update_heading(ConvertedImuData magneto);
        ConvertedImuData read_euler();

        // cache values
        float sin_phi, cos_phi, sin_theta, cos_theta;
        EulerTrigonometryCache get_euler_trigs();
};

class PositionKalman {
    public:
        PositionKalman();
        void predict(ConvertedImuData accels);
        //void update_pos(LonLat lonlat);
        //void update_vel(ConvertedImuData flows);
        //void update_alt(float alt);
};

#endif