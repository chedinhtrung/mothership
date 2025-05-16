#ifndef QUATERNION
#define QUATERNION

#define EQ_EPSILON 0.000001

#ifndef STRUCT_3DPOSE
#define STRUCT_3DPOSE

#include "BasicLinearAlgebra/BasicLinearAlgebra.h"
#include "msvector.h"

#endif

struct Quaternion { 
    union {
        struct {
            float w, i, j, k;
        }; 
        float data[4];
    };

    public:
    Quaternion(float wq, float iq, float jq, float kq); 
    Quaternion(MSVector3 vec);   // create pure quaternion from vec
    Quaternion();
    float norm();
    void normize();
    Quaternion T();        //  returns conjugate. 
    Quaternion operator +(Quaternion q);
    Quaternion operator *(Quaternion q);
    Quaternion operator *(float s);
    Quaternion operator /(float s);
    Quaternion operator /(Quaternion q);
    Quaternion inv();
    bool operator ==(Quaternion q);
    void print(char* buf);
    void operator =(Quaternion q);
    MSVector3 vec();
};


#endif 