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

    vector3d refract(double inputIndex, double outputIndex, double tatalReflactSin) const
    {
        if(fabs(inputIndex - outputIndex) < 0.001){
            return hitDirection;
        }
        auto refractIndex = inputIndex / outputIndex;
        auto identityDirection = identityVector(hitDirection);
        auto identityNormal = identityVector(normal);
        auto sin_vector = dot(-identityDirection, identityNormal) * identityNormal + identityDirection;
        auto refract_sin_vector = sin_vector * refractIndex;
        auto refract_sin = refract_sin_vector.lengthSquared();
        if(inputIndex < outputIndex) {
            return refract_sin_vector - sqrt(fabs(1 - refract_sin)) * identityNormal;
        } else {
            if(refract_sin > pow(tatalReflactSin, 2)){
                return reflect();
            }
            return refract_sin_vector - sqrt(fabs(1 - refract_sin)) * identityNormal;
        }
    }
};

class entityCell
{
public:
    virtual ~entityCell() {}
    virtual bool hit(const ray& ray, double minT, double maxT, hitRecord& result) const = 0;
};