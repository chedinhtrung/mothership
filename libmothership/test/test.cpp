#include "dataexchange.h"
#include <iostream>
#include <cstring> 

int main() {
    
    // Test message format
    Message m;
    m.type = M_NAV;
    m.source = DRONE;
    m.payload_len = sizeof(NavPayload);
    m.payload = (uint8_t*)malloc(sizeof(NavPayload));
    NavPayload payload;
    payload.heading = 1000;
    payload.lat = 10;
    payload.lon = 10;
    memcpy(m.payload, &payload, sizeof(NavPayload));

    std::cout << "payload length " << m.payload_len << "\n";
    NavPayload decoded_payload;
    memcpy(&decoded_payload, m.payload, sizeof(NavPayload));
    printf("Decoded payload heading:%i, lat:%f, lon:%f \n", 
        decoded_payload.heading, decoded_payload.lat, decoded_payload.lon);

    // Test message serialization
    SerializedMessage sm = serialize(m);
    std::cout << "Total len:" << sm.total_len << "\n";  //payload = 10B, type = 1B, source = 1B, len = 2B, checksum = 2B => 16B 
    uint8_t mtype; 
    memcpy(&mtype, sm.buf, sizeof(uint8_t));
    printf("Type %i, Source %i, Len: %i \n", *sm.buf, *(sm.buf+1), *(sm.buf+2));     // Expected: NAV = 4

    // Test deserialization
    NavPayload deserialized_payload;
    uint8_t* payload_ptr = sm.buf + sizeof(MessageType) + sizeof(MessageSource) + sizeof(uint16_t);
    memcpy(&deserialized_payload, payload_ptr, sizeof(NavPayload));
    printf("Deserialized payload heading:%i, lat:%f, lon:%f \n", 
            deserialized_payload.heading, deserialized_payload.lat, deserialized_payload.lon);     

    // Test message deserialization using deserializer
    MsgParser parser;
    parser.parse(UART_STARTBYTE);       // Needs startbyte
    bool valid = parser.parse(sm.buf, sm.total_len);
    NavPayload parsed_payload;
    if (valid){
        std::cout << "Parsed: \n";
        printf("Type: %i, Source: %i, Len: %i", parser.msg.type, parser.msg.source, parser.msg.payload_len);
        memcpy(&parsed_payload, parser.msg.payload, sizeof(NavPayload));
        printf("Using parser heading:%i, lat:%f, lon:%f \n", 
        parsed_payload.heading, parsed_payload.lat, parsed_payload.lon);  
    } else { 
        std::cout << "invalid msg, stopped at " << (int)parser.status << "\n";
        printf("Type: %i, Source: %i, Len: %i", parser.msg.type, parser.msg.source, parser.msg.payload_len);
        memcpy(&parsed_payload, parser.msg.payload, sizeof(NavPayload));
        printf("Using parser heading:%i, lat:%f, lon:%f \n", 
        parsed_payload.heading, parsed_payload.lat, parsed_payload.lon);  
    }

    return 0;
}