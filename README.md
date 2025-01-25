## Project Mothership

Goal: Autonomous drone that is carried by a rover. Using autopilot, it can follow the rover and land on it.

Components:

    - Drone: 
        - Arduino based flight controller
        - Raspberry Pi Zero 2W based flight computer with camera
        - Drone connects to Rover via Rover's wifi router
        - Autopilot
        - Frame: preferably below 5 inches
        - Computer Vision: either on-board or off-board (streams to Rover)
        - Flight software: preferrably all C++
    
    - Rover: 
        - Fully WAN capable, with own 4G router
        - Nvidia Jetson Nano computer, 2x CSI camera for autonomous landing assist
        - Live streams H264 via own protocol that sends raw H264
        - CV: Visual landing assist, autopilot
        - Software: preferrably C++
        - On board GPS & battery indicator

Knowledge needed & sources: 
    - State estimation (Extended Kalman Filter), control and regulation 
    - Autopilot design
    - System design
    - Networking in C++
    - Camera device access with C++ & encoding/decoding setup 
    - Application development on C++
    - Multiple View Geometry in Computer Vision
    - Basic Object Detection models

Sources:
    [1] Dan Simon - Optimal State Estimation 
    [2] Randal W. Beard - Small Unmanned Aircraft Theory and Practice
    [3] deeplearningbook.org
    [4] 


