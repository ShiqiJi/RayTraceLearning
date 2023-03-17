#include "material.h"
#include "entitycell.h"

class metal : public material
{
public:
    metal();
    metal(const color& albedo, double fuzz);
    ~metal() override {}

    bool scatter(const hitRecord& record, color& attenuation, ray& scetterRay) const override;  
private:
    color m_albedo;
    double m_fuzz;
};

metal::metal()
    : m_albedo(color())
{
}

metal::metal(const color& albedo, double fuzz)
    : m_albedo(albedo)
    , m_fuzz(fuzz)
{
}

bool metal::scatter(const hitRecord& record, color& attenuation, ray& scetterRay) const
{
    attenuation = m_albedo;
    scetterRay = ray(record.hitPoint, identityVector(record.reflect()) * m_fuzz + vector3d::randomInUnitSphere(), record.time);
    return true;
}