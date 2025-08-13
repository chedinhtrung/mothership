#include "Arduino.h"
#include <Wire.h>

#include "config.h"
#include "sensor/imu.h"
#include "utils/debugger.h"

Mpu9250 imu;

void setup(){
    Serial.begin(115200);   // Serial debug
    Wire.begin();
    Wire.setClock(400000);  // High speed i2c with imu, altimeter, magnetometer
    delay(4000);

    imu.setup();
    delay(100);
}

unsigned long last_mainloop_update;

void loop(){
    if (micros() - last_mainloop_update > DT*1e3){
        last_mainloop_update = micros();
        ImuData data = imu.read();
        debug("gyro", data.gyro); 
    }
}