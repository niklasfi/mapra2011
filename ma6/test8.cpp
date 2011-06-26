#include "test.cpp"

int main(){
	GreyScale("bilder/bauteil.pgm").Contrast().Binarize(.5).ToFile("output/result8.pgm");
}