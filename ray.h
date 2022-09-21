#ifndef RAY
#define RAY

#include "vector3d.h"

class ray
{
public:
    ray();
    ray(const point3d& origin, const vector3d& direction);
    
    point3d origin() const;
    vector3d direction() const;
    point3d at(double t) const;

public:
    point3d m_origin;
    vector3d m_direction;
};

#endif