#include "quaternion.h"
#include <cstdio>
#include <math.h>

Quaternion::Quaternion(float wq, float iq, float jq, float kq){
    w = wq;
    i = iq; 
    j = jq; 
    k = kq;
}

Quaternion::Quaternion(){
    w = 1;
    i = j = k = 0;
}

Quaternion Quaternion::T(){
    Quaternion conj;
    conj.w = w;
    conj.i = -i;
    conj.j = -j;
    conj.k = -k;
    return conj;
}

float Quaternion::norm(){
    return sqrt(w*w + i*i + j*j + k*k);
}

void Quaternion::normize(){
    float n = norm();
    w /= n;
    i /= n;
    j /= n;
    k /= n;
}

void Quaternion::operator=(Quaternion q){
    w = q.w;
    i = q.i;
    j = q.j; 
    k = q.k;
}

Quaternion Quaternion::operator*(float s){
    Quaternion res;
    res.w = s*w;
    res.i = s*i;
    res.j = s*j;
    res.k = s*k;
    return res;
}

Quaternion Quaternion::operator*(Quaternion q){
    // Reference: Jack Kuipers Quaternion & Rotation Sequences, p.109 Eq (5.3)
    Quaternion res;
    res.w = q.w*w - q.i*i - q.j*j - q.k*k;
    res.i = q.w*i + q.i*w - q.j*k + q.k*j;
    res.j = q.w*j + q.i*k + q.j*w - q.k*i;
    res.k = q.w*k - q.i*j + q.j*i + q.k*w;
    return res;
}

Quaternion Quaternion::inv(){
    return T() / (norm() * norm());
}

Quaternion Quaternion::operator/(float s){
    return Quaternion(w/s, i/s, j/s, k/s);
}

Quaternion Quaternion::operator/(Quaternion q){
    return *this * q.inv();
}

void Quaternion::print(char* buf){
    sprintf(buf, "(w: %f; i: %f, j: %f, k: %f) \n", w, i, j, k);
    // Printing is platform dependent. On MCU it would be using Serial interface.
    // Here only prints into a buffer.
}

Vector3D Quaternion::vec(){
    Vector3D vec;
    vec.x = i;
    vec.y = j; 
    vec.z = k;
    return vec;
}

Quaternion Quaternion::operator +(Quaternion q){
    Quaternion res(w + q.w, i+q.i, j+q.j, k+q.k);
    return res;
}

bool Quaternion::operator ==(Quaternion q){
    return w - q.w < EQ_EPSILON &&  i - q.i < EQ_EPSILON && j - q.j < EQ_EPSILON && k - q.k < EQ_EPSILON;
} 