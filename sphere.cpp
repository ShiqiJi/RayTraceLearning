#include <cmath>
#include "sphere.h"

sphere::sphere() : m_center(point3d()), m_radius(0.0) {}

sphere::sphere(const point3d& center, double radius)
    : m_center(center)
    , m_radius(radius)
{
}

sphere::~sphere()
{
}

bool sphere::hit(const ray& ray, double minT, double maxT, hitRecord& result)
{
    auto a_c = ray.origin() - m_center;
    auto a = dot(ray.direction(), ray.direction());
    auto halfB = dot(a_c, ray.direction());
    auto c = dot(a_c, a_c) - m_radius * m_radius;
    auto discriminant = halfB * halfB - a * c;
    if(discriminant < 0){
        return false;
    }
    auto t = (0.0 - halfB - sqrt(halfB * halfB - a * c)) / a;
    if(t > maxT || t < minT){
        auto t = (0.0 - halfB + sqrt(halfB * halfB - a * c)) / a;
        if(t > maxT || t < minT){
            return false;
        }
    }
    result.hitDirection = ray.direction();
    result.hitPoint = ray.at(t);    
    result.normal = (result.hitPoint - m_center) / m_radius;
    result.t = t;
    result.frontFace = dot(result.normal, result.hitDirection) < 0;
    return true;
}