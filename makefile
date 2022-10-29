buildPath = ./build

image : creatImage
	./creatImage 1>image.ppm 2>log

creatImage : main.cpp vector3d.h ray.h entity.h sphere.h camera.h entitycell.h
	g++ main.cpp -o creatImage

test : unitTest
	./unitTest 2>&1 1>testLog

unitTest : test.cpp
	g++ test.cpp -o unitTest

clear :
	rm creatImage *.ppm unitTest log testLog