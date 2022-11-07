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

int main(void){
    std::cerr << "===============\n";
    std::vector<color> pix;
    pix[10] = color();
}