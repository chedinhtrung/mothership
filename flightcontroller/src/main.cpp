#include <Arduino.h>
#include <Wire.h>
#include "imu.h"
#include "kalman.h"
#include "debugger.h"
#include "utils.h"
#include "opticalflow.h"
#include "dps310.h"
#include "rpi.h"

Imu imu = Imu();
AttitudeKalman attitude_kf = AttitudeKalman();
OpticalFlow of = OpticalFlow();
Dps310Altimeter alt = Dps310Altimeter();
Rpi pi;

void setup(){
    // Start comm
    Serial.begin(115200);   // Serial debug
    Wire.begin();
    Wire.setClock(400000);  // High speed i2c with imu, altimeter, magnetometer
    delay(4000);

    NavPayload npl;
    npl.lat = 10.0;

    Message m(npl);
    pi.send(m);

    NavPayload new_npl = m.get_data<NavPayload>();
    Serial.println();
    Serial.printf("payload recv: %f %f % i", new_npl.lat, new_npl.lon, new_npl.heading);

    // Setup imu: Subtract gyro static bias
    imu.setup();
    delay(100);

    // Setup altimeter: Get calibration terms, get start alt
    alt.setup();
}

unsigned long last_mainloop_update;

void loop(){
    if (micros()-last_mainloop_update < DT*1e3) {return;}
    last_mainloop_update = micros();
    ImuData data = imu.read();
    attitude_kf.predict(data.gyro);
    attitude_kf.update_roll_pitch(data.accel);
    ConvertedImuData euler = attitude_kf.read_euler();
    rad_to_deg(euler); 
    debug("euler:", euler);
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