#include "Arduino.h"
#include <Wire.h>

#include "config.h"
#include "sensor/imu.h"
#include "utils/debugger.h"
#include "quaternion.h"
#include "sensor/alt.h"

Mpu9250 imu;
Dps310Altimeter alt;

void setup(){
    Serial.begin(115200);   // Serial debug
    Wire.begin();
    Wire.setClock(400000);  // High speed i2c with imu, altimeter, magnetometer
    delay(4000);

    imu.setup();
    delay(100);
    
    alt.setup();
    delay(100);
}

unsigned long last_mainloop_update;

void loop(){
    if (micros() - last_mainloop_update > 100*1e3){
        float a = alt.read() + alt.initial;
        debug("alt", a);
    }
}