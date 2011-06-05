/*****************************************************
*  Name       : RuKu.cpp                             *
*  Verwendung : Runge-Kutta-Verfahren		         *
*  Autor      : Jee Siang, Soh; Niklas Fischer       *
*  Datum      : Mai/ Juni '2011                      *
*****************************************************/


#include "tvektor.h"
#include "tmatrix.h"
#include "unit5.h"

#include <cmath>
#include <iostream>

using namespace std;

int m = Delta.Laenge();				// 'm' im Blatt erstellen

Vektor y0, tlist(2), hlist(2), ytilda[2], K[m+1];
FunktionVF f;
real tAnf, tEnd, h0;

tlist(0)= tAnf;
hlist(0)= h0;
ytilda(0).ReDim(y0.Laenge());
ytilda(1).ReDim(y0.Laenge());


int i = 0;


void RKSchritt (f, real &t, Vektor &y, real &h){

	if (t < tEnd){
		Kfunc();		// Liste fuer K im i-ten Schritt zu erstellen
		hnew();			// Neue Schrittweite zu berechnen
		ynew();			// Neue y-wert zu berechnen
		i++;
	}	

y = ytilda(i%2);
h = hlist(i%2);

};


// Hilfsfunktionen:


void Kfunc(){												// Liste fuer K im i-ten Schritt zu erstellen
	
	K(1) = f(tlist(i%2)+Alpha(0)*hlist(i%2), ytilda(i%2));	// K(0) ignoriert, um Verwirrung mit Indices im Blatt zu 
															// vermeiden
	
	for (int j = 2; j <= m ; j++){
		Vektor Ksubsum(y0.Laenge());								// Hilfssumme um K(j) zu berechnen

			for (int l = 1; l < j ; l++) Ksubsum += Beta(j,l)*K(l);	// Summe in K(j)

		K(j) = f(tlist(i%2) + Alpha(j)*hlist(i%2), ytilda(i%2) + hlist(i%2)*Ksubsum);
	
	}
	
};



void hnew(){						// Neue Schrittweite zu berechnen
	
	Vektor hsubsum(y0.Laenge());
	
		for (int l = 1; l <= m; l++) hsubsum += Delta(l)*K(l);
	
	real c = 0.9*pow( eps/((hlist(i%2)*hsubsum).NormMax()) , 1/(p+1) );
	
		if (c < 0.1) 
			hlist((i+1)%2) = hlist(i%2)*0.1;
		if (c > 5)
			hlist((i+1)%2) = hlist(i%2)*5;
		else hlist((i+1)%2) = c;

};



void ynew(){						// Neue y-wert zu berechnen

	Vektor ysubsum(y0.Laenge());
	
		for (int l = 1; l <= m; l++) ysubsum += Gamma(l)*K(l);
	
	ytilda((i+1)%2) = ytilda(i%2) + hlist(i%2)*ysubsum;

};
