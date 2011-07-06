#include "test.cpp"

void firstA(){
	GreyScale pic1("bilder/roentgen.pgm");
	pic1.SetFormat(GreyScale::Raw)
		.ToFile("output/result12.pgm");
	GreyScale pic2("output/result12.pgm");
	Display(pic2,1,"new file");
	//sleep(1);
	
	GreyScale pic3("bilder/shuttle.pgm");
	pic3.SetFormat(GreyScale::Raw)
		.ToFile("output/result15.pgm");
	GreyScale pic4("output/result15.pgm");
	Display(pic4,4,"new file");
	//sleep(1);
}

void secondA(){
	GreyScale pic1("bilder/roentgen.pgm");
	pic1.SetFormat(GreyScale::HuffmanA)
		.ToFile("output/result13.pgm");
	GreyScale pic2("output/result13.pgm");
	Display(pic2,2,"new file");
	//sleep(1);
	
	GreyScale pic3("bilder/shuttle.pgm");
	pic3.SetFormat(GreyScale::HuffmanA)
		.ToFile("output/result17.pgm");
	GreyScale pic4("output/result17.pgm");
	Display(pic4,4,"new file");
	//sleep(1);
}

void thirdA(){
	GreyScale pic1("bilder/roentgen.pgm");
	pic1.SetFormat(GreyScale::HuffmanB)
		.ToFile("output/result14.pgm");
	GreyScale pic2("output/result14.pgm");
	Display(pic2,3,"new file");
	sleep(1);
	
	GreyScale pic3("bilder/shuttle.pgm");
	pic3.SetFormat(GreyScale::HuffmanB)
		.ToFile("output/result18.pgm");
	GreyScale pic4("output/result18.pgm");
	Display(pic4,3,"new file");
	sleep(1);
}

int main(int argc, const char* argv[]){
	if     (*argv[1] == '1') firstA();
	else if(*argv[1] == '2') secondA();
	else if(*argv[1] == '3') thirdA();
}
