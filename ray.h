#pragma once

#include "vector3d.h"

class ray
{
public:
    ray();
    ray(const point3d& origin, const vector3d& direction, double time);
    
    point3d origin() const;
    vector3d direction() const;
    point3d at(double t) const;
    double time() const;

private:
    point3d m_origin;
    vector3d m_direction;
    double m_time;
};

ray::ray() : m_origin(point3d()), m_direction(vector3d()){}

ray::ray(const point3d& origin, const vector3d& direction, double time)
    : m_origin(origin)
    , m_direction(identityVector(direction))
    , m_time(time)
{
}

point3d ray::origin() const
{
    return m_origin; 
}

vector3d ray::direction() const
{
    return m_direction;
}

point3d ray::at(double t) const
{
    return m_origin + (m_direction * t);
}

double ray::time() const
{
    return m_time;
}