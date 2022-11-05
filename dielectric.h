#include "material.h"
#include "entitycell.h"

class dielectric : public material
{
public:
    dielectric() {}
    dielectric(const color& albedo, double refractIndex);
    ~dielectric() override {}

    bool scatter(const hitRecord& record, color& attenuation, ray& scetterRay) const override;  

private:
    color m_albedo = color(1.0, 1.0, 1.0);
    double m_refractIndex = 1.0;
};

dielectric::dielectric(const color& albedo, double refractIndex)
    : m_albedo(albedo)
    , m_refractIndex(refractIndex < 1.0 ? 1.0 : refractIndex)
{
}

bool dielectric::scatter(const hitRecord& record, color& attenuation, ray& scetterRay) const
{
    attenuation = m_albedo;
    if(record.frontFace){
        scetterRay = ray(record.hitPoint, record.refract(1.0, m_refractIndex));
    } else {
        scetterRay = ray(record.hitPoint, record.refract(m_refractIndex, 1.0));
    }
    return true;
}