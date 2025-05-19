#include "dataexchange.h"
#include <iostream>
#include <cstring> 
#include <math.h>

#include "quaternion.h"
#include "msvector.h"

int main(){

    MSVector3 v(0.0f,1.0f,0.0f);

    Quaternion q(0.0f,1.0f,0.0f,0.0f);
    
    MSVector3 rv = q.rotate(v);
    
    char buf[100];

    rv.print(buf);
    std::cout << "Testing rotate with quaternion \n";
    std::cout << "Expecting: " << "(0,-1,0)" << "\n";
    std::cout << "Got:      " << buf << "\n\n";

    Quaternion q1(sqrt(2.0f)/2.0f, 0.0f,0.0f,sqrt(2.0f)/2.0f);
    v = MSVector3(1.0f, 0.0f, 0.0f); 
    rv = q1.rotate(v);

    rv.print(buf);
    std::cout << "Testing rotate with quaternion 2 \n";
    std::cout << "Expecting: " << "(0,1,0)" << "\n";
    std::cout << "Got:      " << buf << "\n\n";

    Quaternion q2(0.5f, 0.5f, 0.5f, 0.5f);      // rotate 120 deg around 1,1,1
    v = MSVector3(1,2,3);
    rv = q2.rotate(v);

    rv.print(buf);
    std::cout << "Testing rotate with quaternion 3 \n";
    std::cout << "Expecting: " << "(3, 1, 2)" << "\n";
    std::cout << "Got:      " << buf << "\n\n";

    Quaternion q3(0.92388f, 0.10227f, 0.30683f, 0.204553f);      // rotate 120 deg around 1,1,1
    v = MSVector3(1,2,3);
    rv = q3.rotate(v);

    rv.print(buf);
    std::cout << "Testing rotate with quaternion 3 \n";
    std::cout << "Expecting: " << "(1.92399, 2.041, 2.47628)" << "\n";
    std::cout << "Got:      " << buf << "\n\n";


    return 0;
}