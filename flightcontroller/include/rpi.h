#ifndef RPICOM
#define RPICOM

#include <Arduino.h>

#define RPI_SERIAL Serial4
#include "dataexchange.h"

// Class to communicate with Pi, using common data exchange formats

class Rpi { 
    public:
        void send(Message m);      // serialize a message, send over serial
        bool recv(Message &m);     // read 1 byte from serial and parse. returns true when parse is complete.
};

#endif 