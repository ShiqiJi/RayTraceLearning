#pragma once

#include <cmath>
#include "vector3d.h"
#include "entitycell.h"

class sphere : public entityCell
{
public:
    sphere();
    sphere(const point3d& center, double radius, std::shared_ptr<material> material);
    ~sphere();

    bool hit(const ray& ray, double minT, double maxT, hitRecord& result) const override;

private:
    point3d m_center;
    double m_radius;
    std::shared_ptr<material> m_material;
};

sphere::sphere() : m_center(point3d()), m_radius(0.0) {}

sphere::sphere(const point3d& center, double radius, std::shared_ptr<material> material)
    : m_center(center)
    , m_radius(radius)
    , m_material(material)
{
}

sphere::~sphere()
{
}

bool sphere::hit(const ray& ray, double minT, double maxT, hitRecord& result) const
{
    auto A_C = ray.origin() - m_center;
    auto a = dot(ray.direction(), ray.direction());
    auto h = dot(A_C, ray.direction());
    auto c = dot(A_C, A_C) - m_radius * m_radius;
    auto h2_ac = h * h - a * c;
    if(h2_ac < 0){
        return false;
    }
    auto sh2_ac = sqrt(h2_ac);
    auto t = (-h - sh2_ac) / a;
    if(t > maxT || t < minT){
        t = (-h + sh2_ac) / a;
        if(t > maxT || t < minT){
            return false;
        }
    }
    result.hitDirection = ray.direction();
    result.hitPoint = ray.at(t);
    result.normal = (result.hitPoint - m_center) / m_radius;
    result.t = t;
    result.frontFace = dot(result.normal, result.hitDirection) < 0;
    if(!result.frontFace){
        result.normal = -result.normal;
    }
    result.materialPtr = m_material;
    return true;
}