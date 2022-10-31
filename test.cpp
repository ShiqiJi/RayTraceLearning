#include <iostream>
#include "camera.h"
#include "vector3d.h"
#include "dielectric.h"

camera c0;

int main(void){
    std::cerr << "===============\n";

    hitRecord rcd;
    rcd.frontFace = false;
    rcd.hitDirection = vector3d(0, 1, -1);
    rcd.hitPoint = point3d(0, 0, 0);
    rcd.materialPtr = std::make_shared<dielectric>(color(0.9, 0.9, 0.9), 1.4, 0.95);
    rcd.normal = vector3d(0, 0, 1);
    rcd.t = 1;
    color attenuation = color();
    ray refract = ray();
    rcd.materialPtr->scatter(rcd, attenuation, refract);
    std::cerr << refract.direction() <<std::endl;
}