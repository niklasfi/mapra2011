#include "unit4.h"
#include <cmath>
#include <iostream>

int main(int argc, char *argv[]){
	if(argc == 1){
		std::cout << "usage: powerit.exe bspNummer\n";
		exit(1);
	}
	
	int bsp = ui2::readarg<int>((std::string)argv[1],"konnte Beispielnummer liegt nicht im richtigen Zahlenbereich.", ui2::check_range<int>(1,AnzahlBeispiele));

	Matrix A; Vektor x[2]; double eps;
	
	Start (bsp, A, x[0], eps );

	x[1].ReDim(x[0].Laenge());
	
	Vektor xTild[2];
	
	xTild[0].ReDim(x[0].Laenge());
	xTild[1].ReDim(x[0].Laenge());
	
	xTild[0](0) = 1.0/0.0; //stellt sicher, dass man nicht sofort aus der while-schleife rausfliegt

	int i = 1, k = 0;
	
	while(true){
		xTild[i % 2] = A * x[(i-1) % 2];
		
		x[i % 2] = xTild[i % 2] / xTild[i % 2](k);
		
		if ((x[0]-x[1]).NormMax() < eps && fabs(xTild[0](k) - xTild[1](k)) < eps) break;
		
		int max;
		if(2 * fabs(xTild[i % 2](k)) <= xTild[i % 2].NormMax(max))
			k = max;
		
		i++;
	}
	
	Ergebnis ( x[i%2], xTild[i%2](k), i );
}
