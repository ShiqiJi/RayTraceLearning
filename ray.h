#pragma once

#include "vector3d.h"

class ray
{
public:
    ray();
    ray(const point3d& origin, const vector3d& direction);
    
    point3d origin() const;
    vector3d direction() const;
    point3d at(double t) const;

private:
    point3d m_origin;
    vector3d m_direction;
};

ray::ray() : m_origin(point3d()), m_direction(vector3d()){}

ray::ray(const point3d& origin, const vector3d& direction)
    : m_origin(origin)
    , m_direction(identityVector(direction))
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