#pragma once

#include <cmath>
#include "vector3d.h"
#include "entitycell.h"

class sphere : public entityCell
{
public:
    sphere();
    sphere(const point3d& startCenter, const point3d& endCenter, double radius, std::shared_ptr<material> material, double startTime, double endTime);
    ~sphere();

    bool hit(const ray& ray, double minT, double maxT, hitRecord& result) const override;

private:
    point3d m_startCenter;
    point3d m_endCenter;
    double m_radius;
    std::shared_ptr<material> m_material;
    double m_startTime;
    double m_endTime;
};

sphere::sphere() 
    : m_startCenter(point3d())
    , m_endCenter(point3d())
    , m_startTime(0.0)
    , m_endTime(0.0)
    , m_radius(0.0) {}

sphere::sphere(const point3d& startCenter, const point3d& endCenter, double radius, std::shared_ptr<material> material, double startTime, double endTime)
    : m_startCenter(startCenter)
    , m_radius(radius)
    , m_material(material)
    , m_startTime(startTime)
    , m_endTime(endTime)
{
}

sphere::~sphere()
{
}

bool sphere::hit(const ray& ray, double minT, double maxT, hitRecord& result) const
{
    double time = ray.time();
    if(time > m_endTime){
        time = m_endTime;
    } else if(time < m_startTime) {
        time = m_startTime;
    }
    point3d center = m_startCenter + (m_endCenter - m_startCenter) * (time - m_startTime) / (m_endTime - m_startTime);
    auto A_C = ray.origin() - center;
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
    result.normal = (result.hitPoint - center) / m_radius;
    result.t = t;
    result.frontFace = dot(result.normal, result.hitDirection) < 0;
    if(!result.frontFace){
        result.normal = -result.normal;
    }
    result.materialPtr = m_material;
    result.time = time;
    return true;
}