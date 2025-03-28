/*
    Unified data exchange form between Rover, Drone, and MissionControl
*/
#ifndef DEXCH 
#define DEXCH
#define UART_STARTBYTE 0x78
#define NETWORK_STARTBYTE 0x51
#define FLIGHT_DISP_UPDATE_RATE 10
#define NAV_UPDATE_RATE 10

#include <cstdint>
enum MessageType : uint8_t {
    INFO,
    DEBUG,
    ERROR,
    CMD,
    NAV,
    TELEMETRY,
    FLIGHTDISP
};

enum MessageSource : uint8_t {
    ROVER,
    DRONE,
    MISSION_CTL,
    SERVER
};

#pragma pack(1)       // No padding! 

// Message is serialized in this order
struct Message { 
    MessageType type;
    MessageSource source;
    uint16_t payload_len;
    uint8_t* payload = nullptr;
    uint8_t checksum;
    ~Message();
};

struct SerializedMessage {
    uint8_t* buf = nullptr;
    int16_t total_len;
    ~SerializedMessage();
};

struct NavPayload { 
    float lon;
    float lat;
    int16_t heading;
};

struct FlightDispPayload { 
    int16_t roll;           // To be set: (int)100*roll. 
    int16_t pitch;
    int8_t vspeed;
    int8_t gspeed;
    int16_t alt;
};

#pragma pack()

SerializedMessage serialize(Message m);

class MsgParser {
    /*
        WARNING: not thread safe! parser will free the memory of msg everytime a new msg begins
    */
    private: 
        uint8_t bytecount = 0;
        uint8_t sum;
    public: 
        Message msg;    // Current message being parsed
        uint8_t status = 0; // current step during sequential parse
        bool parse(uint8_t data);             // parse next byte, for arduino UART. Returns true when msg is complete
        bool parse(uint8_t* data, unsigned int len);   // parse all at once, for socket
};

#endif