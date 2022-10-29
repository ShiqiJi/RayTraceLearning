#include <iostream>
#include "camera.h"
#include "vector3d.h"

camera c0;

int main(void){
    std::cout << dot(vector3d(1.0, 1.0, 0.0), vector3d(0.0, 1.0, 0.0)) << "\n";        
}