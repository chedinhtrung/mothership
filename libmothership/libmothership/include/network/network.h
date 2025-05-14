#ifndef NETWORK 
#define NETWORK
#define WIN32_LEAN_AND_MEAN

#include "platforms.h"
#ifdef PLATFORM_WIN
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#ifdef PLATFORM_UNIX
#include <socket.h>
#endif

#include "dataexchange.h"
#include <queue>

class DataChannel {
    public: 
        

};

class UdpDataChannel {
    public: 
        
};

#endif