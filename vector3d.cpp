#include <cmath>
#include "vector3d.h"

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

double vector3d::length() const
{
    return sqrt(lengthSquared());
}

double vector3d::lengthSquared() const
{
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}