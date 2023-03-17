headfiles = ./*.h

image : creatImage
	./creatImage 1>image.ppm 2>log

creatImage : main.cpp $(headfiles)
	g++ -g main.cpp -o creatImage

test : unitTest
	./unitTest >>testLog 2>&1

unitTest : test.cpp $(headfiles)
	g++ test.cpp -o unitTest

clear :
	rm creatImage *.ppm unitTest log testLog