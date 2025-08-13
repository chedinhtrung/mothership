#ifndef ALT
#define ALT 
#include "Arduino.h"

#define DPS310ADDR 0x76

class Altimeter {
    public: 
    float initial = 0.0;
    void get_initial();
    virtual float read();
};

class Dps310Altimeter : public Altimeter { 
    public:
        int16_t c0, c1, c01, c11, c20, c21, c30;
        int32_t c00, c10;
        int16_t raw_alt = 0;         // 16 bit value for data collection

        void setup();
        void get_calibrations();
        float read();
};

#endif