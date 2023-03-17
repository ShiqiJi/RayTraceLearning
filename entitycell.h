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
    double time;
    hitRecord() 
        : hitPoint(point3d(0.0, 0.0, 0.0))
        , hitDirection(vector3d(0.0, 0.0, 0.0))
        , normal(vector3d(0.0, 0.0, 0.0))
        , t(0.0)
        , frontFace(true) 
        , materialPtr(nullptr) 
        , time(0.0) {}
    vector3d reflect() const
    {
        return hitDirection - 2 * dot(hitDirection, normal) * normal;
    }

    vector3d refract(double inputIndex, double outputIndex) const
    {
        if(fabs(inputIndex - outputIndex) < 0.001){
            return hitDirection;
        }
        auto refractIndex = inputIndex / outputIndex;
        auto identityDirection = identityVector(hitDirection);
        auto identityNormal = identityVector(normal);
        auto cos_theta = dot(-identityDirection, identityNormal);
        auto sin_vector = cos_theta * identityNormal + identityDirection;
        auto refract_sin_vector = sin_vector * refractIndex;
        auto refract_sin = refract_sin_vector.lengthSquared();
        auto R0 = pow((inputIndex - outputIndex) / (inputIndex + outputIndex), 2);
        auto R_theta = R0 + (1 - R0) * pow((1-cos_theta), 5);
        if(refract_sin > 1.0 || R_theta > randomDouble()){
            return reflect();
        }
        return refract_sin_vector - sqrt(fabs(1 - refract_sin)) * identityNormal;
    }
};

class entityCell
{
public:
    virtual ~entityCell() {}
    virtual bool hit(const ray& ray, double minT, double maxT, hitRecord& result) const = 0;
};