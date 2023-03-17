#include "material.h"
#include "entitycell.h"

class lambertain : public material
{
public:
    lambertain();
    lambertain(const color& albedo);
    bool scatter(const hitRecord& record, color& attenuation, ray& scetterRay) const override;  

private:
    color m_albedo;
};

lambertain::lambertain()
    : m_albedo(color())
{
}

lambertain::lambertain(const color& albedo)
    : m_albedo(albedo)
{
}

bool lambertain::scatter(const hitRecord& record, color& attenuation, ray& scetterRay) const
{
    auto direction = record.normal + identityVector(vector3d::randomInUnitSphere());
    if(vector3d::isNullVector(direction)){
        direction = record.normal;
    }
    scetterRay = ray(record.hitPoint, direction, record.time);
    attenuation = m_albedo;
    return true;
}