#include "romberg.h"

bool Rom::grafik;
bool Rom::ausgabe;

Rom::Rom(Funktion f):f(f){}

int Rom::numparts(int i){	// spart speicher :)
	return 1<<i;		// verdoppelt i, d.h. "N" im Blatt erstellen
}
	
double Rom::stepOnce(){			// berechnet T[index,0]
	int till = numparts(index);	// Anzahl von Teile
	double h = h0/numparts(index);	// Schrittlaenge im"index"-ten Schritt erstellen
	
	for(int j = 1; j < till; j+= 2)	// f an jeden "neuen" Stellen berechnen und zu "all" summieren
		all+=f(a+j*h);
		
	return all*h;
}

double Rom::stepInit(){			// Initialisierung von f fuer die ersten Schritt = T[0,0]
	all = (f(a)+f(a+h0))/2;		// Intialisierung von "all" zum Benutzen in stepOnce()
	return all*h0;
}
	
double Rom::extrapolate(){		
	index ++;				

	double tdiag[2];				// array aus 2 Stellen
	
	tdiag[0] = extrapol[0];				// Speichern von T[index-1,0]
	extrapol[0] = stepOnce();			// = T[index,0]
	
	for(int j = 1; j<=index; j++){		
		tdiag[j % 2] = extrapol[j];	// Speichern von T[index-1,j] an der im j-ten Schritt nicht zu
						// benutzenden Stelle fuer den (j+1)-ten Schritt
		double hpart = double(numparts(index))/numparts(index-j);
							// = h[i-k]/h[i] nach evtl. Abkuerzung
		
		extrapol[j] = extrapol[j-1] + (extrapol[j-1]-tdiag[(j-1)%2])/(hpart*hpart -1);
	}						// Extrapolationsformel benutzen
	
	print();					//Ausgabe(index, extrapol)
	
	return fabs(extrapol[index]-extrapol[index-1]); 
							// Differenz von T[i,i] und T[i,i-1] nehmen (Error abschaetzen)
}

void Rom::print(){
	if (ausgabe){
		Ausgabe(index,extrapol);
	}
}

double Rom::integrate(double a, double b, double eps, bool extrapolate){
	if(b==a) return 0;		// Trivialer Fall
	
	index = 0;			// Initialisierung von index
	
	this->eps = eps;
	this->minus = b < a;		
	
	if(minus){			// Falls b < a
		this->a = b;		
		this->h0 = a-b;
	}
	else{				// Fall a > b
		this->a = a;
		this->h0 = b-a;
	}
	
	double res;
	if(extrapolate) res= integrate_wisely(a,b,eps);	// Romberg mit extrapolation
	else res = integrate_dumb(a,b,eps); 		// Romberg ohne Extrapolation
	
	if(minus) res *= -1;
	
	Schluss (res,eps,extrapol,index);
	
	return res;	
}

double Rom::integrate_wisely(double a, double b, double eps){	// Romberg mit Extrapolation
	extrapol[0]=stepInit();		// = T[0,0]
	
	print();			// Ausgabe	
	
	while(extrapolate() > eps);	// Fehler bis zum Epsilon abschaetzen mit Extrapolation
	
	return extrapol[index];		// Abschaetzung mit Epsilon genauigkeit
}
double Rom::integrate_dumb(double a, double b, double eps){	// Trapezregel mit Romberg
	
	extrapol[0] = stepInit();				// = T[0,0]
	extrapol[1] = 1.0/0.0;					// = infinity
	
	print();						// Ausgabe
	
	while( fabs(extrapol[0] - extrapol[1]) > 3 * eps ){	// Vergleich von T[index,0] und T[index-1,0]
		index ++;
		extrapol[1] = extrapol[0];			// Speichern von T[index-1,0]
		extrapol[0] = stepOnce();			// Berechnen und Speichern von T[index,0]
		print();					// Ausgabe
	}
	
	return extrapol[0];
}
