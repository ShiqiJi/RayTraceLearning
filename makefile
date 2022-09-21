image : creatImage
	./creatImage > image.ppm

creatImage : main.cpp vector3d.h vector3d.cpp ray.h ray.cpp
	g++ main.cpp vector3d.cpp ray.cpp -o creatImage

clean :
	rm creatImage *.ppm