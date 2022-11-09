#include <limits>
#include <mutex>
#include <memory>
#include <vector>
#include <thread>
#include "vector3d.h"
#include "ray.h"
#include "sphere.h"
#include "entity.h"
#include "camera.h"
#include "metal.h"
#include "lambertian.h"
#include "dielectric.h"

camera camera0(point3d(0.0, 0.0, 100.0), vector3d(0.0, 20.0, 8.0), 4.0, 480, 270);
camera camera1(point3d(50.0, -10.0, 10.0), vector3d(0.0, 20.0, 8.0), 5.0, 480, 270);
camera camera3(point3d(50.0, -10.0, 10.0), vector3d(0.0, 20.0, 8.0), 20.0, 1920, 1200);
camera camera4(point3d(50.0, -10.0, 10.0), vector3d(0.0, 20.0, 8.0), 40.0, 3840, 2160);
#define CAMERA camera3
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

void generateWorld()
{
    world.add(std::make_shared<sphere>(point3d(0.0, 0.0, -320000.0), 320000.0, std::make_shared<lambertain>(color(0.8, 0.8, 0.0))));
    world.add(std::make_shared<sphere>(point3d(-20.0, 20.0, 8.0), 8.0, std::make_shared<lambertain>(color(0.7, 0.3, 0.3))));
    world.add(std::make_shared<sphere>(point3d(20.0, 20.0, 8.0), 8.0, std::make_shared<metal>(color(0.8, 0.8, 0.8), 128)));
    world.add(std::make_shared<sphere>(point3d(0.0, 20.0, 8.0), 8.0, std::make_shared<dielectric>(color(0.9, 0.9, 0.9), 1.25)));

    for(int i = -16; i < 16; i++){
        for(int j = -16; j < 16; j++){
            auto ramdom = randomDouble(0.0, 1.0);
            auto radius = randomDouble(2.0, 3.0);
            auto center = point3d(i * 8.0 + randomDouble(-1.0, 1.0), j * 8.0 + randomDouble(-1.0, 1.0), radius);
            if(center.x() < 34.0 && center.x() > -34.0 && center.y() < 26.0 && center.y() > 14.0) continue;
            auto col = color(randomDouble(0.0, 1.0), randomDouble(0.0, 1.0), randomDouble(0.0, 1.0));

            if(ramdom > 0.92){
                world.add(std::make_shared<sphere>(center, radius, std::make_shared<lambertain>(col)));
            } else if(ramdom > 0.84) {
                world.add(std::make_shared<sphere>(center, radius, std::make_shared<metal>(col, randomDouble(16.0, 128.0))));
            } else if(ramdom > 0.76){
                world.add(std::make_shared<sphere>(center, radius, std::make_shared<dielectric>(col, randomDouble(1.01, 1.6))));
            }
        }
    }

}

int main(void)
{
    generateWorld();

    std::vector<std::vector<color>> pixMap(CAMERA.height());
    std::mutex pixMutex;
    int row = 0;
    std::mutex mutex;

    auto funciton = [&](){
        while(true){
            mutex.lock();
            if(row == CAMERA.height()) {
                mutex.unlock();
                return;
            }
            auto currentRow = row;
            row++;
            mutex.unlock();
            std::vector<color> currentRowPix(CAMERA.width());
            for(int i = 0; i < CAMERA.width(); i++){
                color colorSum;
                for (int mixTime = 0; mixTime < 32; mixTime++) {
                    colorSum += rayColor(CAMERA.getRay(i, currentRow), world, 32);
                }
                currentRowPix[i] = colorSum / 32;
            }
            std::cerr << "finish row" << currentRow << "\n";
            pixMutex.lock();
            pixMap[currentRow] = currentRowPix;
            pixMutex.unlock();
        }
    };

    std::thread threads[8];
    for(int i = 0; i < 8; i++){
        threads[i] = std::thread(funciton);
    }
    for(auto &t : threads){
        t.join();
    }

    std::cerr << "generate finish";

    std::cout << "P3\n" << CAMERA.width() << ' ' << CAMERA.height() << "\n255\n";

    for(int j = CAMERA.height() - 1; j >= 0; j--){
        for(auto &pix : pixMap[j]){
            writeColor(std::cout, pix);
        }
    }
} 