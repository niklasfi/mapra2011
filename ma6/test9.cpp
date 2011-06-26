#include "test.cpp"

int main(){
	GreyScale("bilder/bauteil.pgm").Sobel().Invert().ToFile("output/result9.pgm");
}