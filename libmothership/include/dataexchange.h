/*
    Unified data exchange format between Rover, Drone, and MissionControl
*/
#ifndef DEXCH 
#define DEXCH
#define UART_STARTBYTE 0x78
#define NETWORK_STARTBYTE 0x51
#define FLIGHT_DISP_UPDATE_RATE 10
#define NAV_UPDATE_RATE 10
#define MSG_LEN_TYPE uint16_t
#define CHECKSUM_TYPE uint8_t

#include <cstdint>
enum MessageType : uint8_t {
    M_INFO,
    M_DEBUG,
    M_ERROR,
    M_CMD,
    M_NAV,
    M_TELEMETRY,
    M_FLIGHTDISP
};

enum MessageSource : uint8_t {
    ROVER,
    DRONE,
    MISSION_CTL,
    SERVER
};

#pragma pack(1)       // No padding! 

// Note: declare Payload types before Message types!
struct NavPayload { 
    float lon = 0.0;
    float lat = 0.0;
    int16_t heading = 0;
};

struct FlightDispPayload { 
    int16_t roll = 0;           // To be set: (int)100*roll. 
    int16_t pitch = 0;
    int8_t vspeed = 0;
    int8_t gspeed = 0;
    int16_t alt = 0;
};

// Message is serialized in this order
struct Message { 
    MSG_LEN_TYPE len = 0;
    MessageType type = M_INFO;
    MessageSource source = MISSION_CTL;
    uint8_t* payload = nullptr;
    CHECKSUM_TYPE checksum = 0;
    bool valid = 1;

    Message() = default;
    Message(NavPayload pl);
    Message(FlightDispPayload pl);
    ~Message();
    MSG_LEN_TYPE get_payload_len();

    bool get_nav(NavPayload &pl);
    bool get_flightdisp(FlightDispPayload &pl);
};

#pragma pack()

int serialize(uint8_t* &buf, Message &m);
int serialize_uart(uint8_t* &buf, Message &m);

bool parse(Message &m, uint8_t data);


#endif