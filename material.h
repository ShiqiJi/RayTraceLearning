#pragma once
#include "ray.h"

class hitRecord;

class material
{
public:
    virtual ~material() {}
    virtual bool scatter(const hitRecord& record, color& attenuation, ray& scetterRay) const = 0;  
};