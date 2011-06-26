#include "test.cpp"

int main(){
	GreyScale pic("bilder/roentgen.pgm");
	GreyScale newpic;
	newpic = pic.Sobel().LinTrans(0.1,0);
	newpic+=pic;
	pic=newpic;
	newpic = pic.Sobel().LinTrans(0.1,0);
	newpic+=pic;
	pic=newpic;
	newpic=pic.Sobel().LinTrans(0.1,0);
	newpic+=pic;
	pic=newpic;
	pic.Contrast().ToFile("output/result10.pgm");
}