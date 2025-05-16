#ifndef MSVECTOR
#define MSVECTOR

// Just some reimplemented Vector3 for convenience
#include "BasicLinearAlgebra/BasicLinearAlgebra.h"

struct MSVector3 {
    public:
    union {
        struct {
            float x, y, z;
        };
        float data[3];
    };

    BLA::Matrix<3,1>& as_BlaVec(){
        return *reinterpret_cast<BLA::Matrix<3,1>*>(data);
    }

    const BLA::Matrix<3,1>& as_BlaVec() const{
        return *reinterpret_cast<const BLA::Matrix<3,1>*>(data);
    }
};


#endif