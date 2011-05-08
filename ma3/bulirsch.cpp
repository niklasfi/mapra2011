#include "bulirsch.h"

bool Bul::grafik, Bul::ausgabe;

Bul::Bul(Funktion f):f(f){}

double Bul::integrate(double a, double b, double eps){
	if(b==a) return 0;		// trivialer Fall
	
	index = 0;			// Initialiserung von "index"
	
	this->eps = eps;
	this->minus = b < a;		
	
	if(minus){			// Falls b < a
		this->a = b;
		this->h0 = a-b;
	}
	else{				// falls b > a
		this->a = a;
		this->h0 = b-a;
	}
	
	extrapol[0]=stepInit();
	
	print();
	
	while(extrapolate() > eps);
	
	double res = (minus?-1:1)*extrapol[index];
	
	Schluss (res,eps,extrapol,index);
	
	return res;
}

int Bul::numparts(int i){ 		// spart speicher :), definiert "N"
	if(i==0) return 1;
	if(i%2) return 1<<((i+1)/2); 	// i odd
	else return 3*(1<<(i/2-1)); 	// i even
}

double Bul::stepOnce(){			// berechnet T[index,0]
	if(index==0)
		return stepInit();
	if(index % 2)
		return stepOdd();
	else
		return stepEven();
}

double Bul::stepInit(){				// Initialisierung von f fuer die ersten Schritt = T[0,0]
	double l = f(a);
	double r = f(a+h0);			// a+h0 = b
	all = (l+r)/2;				// Initialiserung von "all", Speichern von 
	even=0;					// Speichern von alle Berechnungen im Fall index=even
	return all*h0;
}

double Bul::stepEven(){ 				// wird ausgeführt, wenn index % 2 == 0
	int till = numparts(index);			// numparts: even, Anzahl von Teile
	double h = h0/till;				// Schrittlaenge im "index"-ten Schritt erstellen

	for(int j = 1; j < till; j+=(index>2?2:1)){	// Die in vorherigen "even" berechneten Punkte vermeiden
		if( j % 3 == 0) continue;		// Die in "odd" berechneten Punkte vermeiden
		double fx = f(a+h*j);			// Falls j % 3 != 0
		even+= fx;
	}
	
	double sigma = even + all;
	all += odd;
	return h * sigma;
}

double Bul::stepOdd(){ 				// wird ausgeführt (wie beim Romberg Verfahren), wenn index % 2 == 1
	int till = numparts(index);		
	double h = h0/till;			
	
	odd = 0;				// Speichern von alle Berechnungen im Fall index = odd
	
	for(int j = 1; j < till; j+= 2){
		double fx = f(a+h*j);
		odd += fx;
	}
	
	return h*(odd + all);
}

double Bul::extrapolate(){			//wie im Romberg Verfahren
	index ++;

	double tdiag[2];
	
	tdiag[0] = extrapol[0];
	extrapol[0] = stepOnce();
	
	for(int j = 1; j<=index; j++){
		tdiag[j % 2] = extrapol[j];
		double hpart = double(numparts(index))/numparts(index-j);
		
		extrapol[j] = extrapol[j-1] + (extrapol[j-1]-tdiag[(j-1)%2])/(hpart*hpart -1);
	}
	
	print();
	
	return fabs(extrapol[index]-extrapol[index-1]);
}

void Bul::print(){
	if (ausgabe){
		Ausgabe(index,extrapol);
	}
}
