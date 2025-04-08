#include "rpi.h"

void Rpi::send(Message m){
    uint8_t buf[MSG_BUF_SIZE];
    int n_bytes = serialize(buf, m);
    Serial.printf("Serialized: %i", n_bytes);
}