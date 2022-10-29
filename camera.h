#pragma once

#include <vector>
#include "vector3d.h"
#include "ray.h"

const int imageWidth = 960;
const int imageHeight = 540;

const int maxColorMixTimes = 32;

class camera
{
public:
    camera();

    ray getRay(int u, int v); //u: horizontal position v:vertical position
    std::vector<ray> getRay();  

private:
    point3d m_origin;
    point3d m_bottomLeft;
    vector3d m_horizontalIdentity;
    vector3d m_verticalIdentity;
};

camera::camera()
    : m_origin(point3d())
    , m_bottomLeft(point3d(-(imageWidth / 200.0), 2.0, -(imageHeight / 200.0)))
    , m_horizontalIdentity(vector3d(0.01, 0.0, 0.0))
    , m_verticalIdentity(vector3d(0.0, 0.0, 0.01))
{
}

ray camera::getRay(int u, int v)
{
    if(u < 0.0) u = 0.0;
    if(v < 0.0) v = 0.0;
    if(u > imageWidth) u = imageWidth;
    if(v > imageHeight) v = imageHeight;
    auto direction = m_bottomLeft 
    + ((u + randomDouble(-0.5, 0.5)) * m_horizontalIdentity) 
    + ((v + randomDouble(-0.5, 0.5)) * m_verticalIdentity) - m_origin;
    return ray(m_origin, identityVector(direction));
}

std::vector<ray> camera::getRay()
{
    std::vector<ray> rayCollection;
    for(int j = imageHeight - 1; j >= 0; j--){
        for(int i = 0; i < imageWidth; i++){
            rayCollection.push_back(getRay((double)i, (double)j));
        }
    }
    return rayCollection;
}