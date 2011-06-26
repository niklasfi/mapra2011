#include "test.cpp"

int main(){
	GreyScale("bilder/shuttle.pgm").Laplace().ToFile("output/result6.pgm");
}