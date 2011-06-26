#include "test.cpp"

int main(){
	GreyScale pic("output/result4.pgm");
	GreyScale newpic;
	newpic=pic.Laplace().LinTrans(0.1,0);
	newpic+=pic;
	pic = newpic;
	newpic=pic.Laplace().LinTrans(0.1,0);
	newpic+=pic;
	pic = newpic;
	newpic=pic.Laplace().LinTrans(0.1,0);
	newpic+=pic;
	pic = newpic;
	newpic=pic.Laplace().LinTrans(0.1,0);
	newpic+=pic;
	pic = newpic;
	newpic=pic.Laplace().LinTrans(0.1,0);
	newpic+=pic;
	pic = newpic;
	pic.ToFile("output/result11.pgm");
}