#include "meina3.h"

void Trapez(Funktion& f, double &eps, double &a, double &b){
	double h=b-a, sigma=(f(a)+f(b))/2, tcurrent=1.0/0.0, tprevious=0; //sigma
	Vektor v;
	
	while(fabs(tcurrent-tprevious)/3 >= eps){
		for(int j = 1; j < (b-a)/h; j+=2){
			double fx= f(a+j*h);
			sigma+=fx;
		}
		tprevious=tcurrent;
		tcurrent=sigma*h;
		h/=2;
		v[0]=tcurrent;
		Ausgabe(0,v);
		int y; std::cin >> y;
	}
	Schluss(tcurrent,eps,v,0);
}

int main(){
	int beispiel; bool sehr_genau; bool grafik; int _Verfahren; VerfahrensTyp Verfahren;
	
	/*std::cout << "beispiel?\n";
	std::cin>> beispiel;
	std::cout<< "sehrgebau?\n";
	std::cin>> sehr_genau;
	std::cout<< "grafik?\n";
	std::cin>> grafik;
	std::cout<< "Verfahren?\n"
		<< "\t 0:Trapezregel \n"
		<< "\t 1:Romberg \n"
		<< "\t 2:Bulirsch \n";
	std::cin>> _Verfahren; Verfahren = (VerfahrensTyp) _Verfahren;*/
	
	beispiel=1;
	sehr_genau=0;
	grafik=1;
	Verfahren=(VerfahrensTyp)0;
	
	Funktion f; double eps, a, b;
	
	Start( beispiel, sehr_genau, grafik, Verfahren, f, eps, a, b);	
	
	switch(Verfahren){
		case Trapezregel:
			Trapez(f,eps,a,b);
			break;
		default:
			;
	}
}
