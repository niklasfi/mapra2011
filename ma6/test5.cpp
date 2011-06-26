#include "test.cpp"

int main(){
	GreyScale("bilder/shuttle.pgm").Kirsch().Contrast().ToFile("output/result5.pgm");
}