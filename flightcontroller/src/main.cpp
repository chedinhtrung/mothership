#include <Arduino.h>
#include <Wire.h>
#include "imu.h"
#include "kalman.h"
#include "debugger.h"
#include "utils.h"
#include "opticalflow.h"
#include "dps310.h"
#include "rpi.h"
#include "compass.h"

Imu imu = Imu();
AttitudeKalman attitude_kf = AttitudeKalman();
OpticalFlow of = OpticalFlow();
Dps310Altimeter alt = Dps310Altimeter();
Rpi pi;
Magnetometer mag = Magnetometer();


void setup(){
    // Start comm
    Serial.begin(115200);   // Serial debug
    Wire.begin();
    Wire.setClock(400000);  // High speed i2c with imu, altimeter, magnetometer
    //mag.calibrate();
    delay(4000);
    //mag.calibrate();
    // Setup imu: Subtract gyro static bias
    imu.setup();
    delay(100);
    mag.setup();
    delay(100);

    // Setup altimeter: Get calibration terms, get start alt
    alt.setup();
}

unsigned long last_mainloop_update;
unsigned long last_compass; 

void loop(){
    if (micros() - last_mainloop_update > DT*1e3){
        last_mainloop_update = micros();
        ImuData data = imu.read();
        attitude_kf.predict(data.gyro);
        attitude_kf.update_roll_pitch(data.accel);
        ConvertedImuData euler = attitude_kf.read_euler();
        
    }

    if (millis() - last_compass > 40){
        last_compass = millis();
        float heading = mag.read_compensated_heading(attitude_kf.get_euler_trigs());
        
        /*
        Serial.printf("Heading: %f", heading);
        Serial.println();
        */
       Serial.printf("r %f p %f y %f iy %f \n", attitude_kf.x(0,0)/PI*180, attitude_kf.x(1,0)/PI*180, attitude_kf.x(2,0)/PI*180);
    }
    
}

void serialEvent3(){
    if (of.micolink_decode((uint8_t)OF_SERIAL.read())) {
        /*
        Serial.printf("h: %i, fx: %i, fy: %i, qf: %i", of.payload.distance, of.payload.flow_vel_x, 
                        of.payload.flow_vel_y, of.payload.flow_quality);
        Serial.println();
        */
    };
}