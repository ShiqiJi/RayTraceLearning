buildPath = ./build

image : creatImage
	./creatImage > image.ppm

creatImage : main.cpp vector3d.h ray.h entity.h sphere.h camera.h entitycell.h
	g++ main.cpp -o ./creatImage

clear :
	rm creatImage *.ppm