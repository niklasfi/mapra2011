#include <cmath>
#include <iostream>

#include "tvektor.h"
#include "tmatrix.h"
#include "unit5.h"

using namespace std;

void RKSchritt(FunktionVF f, real &t, Vektor &y, real &h){

	int m = Delta.Laenge();
	real e = 1.0/0.0;			// stellt sicher, dass wir in der Schleife gehen

	Vektor K[m+1];

		while (e >= eps){
			
			// Erstellen von Liste von K's werten
			K[1] = f(t+Alpha(0)*h, y);		// K(0) ignoriert, um Verwirrung mit Indices im Blatt zu vermeiden
	
				for (int j = 2; j <= m ; j++){
					Vektor Ksubsum(y.Laenge());				// Hilfssumme um K(j) zu berechnen
						for (int l = 1; l < j ; l++) 
								Ksubsum += Beta(j,l)*K[l];	// Summe in K[j]
					K[j] = f(t + Alpha(j)*h, y + h*Ksubsum);
				}
				
			// neue Abschaetzung von e
			Vektor hsubsum(y.Laenge());
				for (int l = 1; l <= m; l++) 
						hsubsum += Delta(l)*K[l];
			e = (h*hsubsum).NormMax();		
			
			// neuer Wert von h erstellen
			real c = 0.9*pow( eps/e , 1/(Ordnung+1));
	
			if (c < 0.1) 
					h *= 0.1;
			if (c > 5)
					h *= 5;
			else	h = c;
		}	

	// y(t+h) berechnen
	Vektor ysubsum(y.Laenge());
		for (int l = 1; l <= m; l++) 
				ysubsum += Gamma(l)*K[l];
	y = y + h*ysubsum;
	
	// neues t berechnen
	t = t + h;
}


int main(){

int Bsp, Grafik, Ausgabe;

	Vektor Masse, y0;
	FunktionVF f;
	real tAnf, tEnd, h0;



		cout << "beispiel?\n";
		cin >> Bsp;
		if (Bsp > AnzahlBeispiele) cerr << "Beispiel nicht vorhanden! \n";
		cout << "grafik?\n";
		cin >> Grafik;

	Start ( Bsp, Masse, f, y0, tAnf, tEnd, h0, Grafik, Ausgabe);

	real h = h0, t = tAnf;
	Vektor y = y0;

		while (t < tEnd){
			RKSchritt(f, t, y, h);
			Schritt_Ausgabe (t, y, Grafik, Ausgabe);
		}
	
	Ergebnis (t, y, Ausgabe);
	
	return 0;	
}















