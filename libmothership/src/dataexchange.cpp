#include "dataexchange.h"
#include <cstring>
#include <iostream>

SerializedMessage serialize(Message m){
    const int total_len = sizeof(Message) - sizeof(uint8_t*) + m.payload_len;
    uint8_t* msg_buf = new uint8_t[total_len];
    uint8_t* msg_buf0 = msg_buf;
    memset(msg_buf, 0, total_len);
    memcpy(msg_buf, &m.type, sizeof(MessageType)); msg_buf += sizeof(MessageType);
    memcpy(msg_buf, &m.source, sizeof(MessageSource)); msg_buf += sizeof(MessageSource);
    memcpy(msg_buf, &m.payload_len, sizeof(uint16_t)); msg_buf += sizeof(uint16_t);
    memcpy(msg_buf, m.payload, m.payload_len); msg_buf += m.payload_len;
    // Calculate checksum
    uint8_t checksum = 0;
    for (uint8_t* ptr = msg_buf0; ptr < msg_buf0+total_len-sizeof(uint8_t); ptr++){
        std::cout << " " << (unsigned int)*ptr;
        checksum ^= (uint8_t)*ptr;
    }
    m.checksum = checksum;
    memcpy(msg_buf, &m.checksum, sizeof(uint8_t));  msg_buf += sizeof(uint8_t);
    msg_buf -= total_len;
    SerializedMessage serialized_msg;
    serialized_msg.buf = msg_buf;
    serialized_msg.total_len = total_len;
    return serialized_msg;
}

/*
Message structure: 

| StartByte | type | source | Len | --- Payload --- | Checksum |
    1B         1B      1B     2B         len             1B
*/

bool MsgParser::parse(uint8_t data){
    // check startbyte
    switch (status){
        case 0:
            // WARNING: msg is deleted when a new msg begins. NOT THREAD SAFE.
            delete msg.payload;
            msg.payload = nullptr;
            memset(&msg, 0, sizeof(msg));
            if (data == UART_STARTBYTE){
                status++;
            }
            return 0;

        case 1: 
            msg.type = (MessageType)data;
            status++; sum ^= data;
            return 0;

        case 2:
            msg.source = (MessageSource)data;
            status++; sum ^= data;
            return 0;
        
        case 3: 
            memcpy(&(msg.payload_len) + bytecount, &data, 1);
            bytecount += 1; sum ^= data;
            if (bytecount == 2){    // Msg len is uint16_t = 2B
                status++;
                bytecount = 0;
            }
            return 0;

        case 4: 
            if (bytecount == 0){
                msg.payload = (uint8_t*)malloc(msg.payload_len);
            }
            memcpy(msg.payload + bytecount, &data, 1);
            bytecount += 1; sum ^= data;
            if (bytecount == msg.payload_len){
                status++;
                bytecount = 0;
            }
            return 0;
        case 5:
            memcpy(&(msg.checksum), &data, 1);
            bytecount = 0;
            status = 0;
            // Checksum
            bool isvalid;
            isvalid = sum == msg.checksum; 
            sum = 0;
            return isvalid;
        
        default: 
            return 0;
    }
}

bool MsgParser::parse(uint8_t* data, unsigned int len){
    /*
        WARNING: incorrect len will lead to crash/undefined behavior
    */
   bool valid = false;
   for (uint8_t* ptr = data; ptr < data + len; ptr++){
        valid = parse(*ptr);
   }
   return valid;
}   
