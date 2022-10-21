#include <limits>
#include "vector3d.h"
#include "ray.h"
#include "sphere.h"
#include "entity.h"
#include "camera.h"
#include "metal.h"
#include "lambertian.h"
#include "dielectric.h"

camera camera0;

point3d eye(0.0, 0.0, 0.0);

entity world;

void writeColor(std::ostream& out, color c)
{
    out << static_cast<int>(256 * sqrt(limitValue(c.x(), 0.0, 0.999))) << ' '
        << static_cast<int>(256 * sqrt(limitValue(c.y(), 0.0, 0.999))) << ' '
        << static_cast<int>(256 * sqrt(limitValue(c.z(), 0.0, 0.999))) << '\n';
}

color rayColor(const ray& r, const entityCell& entity, int reflectMaxTimes)
{
    hitRecord hitRecord1;
    
    if(--reflectMaxTimes < 0){
        //std::cerr << "black" << std::endl; 
        return color(0.0, 0.0, 0.0);
    }
    
    if(entity.hit(r, 0.1, std::numeric_limits<double>::infinity(), hitRecord1)){
        color attenuation;
        ray scatterRay;
        hitRecord1.materialPtr->scatter(hitRecord1, attenuation, scatterRay);
        return attenuation * rayColor(scatterRay, entity, reflectMaxTimes);
    }

    auto unit = identityVector(r.direction());
    auto t = 0.5 * (unit.z() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main(void)
{
    world.add(std::make_shared<sphere>(point3d(0.0, 20.0, 0.0), 8.0, std::make_shared<lambertain>(color(0.7, 0.3, 0.3))));
    world.add(std::make_shared<sphere>(point3d(0.0, 20.0, -10008.0), 10000.0, std::make_shared<lambertain>(color(0.8, 0.8, 0.0))));
    world.add(std::make_shared<sphere>(point3d(20.0, 20.0, 0.0), 8.0, std::make_shared<metal>(color(0.8, 0.8, 0.8), 32)));
    world.add(std::make_shared<sphere>(point3d(-20.0, 20.0, 0.0), 8.0, std::make_shared<dielectric>(color(0.9, 0.9, 0.9), 1.4, 0.8)));

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for(int j = imageHeight - 1; j >= 0; j--){
        for(int i = 0; i < imageWidth; i++){
            color colorSum;
            for (int mixTime = 0; mixTime < maxColorMixTimes; mixTime++) {
                colorSum += rayColor(camera0.getRay(i, j), world, 32);
            }
            writeColor(std::cout, colorSum / maxColorMixTimes);
        }
    }
} 