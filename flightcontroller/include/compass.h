#ifndef COMPASS
#define COMPASS
#define MAGADDR0 0x0D // I2C address of QMC5883L magnetometer on the GEPRC M10DQ
#include "Wire.h"
#include "imu.h"

class Magnetometer { 
    public:
        void setup();
        float read_compensated_heading(ConvertedImuData correction);
        ConvertedImuData read_magneto();
};

#endif