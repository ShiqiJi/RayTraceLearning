#ifndef ENTITY
#define ENTITY

#include "ray.h"

struct hitRecord
{
    point3d hitPoint;
    vector3d hitDirection;
    vector3d normal;
    double t;
};

class entity
{
public:
    virtual ~entity() {}
    virtual bool hit(const ray& ray, double minT, double maxT, hitRecord& result) = 0;
};

#endif