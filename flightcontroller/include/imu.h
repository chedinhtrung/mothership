#ifndef IMU 
#define IMU

#include "config.h"
#include <Arduino.h>

#define IMUADDR 0x68  // MPU6050/9250 I2C address

struct RawImuData {
    int16_t x = 0;
    int16_t y = 0;
    int16_t z = 0;
};

struct ConvertedImuData {
    float x = 0;
    float y = 0;
    float z = 0;
};

struct ImuData {
    ConvertedImuData accel;
    ConvertedImuData gyro;
    ConvertedImuData magneto;
};

struct EulerTrigonometryCache {
    float sin_phi = 0;
    float cos_phi = 0;
    float sin_theta = 0;
    float cos_theta = 0;
};

class Imu {
    public:  
        ImuData offset; 
        void setup();
        ImuData read();
        void calibrate_gyro();

        RawImuData raw_accels;
        RawImuData raw_gyros;
};

#endif 

