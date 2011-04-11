/***********************************************************
*  Name       : meina1.cpp                                 *
*  Verwendung : Loesung der ersten Praktikumsaufgabe,      *
*               Nullstellen eines quadratischen Polynoms   *
*  Autor      :                                            *
*  Datum      :                                            *
*  Sprache    : C++                                        *
***********************************************************/

#include <iostream>
#include "unit1.h"

// ===== Hauptprogramm =====

int main()
{
	double a,b,c;
	
	 // Hier kommt nun Ihr Programm; viel Erfolg!
	for(unsigned char bsp = 1; bsp<14; bsp++){
		Start(bsp,a,b,c);
		print(bsp, a,b,c);
		find(a,b,c);
	}
  return 0;
}

void print(const int &bsp, const double &a, const double &b, const double &c){
	std::cout << "bsp:\t" << bsp << "\na:\t" << a << "\nb:\t" << b << "\nc:\t" << c << "\n";
}

void find ( double &a, double &b, double &c ){
	if( a == 0 && b == 0)
		//constant
		if(c!=0) return Ergebnis(0);
		else return Ergebnis(Unendlich);
	else if( a == 0 ) // b != 0
		//linear
		//bx+c = 0 <=> x=-c/b
		return Ergebnis(1,false,-c/b);
	else // a != 0
		//quadratic
		if(c == 0)
			//ax²+bx = x(ax+b) = 0 <=> x = 0 v x = -b/a 
			if(b!=0) return Ergebnis(2,false,-b/a,0);
			else return Ergebnis(1,false,0);
		else{ //a != 0 && c != 0
			return quadsolv(b/a,c/a);
		}
}

/*
	gets roots of quadratic function.
	prerequisites: a!=0 && c!=0
*/

void quadsolv(double p, double q){
	double root;
	int real;
	if( std::abs(p) > DBL_ROOT * 2){ //p²/4 too large!
			real = (.25 - (q/p)/p >= 0 ) ? 1 :-1;
		root = std::abs(p) * sqrt(real * (.25 - (q/p)/p));
	}
	else{
		real = (p/4*p-q >= 0) ? 1 : -1;
		root = sqrt( real * (p/4*p-q) );
	}
	if ( root == 0 ){
		return Ergebnis( 1, false, -p/2);
	}
	else if ( real == 1){
		double x = - p/2 - (p>0?1:-1) * root;
		// xy=q <=> y=q/x
		double y = q/x;
		return Ergebnis(2,false, x,y);
	}
	else{ //real == -1
		return Ergebnis(2,true,-p/2,root);
	}
}

/*void quadsolv(double &a, double &b, double &c){
	double p=b/a; double q = c/a;
	double root;
	int real;
	if( std::abs(p) > DBL_ROOT * 2){
		std::cout << "big!" <<.25 -(q/p)/p;
		real = .25-(q/p)/p<0?-1:1;
		root = std::abs(b) * sqrt(real * (1/4-(q/p)/p));
	}
	else{
		real = (b/4*b-c<0)?-1:1;
		root = sqrt(real * (b/4*b-c));
	}
	
			std::cout << "--- real: "<< real <<" ---";
	
	if(root == 0)
		return Ergebnis(1,false,-b/2);
	else if(real == 1){
		double x = - b/2 - (b>0?1:-1) * root;
		double y = c/x;
		return Ergebnis(2,false,x,y);
	}
	else{ //real == -1
		Ergebnis(2,true,-b/2,root);
	}
}*/
