#ifndef COMPASS
#define COMPASS
#define MAGADDR0 0x0D // I2C address of QMC5883L magnetometer on the GEPRC M10DQ
#include "Wire.h"
#include "imu.h"
#include <BasicLinearAlgebra.h>

#define DECLINE 4.25

class Magnetometer { 
    public:
        void setup();
        float read_compensated_heading(EulerTrigonometryCache c);
        RawImuData read_raw();
        void calibrate();

        // calibration
        ConvertedImuData offset = {
            .x = (4595.0 + (-6477.0))/2.0,
            .y = (8015.0 + (-3100.0))/2.0,
            .z = (6387.0 + (-5097.0))/2.0
        };
        ConvertedImuData scale = {
            .x = (4595.0 - (-6477.0))/2.0,
            .y = (8015.0 - (-3100.0))/2.0,
            .z = (6387.0 - (-5097.0))/2.0
        };
};

#endif