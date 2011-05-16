/***********************************************
*  Name       : vektor.cpp                     *
*  Verwendung : Vektorklasse                   *
*  Autor      :                                *
*  Datum      :                                *
***********************************************/

#include "vektor.h"
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std;

// =======================
//      Konstruktoren
// =======================


// ----- Konstruktor -----

Vektor::Vektor(const int l)
{
    if (l <= 0)
	VekFehler("Nur Vektoren mit positiver Laenge!");

    Laeng = l;

    Vek = new(nothrow) double[l];
    if (Vek == NULL)
	VekFehler("Nicht genuegend Speicher!");

    for (int i = 0; i < l; i++)
	(*this) (i) = 0;
}


// ----- Kopierkonstruktor -----

Vektor::Vektor(const Vektor & x)
{
    Laeng = x.Laeng;

    Vek = new(nothrow) double[Laeng];
    if (Vek == NULL)
	VekFehler("Nicht genuegend Speicher!");

    for (int i = 0; i < Laeng; i++)
	(*this) (i) = x(i);
}


// ===========================================
//      Vektorelement schreiben und lesen
// ===========================================


// ----- Schreib- und Lesezugriff auf Vektorelemente -----

double &Vektor::operator () (const int i) {
	#ifndef NOBOUNDS
    if (i < 0 || i >= Laeng)
		VekFehler("Ungueltiger Index!");
	#endif
	
    return Vek[i];
}


// ----- Lesezugriff auf Elemente konstanter Vektoren -----

double Vektor::operator () (const int i) const {
	#ifndef NOBOUNDS
    if (i < 0 || i >= Laeng)
		VekFehler("Ungueltiger Index!");
	#endif

    return Vek[i];
}


// =====================
//      Zuweisungen
// =====================

// ----- Zuweisungsoperator "=" ----

Vektor & Vektor::operator =(const Vektor & x)
{
    if (Laeng != x.Laeng)
	VekFehler("Inkompatible Dimensionen fuer 'Vektor = Vektor'!");

    for (int i = 0; i < Laeng; i++)
	(*this) (i) = x(i);

    return *this;
}


// ----- Zuweisungsoperator mit Addition "+=" ----

Vektor & Vektor::operator +=(const Vektor & x)
{
	if(Laeng != x.Laeng) VekFehler("um zwei vektoren addieren zu können müssen sie die gleiche Dimension haben");
	
	for(int i = 0; i<Laeng; i++)
		(*this)(i) += x(i);
	return *this;
}


// ----- Zuweisungsoperator mit Subtraktion "-=" ----

Vektor & Vektor::operator -=(const Vektor & x)
{
	if(Laeng != x.Laeng) VekFehler("um zwei vektoren addieren zu können müssen sie die gleiche Dimension haben");
	
	for(int i = 0; i<Laeng; i++)
		(*this)(i) -= x(i);
	return *this;
}


// ----- Zuweisungsoperator mit Multiplikation "*=" ----

Vektor & Vektor::operator *=(const double c)
{
	for(int i = 0; i<Laeng; i++)
		(*this)(i) *= c;
	return *this;
}


// ----- Zuweisungsoperator mit Divsion "/=" ----

Vektor & Vektor::operator /=(const double c)
{
	for(int i = 0; i<Laeng; i++)
		(*this)(i) /= c;
	return *this;
}


// ==============================
//      Vektorlaenge aendern
// ==============================


// ----- Vektorlaenge aendern -----

Vektor & Vektor::ReDim(const int l)
{
	if(Vek) delete[] Vek;
	if (l <= 0)
		VekFehler("Nur Vektoren mit positiver Laenge!");

    Laeng = l;

    Vek = new(nothrow) double[l];
    if (Vek == NULL)
		VekFehler("Nicht genuegend Speicher!");

    for (int h = 0; h < l; h++)
		(*this) (h) = 0;
	
	return *this;
}

// ======================
//      Vektornormen
// ======================


// ----- Euklidische Norm -----

double Vektor::Norm2() const
{
	double res = 0;
	for (int i = 0; i < Laeng; i++)
		res += (*this)(i)*(*this)(i);
	return sqrt(res);
}


// ----- Maximum-Norm -----

double Vektor::NormMax() const
{
	int max;
    return NormMax(max);
}
double  Vektor::NormMax (int& max) const{
	max = 0;
    for (int i = 0; i < Laeng; i++)
    	if(fabs((*this)(i))>fabs((*this)(max))) max = i;
    return abs(Vek[max]);
}

// ==================================
//      arithmetische Operatoren
// ==================================


// ----- Addition "+" -----

Vektor operator +(const Vektor & x, const Vektor & y)
{
    if (x.Laeng != y.Laeng)
	Vektor::VekFehler("Inkompatible Dimensionen fuer 'Vektor + Vektor'!");

    Vektor z = x;
    return z += y;
}


// ----- Subtraktion "-" -----

Vektor operator -(const Vektor & x, const Vektor & y)
{
	if (x.Laeng != y.Laeng)
		Vektor::VekFehler("Inkompatible Dimensionen fuer 'Vektor - Vektor'!");

    Vektor z = x;
    return z -= y;}


// ----- Vorzeichen wechseln "-" -----

Vektor operator -(const Vektor & x)
{
	Vektor z = x;
	return z *= -1;
}


// ----- Skalarprodukt "*" -----

double operator *(const Vektor & x, const Vektor & y)
{
	if (x.Laeng != y.Laeng)
		Vektor::VekFehler("Inkompatible Dimensionen fuer 'Skalarprodukt'!");
	
	double res = 0;
	for(int i = 0; i < x.Laeng; i++)
		res += x(i)*y(i);
	
	return res;
}


// ----- Multiplikation Skalar*Vektor "*" -----

Vektor operator *(const double c, const Vektor & x)
{
    Vektor z = x;
    return z*=c;
}


// ----- Multiplikation Vektor*Skalar "*" -----

Vektor operator *(const Vektor & x, const double c)
{
	return c*x;
}


// ----- Division Vektor/Skalar "/" -----

Vektor operator /(const Vektor & x, const double c)
{
	Vektor z = x;
	return z /= c;
}


// ==============================
//      Vergleichsoperatoren
// ==============================


// ----- Test auf Gleichheit "==" -----

bool operator ==(const Vektor & x, const Vektor & y)
{
    if (x.Laeng != y.Laeng)
	return false;

    for (int i = 0; i < x.Laeng; i++)
	if (x(i) != y(i))
	    return false;

    return true;
}


// ----- Test auf Ungleichheit "!=" -----

bool operator !=(const Vektor & x, const Vektor & y)
{
	return !(x == y);
}


// ==========================
//      Ein- und Ausgabe
// ==========================


// ----- Ausgabe "<<" -----

ostream & operator <<(ostream & s, const Vektor & x)
{
    s << setiosflags(ios::right);
   	for (int i = 0; i < x.Laeng; i++)
		s << "\n(" << setw(4) << i << ") " << x(i);

    return s << endl;
}


// ----- Eingabe ">>" -----

istream & operator >>(istream & s, Vektor & x)
{
    cout << setiosflags(ios::right);
    for (int i = 0; i < x.Laeng; i++) {
		cout << "\n(" << setw(4) << i << ") ";
		s >> x(i);
    }
    return s;
}


// ==========================
//      Fehlerbehandlung
// ==========================


// ----- Ausgabe der Fehlermeldung "str" -----

void Vektor::VekFehler(const char str[])
{
    cerr << "\nVektorfehler: " << str << '\n' << endl;
    exit(1);
}
