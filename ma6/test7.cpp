#include "test.cpp"

int main(){
	GreyScale("bilder/shuttle.pgm").Sobel().ToFile("output/result7.pgm");
}