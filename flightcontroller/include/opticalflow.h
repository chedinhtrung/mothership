#include <Arduino.h>

#define MICOLINK_MSG_HEAD            0xEF
#define MICOLINK_MAX_PAYLOAD_LEN     64
#define MICOLINK_MAX_LEN             MICOLINK_MAX_PAYLOAD_LEN + 7
#define OF_SERIAL Serial3
/*
    Message ID
*/
enum
{
    MICOLINK_MSG_ID_RANGE_SENSOR = 0x51,     // Range Sensor
};

/*
    Message Structure Definition
*/
typedef struct
{
    uint8_t head;                      
    uint8_t dev_id;                          
    uint8_t sys_id;						
    uint8_t msg_id;                        
    uint8_t seq;                          
    uint8_t len;                               
    uint8_t payload[MICOLINK_MAX_PAYLOAD_LEN]; 
    uint8_t checksum;                          

    uint8_t status;                           
    uint8_t payload_cnt;                       
} MICOLINK_MSG_t;

/*
    Payload Definition
*/
#pragma pack (1)
// Range Sensor
typedef struct
{
    uint32_t  time_ms;		    // System time in ms
    uint32_t  distance;		    // distance(mm), 0 Indicates unavailable
    uint8_t   strength;	            // signal strength
    uint8_t   precision;	    // distance precision
    uint8_t   dis_status;	    // distance status
    uint8_t  reserved1;	            // reserved
    int16_t   flow_vel_x;	    // optical flow velocity in x
    int16_t   flow_vel_y;	    // optical flow velocity in y
    uint8_t   flow_quality;	    // optical flow quality
    uint8_t   flow_status;	    // optical flow status
    uint16_t  reserved2;	    // reserved
} MICOLINK_PAYLOAD_RANGE_SENSOR_t;



class OpticalFlow {
    public:
        OpticalFlow();
        MICOLINK_MSG_t msg;
        MICOLINK_PAYLOAD_RANGE_SENSOR_t payload;
        bool micolink_parse_char(uint8_t data);
        bool micolink_decode(uint8_t data);
    
};
#pragma pack ()