#include "test.cpp"

int main(){
	GreyScale("bilder/dom.pgm").Median().Median().Median().Median().Median().ToFile("output/result3.pgm");
}