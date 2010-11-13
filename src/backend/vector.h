/**
*   vector.h
*/

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstdio>
#include <map>
#include <math.h>

#define TOL 0.000000000000001f          // float type tolerance 
#define PI  3.14159265358979323846f     // value of PI


template <typename T> struct Vector
{
    T x;
    T y;
    T z;

  public:
    
    Vector(T x = 0, T y = 0, T z = 0): x(x), y(y), z(z) {
    }

    void set(T newX, T newY, T newZ) {
        x = newX;
        y = newY;
        z = newZ;
    }

    void setX(T newX) {
    	x = newX;
    }

    void setY(T newY) {
    	y = newY;
    }

    void setZ(T newZ) {
    	z = newZ;
    }

    T getX() {
      return x;
    }

    T getY() {
      return y;
    }

    T getZ() {
      return z;
    }

    T scalar(Vector &V) {
        return V.x * x + V.y * y + V.z * z;
    }

    const Vector<T> &operator=(const Vector<T> &v) {   
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    bool operator==(const Vector<T> &v) {
        return ( (x == v.x) && (y == v.y) && (z == v.z) );
    }

    bool operator!=(const Vector<T> &v) {
        return ( (x != v.x) || (y != v.y) || (z != v.z) );
    }
    
    Vector<T> operator+(const Vector<T> &v) const {   
        return Vector<T>( x+v.x, y+v.y, z+v.z );
    }

    Vector<T> &operator+=(const Vector<T> &v) {
        x += v.x;
        y += v.y; 
        z += v.z;
        return *this;
    }

    Vector<T> operator-(const Vector<T> &v) const {   
        return Vector<T>( x-v.x, y-v.y, z-v.z );
    }

    const Vector<T> &operator-=(const Vector<T> &v) const {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
    
    T operator*(const Vector<T> &v) const {   
        return (x*v.x + y*v.y + y*v.z);
    }   

    const Vector<T> operator*(const T num) const {   
        return Vector<T>(x*num, y*num, z*num);
    }

    Vector<T> &operator*=(const T num) {
        x *= num;
        y *= num;
        z *= num;
        return *this;
    }

    const Vector<T> operator/(const T num) const {
        return Vector<T>(x/num, y/num, z/num);
    }       

    float magnitude() const {   
        return (float)sqrt(*this * *this);
    }

    const Vector<T> unit() {
        float mag;

        if(magnitude() > TOL) {    
            mag = magnitude();
            return Vector<T>(x/mag, y/mag, z/mag);
        }
        return Vector<T>(x,y);     
    }

    static inline float getAngle(const Vector<T> &v1, const Vector<T> &v2) {   
        return acosf((v1*v2)/(v1.magnitude()*v2.magnitude()));  
    }

    static inline float getAngle_normalized(const Vector<T> &v1, const Vector<T> &v2) {   
        return acosf(v1*v2);
    }

    inline float degrees2Radians(float deg) {
        return (deg * PI / 180.0f);
    }

    inline float radians2Degrees(float rad) {
        return rad * 180.0f / PI;
    }    

};


template <typename T>
class vectorCmp 
{
  public:

    bool operator()(const Vector<T> &a, const Vector<T> &b) {
        if (a.x == b.x) {
        	if(a.y == b.y) {
        		return (a.z < b.z);
        	}
        	else {
        		return (a.y < b.y);
        	}
        }
        else {
            return (a.x < b.x);
        }
    }
};


#endif
