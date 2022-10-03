#pragma once

#include <memory>
#include "ray.h"
#include "material.h"

struct hitRecord
{
    point3d hitPoint;
    vector3d hitDirection;
    vector3d normal;
    double t;
    bool frontFace;
    std::shared_ptr<material> materialPtr;
    hitRecord() 
        : hitPoint(point3d(0.0, 0.0, 0.0))
        , hitDirection(vector3d(0.0, 0.0, 0.0))
        , normal(vector3d(0.0, 0.0, 0.0))
        , t(0.0)
        , frontFace(true) 
        , materialPtr(nullptr) {}
    vector3d reflect() const
    {
        return hitDirection - 2 * dot(hitDirection, normal) * normal;
    }
};

class entityCell
{
public:
    virtual ~entityCell() {}
    virtual bool hit(const ray& ray, double minT, double maxT, hitRecord& result) const = 0;
};