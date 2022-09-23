#ifndef SPHERE
#define SPHERE

#include "vector3d.h"
#include "entity.h"

class sphere : public entity
{
public:
    sphere();
    sphere(const point3d& center, double radius);
    ~sphere();

    bool hit(const ray& ray, double minT, double maxT, hitRecord& result) override;

private:
    point3d m_center;
    double m_radius;
};

#endif