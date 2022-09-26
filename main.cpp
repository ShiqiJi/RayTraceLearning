#include "head.h"

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
        return color(0.0, 0.0, 0.0);
    }
    
    if(entity.hit(r, 0.1, 10000.0, hitRecord1)){
        return 0.5 * rayColor(ray(hitRecord1.hitPoint, vector3d::randomIdentity() + hitRecord1.normal), entity, reflectMaxTimes);
    }

    auto unit = identityVector(r.direction());
    auto t = 0.5 * (unit.z() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main(void)
{
    world.add(std::make_shared<sphere>(point3d(0.0, 20.0, 0.0), 8.0));
    world.add(std::make_shared<sphere>(point3d(0.0, 20.0, -10008.0), 10000.0));

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for(int j = imageHeight - 1; j >= 0; j--){
        for(int i = 0; i < imageWidth; i++){
            color colorSum;
            for (int mixTime = 0; mixTime < maxColorMixTimes; mixTime++) {
                colorSum += rayColor(camera0.getRay(i, j), world, 50);
            }
            writeColor(std::cout, colorSum / maxColorMixTimes);
        }
    }
} 