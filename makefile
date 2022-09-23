image : creatImage
	./creatImage > image.ppm

creatImage : main.cpp vector3d.h vector3d.cpp ray.h ray.cpp entity.h sphere.h sphere.cpp
	g++ main.cpp vector3d.cpp ray.cpp sphere.cpp -o creatImage

clean :
	rm creatImage *.ppm