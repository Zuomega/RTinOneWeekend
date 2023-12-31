#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include "utils.h"
using std::sqrt;


class vec3
{
    public:
        FLOAT_FORMAT e[3];

        vec3() : e{0,0,0} {}
        vec3(FLOAT_FORMAT e0, FLOAT_FORMAT e1, FLOAT_FORMAT e2) : e{e0, e1, e2} {}

        FLOAT_FORMAT x() const {return e[0];}
        FLOAT_FORMAT y() const {return e[1];}
        FLOAT_FORMAT z() const {return e[2];}

        vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
        FLOAT_FORMAT operator[](int i) const {return e[i];}
        FLOAT_FORMAT & operator[](int i) {return e[i];}

        vec3& operator+=(const vec3 &v){
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3& operator*=(FLOAT_FORMAT t)
        {
            e[0] *= t;
            e[1] *= t;
            e[2] *=t;
            return *this;
        }

        vec3& operator/=(FLOAT_FORMAT t)
        {
            return *this *= 1/t;
        }

        FLOAT_FORMAT length() const {
            return sqrt(length_squared());
        }

        FLOAT_FORMAT length_squared() const {
            return e[0]*e[0] + e[1] *e[1] + e[2] *e[2];
        }

        static vec3 random(){
            return vec3(random_double(), random_double(),random_double());
        }

        static vec3 random(FLOAT_FORMAT min, FLOAT_FORMAT max)
        {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }
};

using point3 = vec3;

inline vec3 operator+(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0]*v.e[0], u.e[1]*v.e[1], u.e[2]*v.e[2]);
}

inline vec3 operator*(FLOAT_FORMAT t, const vec3 &v)
{
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, FLOAT_FORMAT t)
{
    return t*v;
}

inline vec3 operator/(vec3 v, FLOAT_FORMAT t)
{
    return (1/t)*v;
}

inline FLOAT_FORMAT dot(const vec3 &u, const vec3 &v)
{
    return u.e[0]*v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[1]*v.e[2] - u.e[2] * v.e[1],
                u.e[2]*v.e[0] - u.e[0] * v.e[2],
                u.e[0]*v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v)
{
    return v / v.length();
}

inline vec3 random_in_unit_sphere()
{
    while(true)
    {
        auto p = vec3::random(-1, 1);
        if (p.length_squared() < 1)
        {
            return p;
        }
    }
}

inline vec3 random_unit_vector()
{
    return unit_vector(random_in_unit_sphere());
}

inline vec3 random_on_hemisphere(const vec3& normal)
{
    vec3 on_unit_sphere = random_unit_vector();
    if(dot(on_unit_sphere, normal) > 0.0) // in the same hemisphere as normal
    {
        return on_unit_sphere;
    }
    else
    {
        return -on_unit_sphere;
    }
}
#endif