#include "dataexchange.h"
#include <cstring>
#include <iostream>

/*
Serialized Message structure: 

| StartByte | len | type | source | --- Payload --- | Checksum |
    1B         1B    1B      2B          len             1B

valid is not serialized, hence not considered in Message::get_payload_len()
*/

int serialize(uint8_t* &buf, Message &m){
    // Serialize without a startbyte, for network transport
    int len = m.len;
    int payload_len = m.get_payload_len();

    buf = (uint8_t*)malloc(len);
    
    uint8_t* buf0 = buf;
    memcpy(buf, &m.len, sizeof(MSG_LEN_TYPE)); buf += sizeof(MSG_LEN_TYPE);
    memcpy(buf, &m.type, sizeof(MessageType)); buf += sizeof(MessageType);
    memcpy(buf, &m.source, sizeof(MessageSource)); buf += sizeof(MessageSource);
    
    memcpy(buf, m.payload, payload_len); buf += payload_len;
    uint8_t checksum = 0;
    for (uint8_t* ptr = buf0; ptr < buf0 + len - sizeof(CHECKSUM_TYPE); ptr++){
        checksum ^= *ptr;
    }; 
    m.checksum = checksum;
    memcpy(buf, &m.checksum, sizeof(CHECKSUM_TYPE)); buf += sizeof(CHECKSUM_TYPE);
    buf -= len;
    return len; // Returns the actual length of the buffer 
}

int serialize_uart(uint8_t* &buf, Message &m){
    int len = m.len;
    int payload_len =  m.get_payload_len();

    buf = (uint8_t*)malloc(len + 1);
    *buf = UART_STARTBYTE;
    buf++;
    uint8_t* buf0 = buf;
    memcpy(buf, &m.len, sizeof(MSG_LEN_TYPE)); buf += sizeof(MSG_LEN_TYPE);
    memcpy(buf, &m.type, sizeof(MessageType)); buf += sizeof(MessageType);
    memcpy(buf, &m.source, sizeof(MessageSource)); buf += sizeof(MessageSource);
    
    memcpy(buf, m.payload, payload_len); buf += payload_len;
    uint8_t checksum = 0;
    for (uint8_t* ptr = buf0; ptr < buf0 + len - sizeof(CHECKSUM_TYPE); ptr++){
        checksum ^= *ptr;
    }; 
    m.checksum = checksum;
    memcpy(buf, &m.checksum, sizeof(CHECKSUM_TYPE)); buf += sizeof(CHECKSUM_TYPE);
    buf -= (len + 1);
    return len + 1; // Returns the actual length of the buffer 
}

// Message len = length when serialized

Message::Message(NavPayload pl){
    type = M_NAV;
    len = sizeof(Message) - sizeof(uint8_t*) - sizeof(bool) + sizeof(NavPayload);
    payload = (uint8_t*)malloc(sizeof(NavPayload));
    memcpy(payload, &pl, sizeof(NavPayload));
}

Message::Message(FlightDispPayload pl){
    type = M_FLIGHTDISP;
    len = sizeof(Message) - sizeof(uint8_t*) - sizeof(bool) + sizeof(FlightDispPayload);
    payload = (uint8_t*)malloc(sizeof(FlightDispPayload));
    memcpy(payload, &pl, sizeof(FlightDispPayload));
}

Message::~Message(){
    // WARNING: Double deletion danger!
    delete payload;
    payload = nullptr;
}

MSG_LEN_TYPE Message::get_payload_len(){
    return len - sizeof(Message) + sizeof(bool) + sizeof(uint8_t*);
}

bool parse(Message &m, uint8_t data){
    static int M_PARSE_BYTECOUNT = 0;
    static uint8_t M_PARSE_SUM = 0;
    static int M_PARSE_STEP = 0;
    MSG_LEN_TYPE payload_len;
    switch (M_PARSE_STEP){
        case 0:
            if (data == UART_STARTBYTE){
                M_PARSE_STEP++;
                return 0;
            }
        case 1: 
            memcpy(&m.len + M_PARSE_BYTECOUNT, &data, 1);
            M_PARSE_BYTECOUNT++; M_PARSE_SUM ^= data;
            if (M_PARSE_BYTECOUNT == 2){
                M_PARSE_BYTECOUNT = 0;
                M_PARSE_STEP++;
            } 
            return 0;
            
        case 2: 
            m.type = (MessageType)data; M_PARSE_SUM ^= data;
            M_PARSE_STEP++;
            return 0;

        case 3: 
            m.source = (MessageSource)data; M_PARSE_SUM ^= data;
            M_PARSE_STEP++;
            return 0;
    
        case 4: 
            payload_len = m.get_payload_len();
            if (M_PARSE_BYTECOUNT == 0){
                m.payload = (uint8_t*)malloc(payload_len);
            }
            memcpy(m.payload + M_PARSE_BYTECOUNT, &data, 1);
            M_PARSE_BYTECOUNT += 1; M_PARSE_SUM ^= data;
            if (M_PARSE_BYTECOUNT == payload_len){
                M_PARSE_STEP++;
                M_PARSE_BYTECOUNT = 0;
            }
            return 0;
        
        case 5:
            m.checksum = data;
            M_PARSE_BYTECOUNT = 0;
            M_PARSE_STEP = 0;
            // Checksum
            bool isvalid;
            isvalid = M_PARSE_SUM == m.checksum; 
            M_PARSE_SUM = 0;
            m.valid = isvalid;
            return isvalid;
        
        default: 
            return 0;
    }
}


