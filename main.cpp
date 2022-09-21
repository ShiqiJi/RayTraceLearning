#include "cmath"
#include "vector3d.h"
#include "ray.h"

const int imageWidth = 1920;
const int imageHeight = 1080;

const double cameraWidth = 19.2;
const double cameraHeight = 10.8;
const double focalDistance = 8.0;

point3d eye(0.0, 0.0, 0.0);

point3d sphereCenter(0.0, 20.0, 0.0);
double sphereRadius = 8.0;

double hitSphere(const point3d&, double, const ray&);

void writeColor(std::ostream& out, color c)
{
    out << static_cast<int>(255.99 * c.x()) << ' '
        << static_cast<int>(255.99 * c.y()) << ' '
        << static_cast<int>(255.99 * c.z()) << '\n';
}

color rayColor(const ray& r)
{
    auto hitTime = hitSphere(sphereCenter, sphereRadius, r);
    if(hitTime > 0.0){
        return (identityVector(r.at(hitTime) - sphereCenter) + color(1.0, 1.0, 1.0)) * 0.5;
    }
    auto unit = identityVector(r.direction());
    auto t = 0.5 * (unit.z() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

double hitSphere(const point3d& center, double radius, const ray& ray)
{
    auto a_c = ray.origin() - center;
    auto a = dot(ray.direction(), ray.direction());
    auto b = 2 * dot(a_c, ray.direction());
    auto c = dot(a_c, a_c) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    if(discriminant >= 0){
        return (-b - sqrt(discriminant)) / (2 * a) ;
    }
    return 0.0;
}

int main(void)
{
    vector3d cameraXIdentity = identityVector(vector3d(cameraWidth, 0.0, 0.0));
    vector3d cameraYIdentity = identityVector(vector3d(0.0, 0.0, cameraHeight));
    vector3d cameraLeftDownCorner = eye + vector3d(0.0, focalDistance, 0.0) - cameraXIdentity * cameraWidth / 2 - cameraYIdentity * cameraHeight / 2;

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for(int j = imageHeight - 1; j >= 0; j--){
        for(int i = 0; i < imageWidth; i++){
            auto r = ray(eye, cameraLeftDownCorner 
            + (cameraHeight / static_cast<double>(imageHeight) * static_cast<double>(j) * cameraYIdentity) 
            + (cameraWidth / static_cast<double>(imageWidth) * static_cast<double>(i) * cameraXIdentity) - eye);
            writeColor(std::cout, rayColor(r));
        }
    }

} 