#pragma once

#include <vector>
#include "vector3d.h"
#include "ray.h"

class camera
{
public:
    camera();
    camera(point3d origin = point3d()
    , point3d lookAt = point3d(0.0, 1.0, 0.0)
    , double focus = 4.0
    , int width = 1920
    , int height = 1080
    , double timeMin = 0.0
    , double timeMax = 1.0);

    int width();
    int height();

    ray getRay(int u, int v); //u: horizontal position v:vertical position
    std::vector<ray> getRay();  

private:
    vector3d randomVectorInUnitDisk();

    point3d m_origin;
    point3d m_bottomLeft;
    vector3d m_horizontalIdentity;
    vector3d m_verticalIdentity;
    int m_width;
    int m_height;
    double m_timeMin;
    double m_timeMax;
};

camera::camera(point3d origin, point3d lookAt, double focus, int width, int height, double timeMin, double timeMax)
    : m_origin(origin)
    , m_width(width)
    , m_height(height)
    , m_timeMin(timeMin)
    , m_timeMax(timeMax)
{
    vector3d tempH;
    auto direction = lookAt - origin;
    if(direction.x() == 0.0){
        tempH = vector3d(1, 0, 0);
    } else {
        tempH = vector3d(-direction.y()/direction.x(), 1, 0);
    }
    if(cross(tempH, vector3d(direction.x(), direction.y(), 0)).z() > 0){
        tempH = -tempH;
    }
    auto tempV = cross(direction, tempH);
    m_bottomLeft = origin + focus * identityVector(direction) + m_width / 200.0 * identityVector(tempH) - m_height / 200.0 * identityVector(tempV);
    m_horizontalIdentity = -identityVector(tempH) / 100.0;
    m_verticalIdentity = identityVector(tempV) / 100.0;
}

int camera::width()
{
    return m_width;
}

int camera::height()
{
    return m_height;
}

ray camera::getRay(int u, int v)
{
    if(u < 0.0) u = 0.0;
    if(v < 0.0) v = 0.0;
    if(u > m_width) u = m_width;
    if(v > m_height) v = m_height;
    auto cameraSensor = randomVectorInUnitDisk();
    auto offset = m_horizontalIdentity * cameraSensor.x() * m_width / 200.0 + m_verticalIdentity * cameraSensor.z() * m_height / 200.0;
    auto direction = m_bottomLeft 
    + ((u + randomDouble(-0.5, 0.5)) * m_horizontalIdentity) 
    + ((v + randomDouble(-0.5, 0.5)) * m_verticalIdentity) - m_origin;
    return ray(m_origin, identityVector(direction), randomDouble(m_timeMin, m_timeMax));
}

std::vector<ray> camera::getRay()
{
    std::vector<ray> rayCollection;
    for(int j = m_height - 1; j >= 0; j--){
        for(int i = 0; i < m_width; i++){
            rayCollection.push_back(getRay((double)i, (double)j));
        }
    }
    return rayCollection;
}

vector3d camera::randomVectorInUnitDisk()
{
    while(true){
        auto v = vector3d(randomDouble(-1.0, 1.0), 0.0, randomDouble(-1.0, 1.0));
        if(v.lengthSquared() > 1.0) continue;
        return v;
    }
}