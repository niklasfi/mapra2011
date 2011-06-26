#include "test.cpp"

int main(){
	GreyScale("bilder/dom.pgm").Blur().Blur().ToFile("output/result4.pgm");
}