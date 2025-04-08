#ifndef RECEIVER
#define RECEIVER
#include <PulsePosition.h>

#define PPM_PIN 9


struct ReceiverData {
    float ThrottleIn;
    float RollIn;
    float PitchIn;
    float YawIn;
    float AuxChannel5In;
    float AuxChannel6In; 
};

class Receiver {
    public:
        PulsePositionInput in; 
        Receiver();
        ReceiverData recv();
        ReceiverData to_anglemode(ReceiverData data);
};

#endif