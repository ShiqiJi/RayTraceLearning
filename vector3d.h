# pragma once

#include <iostream>
#include <cmath>

double randomDouble()
{
    return rand() / (RAND_MAX + 1.0);
}

double randomDouble(double min, double max)
{
    return randomDouble() * (max -min) + min;
}

class vector3d
{
public:
    inline static vector3d random();
    inline static vector3d random(double min, double max);
    inline static vector3d randomIdentity();

public:
    vector3d();
    vector3d(double x1, double y1, double z1);

    double x();
    double y();
    double z();

    vector3d operator-() const;
    double operator[](int i) const;
    double& operator[](int i);
    vector3d& operator+=(const vector3d& v);
    vector3d& operator*=(const double t);
    vector3d& operator/=(const double t);
    bool operator==(const vector3d& v);
    bool operator!=(const vector3d& v);

    double length() const;
    double lengthSquared() const; 

private:
    double e[3];
};

using point3d = vector3d;
using color = vector3d;

vector3d vector3d::random()
{
    return vector3d(randomDouble(), randomDouble(), randomDouble());
}

vector3d vector3d::random(double min, double max)
{
    return vector3d(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

vector3d vector3d::randomIdentity()
{
    while(true){
        auto v = random(-1, 1);
        if(v.length() < 1.0){
            return v;
        }
    }
}

vector3d::vector3d()
    : e{0.0, 0.0, 0.0}
{
}

vector3d::vector3d(double x1, double y1, double z1)
    : e{x1, y1, z1}
{
}

double vector3d::x()
{
    return e[0];
}

double vector3d::y()
{
    return e[1];
}

double vector3d::z()
{
    return e[2];
}

vector3d vector3d::operator-() const
{
    return vector3d(-e[0], -e[1], -e[2]);
}

double vector3d::operator[](int i) const 
{
    return e[i];
}

double& vector3d::operator[](int i)
{
    return e[i];
}

vector3d& vector3d::operator+=(const vector3d& v)
{
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this; 
}

vector3d& vector3d::operator*=(const double t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

vector3d& vector3d::operator/=(const double t)
{
    return *this *= (1.0/t);
}

bool vector3d::operator==(const vector3d& v)
{
    if(e[0] == v.e[0] && e[1] == v.e[1] && e[2] == v.e[2]){
        return true;
    }
    return false;
}

bool vector3d::operator!=(const vector3d& v)
{
    if(e[0] == v.e[0] && e[1] == v.e[1] && e[2] == v.e[2]){
        return false;
    }
    return true;
}


double vector3d::length() const
{
    return sqrt(lengthSquared());
}

double vector3d::lengthSquared() const
{
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

inline std::ostream& operator<< (std::ostream& out, const vector3d& v)
{
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline vector3d operator+ (const vector3d& v1, const vector3d& v2)
{
    return vector3d(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

inline vector3d operator- (const vector3d& v1, const vector3d& v2)
{
    return v1 + (-v2);
}

inline vector3d operator* (const vector3d& v1, const vector3d& v2)
{
    return vector3d(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}

inline vector3d operator* (const vector3d& v1, double t)
{
    return vector3d(v1[0] * t, v1[1] * t, v1[2] * t);
}

inline vector3d operator* (double t, const vector3d& v2)
{
    return v2 * t;
}

inline vector3d operator/ (const vector3d& v1, double t)
{
    return v1 * (1.0 / t);
}

inline double dot(const vector3d& v1, const vector3d& v2)
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

inline vector3d cross (const vector3d& v1, const vector3d& v2)
{
    return vector3d(v1[1] * v2[2] - v1[2] * v2[1], v1[2] * v2[0] - v1[0] * v2[2], v1[0] * v2[1] - v1[1] * v2[0]);
}

inline vector3d identityVector(const vector3d& v)
{
    return v / v.length();
}