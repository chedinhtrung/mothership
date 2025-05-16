#ifndef QUATERNION
#define QUATERNION

#define EQ_EPSILON 0.000001

#ifndef STRUCT_3DPOSE
#define STRUCT_3DPOSE

struct Vector3D {
    float x, y, z;
};

#endif

struct Quaternion { 
    float w, i, j, k;
    public:
    Quaternion(float wq, float iq, float jq, float kq); 
    Quaternion(Vector3D vec);   // create pure quaternion from vec
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
    Vector3D vec();
};


#endif 