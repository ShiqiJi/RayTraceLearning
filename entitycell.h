#ifndef ENTITYCELL
#define ENTITYCELL

#include "ray.h"

struct hitRecord
{
    point3d hitPoint;
    vector3d hitDirection;
    vector3d normal;
    double t;
    bool frontFace;
    hitRecord() 
        : hitPoint(point3d(0.0, 0.0, 0.0))
        , hitDirection(vector3d(0.0, 0.0, 0.0))
        , normal(vector3d(0.0, 0.0, 0.0))
        , t(0.0)
        , frontFace(true) {}
};

class entityCell
{
public:
    virtual ~entityCell() {}
    virtual bool hit(const ray& ray, double minT, double maxT, hitRecord& result) = 0;
};

#endif