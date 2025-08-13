#ifndef IMU
#define IMU

#include <Arduino.h>

#define ADDR_9250 0x68      // Address of MPU9250/MPU6050

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
};

class Imu {
    public:  
        ImuData offset; 
        void setup();
        ImuData read();
        void calibrate_gyro();

        RawImuData raw_accels;
        RawImuData raw_gyros;      // Save raw values for reporting/debugs
};

class Mpu9250 {

};


#endif