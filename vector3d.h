#ifndef VECTOR3D
#define VECTOR3D

#include <iostream>

class vector3d
{
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

    double length() const;
    double lengthSquared() const; 

private:
    double e[3];
};

using point3d = vector3d;
using color = vector3d;

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

#endif