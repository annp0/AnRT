#ifndef VEC3_HPP
#define VEC3_HPP

#include "utility.hpp"

#include<iostream>
#include<cmath>

/* 3D Vectors */

class vec3 {
  public:
    double e[3];
    
    vec3() {e[0] = 0; e[1] = 0; e[2] = 0;}
    vec3(double e0, double e1, double e2) {e[0] = e0; e[1] = e1; e[2] = e2;}
    
    /* Use const keyword to makesure the functions
    do not make change to the object itself */
    double x() const {return e[0];}
    double y() const {return e[1];}
    double z() const {return e[2];}

    vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
    double operator[](int i) const {return e[i];}
    /* Return by reference to allow modification
    of the values */
    double& operator[](int i) {return e[i];}

    /* Pass by reference to maximize efficiency */
    vec3& operator+=(const vec3 &v);
    vec3& operator*=(double t);
    vec3& operator/=(double t) {return (*this) *= (1/t);}
    
    double norm_squared() const {return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];}
    double norm() const {return std::sqrt(norm_squared());}
};

vec3& vec3::operator+=(const vec3 &v){
    e[0] += v[0];
    e[1] += v[1];
    e[2] += v[2];
    return *this;
}

vec3& vec3::operator*=(double t){
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

/* To avoid confusion between vectors and points */
using point3 = vec3;

/* Some simple utility functions */

std::ostream& operator<<(std::ostream &out, const vec3 &v){
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

vec3 operator+(const vec3 &v1, const vec3 &v2){
    return vec3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

vec3 operator-(const vec3 &v1, const vec3 &v2){
    return v1 + (-v2);
}

vec3 operator*(const vec3 &v1, const vec3 &v2){
    return vec3(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}

vec3 operator*(double t, const vec3 &v){
    return vec3(t * v[0], t * v[1], t * v[2]);
}

vec3 operator*(const vec3 &v, double t){
    return t * v;
}

vec3 operator/(vec3 v, double t){
    return (1/t) * v;
}

double dot(const vec3 &v1, const vec3 &v2){
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

vec3 cross(const vec3 &v1, const vec3 &v2){
    return vec3(v1[1] * v2[2] - v1[2] * v2[1],
                v1[2] * v2[0] - v1[0] * v2[2],
                v1[0] * v2[1] - v1[1] * v2[0]);
}

vec3 unit(const vec3 &v){
    return v / v.norm();
}

vec3 random_unit_vec(){
    vec3 result = vec3(random_double(-1, 1), random_double(-1, 1), random_double(-1, 1));
    if (result.norm_squared() == 0){
        return random_unit_vec();
    }
    return unit(result);
}

bool is_near_zero(const vec3& v){
    auto s = 1e-8;
    return (fabs(v[0]) < s) && (fabs(v[1]) < s) && (fabs(v[2]) < s);
}

vec3 reflect(const vec3& v, const vec3& n){
    return v - 2 * dot(v, n) * n;
}

vec3 refract(const vec3& v, const vec3& n, double refractive_index){
    auto cos = fmin(dot(-v, n), 1.0);
    vec3 r_out_perp = refractive_index * (v + cos * n);
    vec3 r_out_para = -sqrt(fabs(1.0 - r_out_perp.norm_squared())) * n;
    return r_out_perp + r_out_para;
}

#endif