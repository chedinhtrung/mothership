
#ifndef DEBUGGER
#define DEBUGGER
#include "sensor/imu.h"

void debug(const char* label, ConvertedImuData data);

void debug(const char* label, float fval);
#endif