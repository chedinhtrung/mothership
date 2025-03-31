#include "dataexchange.h"
#include <iostream>
#include <cstring> 

int main() {
    
    // Test message format
    NavPayload payload;
    payload.heading = 1000;
    payload.lat = 10;
    payload.lon = 10;

    Message m(payload);

    std::cout << "message length " << m.len << "\n";
    NavPayload decoded_payload;
    memcpy(&decoded_payload, m.payload, sizeof(NavPayload));
    printf("Decoded payload heading:%i, lat:%f, lon:%f \n", 
        decoded_payload.heading, decoded_payload.lat, decoded_payload.lon);

    // Test message serialization
    std::cout << "Serializing \n";
    uint8_t* buf;
    int len = serialize_uart(buf, m);
    std::cout << "Total len:" << len << "\n";  //payload = 10B, type = 1B, source = 1B, len = 2B, checksum = 1B => 15B 
    
    // Test parsing
    Message new_msg;
    bool valid = false;
    for (uint8_t* ptr = buf; ptr < buf+len; ptr++){
        valid = parse(new_msg, *ptr);
    } 
    if (!valid){
        std::cout << "Invalid msg";
        return 1;
    }
    printf("Len: %i, Type: %i, Source: %i, ", 
            m.len, m.type, m.source);
    NavPayload new_nav;
    unsigned int payload_len =  new_msg.get_payload_len();
    std::cout<< "Payload len: " << payload_len;
    
    memcpy(&new_nav, new_msg.payload, payload_len);
    printf("lon: %f, lat: %f, head: %i", new_nav.lon, new_nav.lat, new_nav.heading);
    
    
    return 0;
}