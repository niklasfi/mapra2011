#include "main.h"

int main(int argc, char* argv[]){
	int beispiel; bool sehr_genau; bool grafik; 
	int _Verfahren;
	VerfahrensTyp Verfahren;
	
	std::cout << "beispiel?\n";
	std::cin>> beispiel;
	std::cout<< "sehrgebau?\n";
	std::cin>> sehr_genau;
	std::cout<< "grafik?\n";
	std::cin>> grafik;
	std::cout<< "Verfahren?\n"
		<< "\t 0:Trapezregel \n"
		<< "\t 1:Romberg \n"
		<< "\t 2:Bulirsch \n";
	std::cin>> _Verfahren; Verfahren = (VerfahrensTyp) _Verfahren;
	
	/*beispiel=4;
	sehr_genau=1;
	grafik=0;
	Verfahren=Trapezregel;*/
	
	Funktion f; double eps, a, b;
	
	Start( beispiel, sehr_genau, grafik, Verfahren, f, eps, a, b);	
	
	if(Verfahren == Trapezregel){
		Rom::grafik = grafik;
		Rom::ausgabe = true;
		Rom rom(f);
		rom.integrate(a,b,eps,false);
	}
	else if(Verfahren == Bulirsch){
		Bul::grafik = grafik;
		Bul::ausgabe = true;
		Bul bul(f);
		bul.integrate(a,b,eps);
	}
	else if(Verfahren == Romberg){
		Rom::grafik = grafik;
		Rom::ausgabe = true;
		Rom rom(f);
		rom.integrate(a,b,eps);
	}
}
