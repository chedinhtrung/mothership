#include "compass.h"

void Magnetometer::setup(){
    // Set reset interval (according to datasheet)
    Wire.beginTransmission(MAGADDR0);
    Wire.write(0x0B);
    Wire.write(0x01);
    Wire.endTransmission();
    delay(20);
    Wire.beginTransmission(MAGADDR0);
    Wire.write(0x09);
    Wire.write(0x0D);       // 2 Gauss resolution, 200Hz reading rate, continuous mode
    Wire.endTransmission();
    delay(20);
}

RawImuData Magnetometer::read_raw(){
    Wire.beginTransmission(MAGADDR0);
    Wire.write(0x00);
    Wire.endTransmission();
    Wire.requestFrom(MAGADDR0, 6);

    RawImuData data;
    data.x = Wire.read() | Wire.read()<<8;
    data.y = Wire.read() | Wire.read()<<8;
    data.z = Wire.read() | Wire.read()<<8;
    return data;
}

float Magnetometer::read_compensated_heading(EulerTrigonometryCache c){
    RawImuData field = read_raw();
    ConvertedImuData cf = {
        .x = (field.x - offset.x)/scale.x,
        .y = (field.y - offset.y)/scale.y,
        .z = (field.z - offset.z)/scale.z,
    };
    
    float m_x = cf.x*c.cos_theta + cf.y*c.sin_theta*c.sin_phi + cf.z*c.sin_theta*c.cos_phi;
    float m_y = cf.y*c.cos_phi - cf.z*c.sin_phi;
    
    float heading = -1.0;
    if (m_y > 0){
        heading = 270.0 + atan(m_x/m_y) * 180/M_PI + DECLINE;
    } else if (m_y < 0){
        heading = 90.0 + atan(m_x/m_y) * 180/M_PI + DECLINE; 
    }
    if (m_y == 0 && m_x >= 0){
        return 180.0 + DECLINE;
    } else if (m_y == 0 && m_x < 0){
        return 0.0 + DECLINE;
    }
    if (heading >= 360){heading -= 360;}
    return heading;
}

void Magnetometer::calibrate(){
    int16_t max_x=-32000, max_y=-32000, max_z=-32000;
    int16_t min_x=32000, min_y=32000, min_z=32000;

    // read every 20ms (50Hz), for total of 3 minutes
    Serial.println("Calibration begins in 5s");
    delay(5000);

    Serial.println("Calibration begin");
    for (int i=0; i<3*60*100; i++){
        RawImuData raw = read_raw();
        max_x = max(max_x, raw.x);
        max_y = max(max_y, raw.y);
        max_z = max(max_z, raw.z);
        min_x = min(min_x, raw.x);
        min_y = min(min_y, raw.y);
        min_z = min(min_z, raw.z);
        delay(20);
    }
    Serial.println("Calibration end");

    Serial.printf("Max: %i, %i, %i, Min: %i, %i, %i", 
                    max_x, max_y, max_z,
                    min_x, min_y, min_z);

}