/***********************************************
*  Name       : vektor.tpp                     *
*  Verwendung : Vektorklasse                   *
*  Autor      :                                *
*  Datum      :                                *
***********************************************/

#include "tvektor.h"
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std;

// =======================
//      Konstruktoren
// =======================


// ----- Konstruktor -----
template < typename T >
TVektor<T>::TVektor(const int l)
{
    if (l <= 0)
	VekFehler("Nur Vektoren mit positiver Laenge!");

    Laeng = l;

    Vek = new(nothrow) T[l];
    if (Vek == NULL)
	VekFehler("Nicht genuegend Speicher!");

    for (int i = 0; i < l; i++)
	(*this) (i) = 0;
}


// ----- Kopierkonstruktor -----
template < typename T >
TVektor<T>::TVektor(const TVektor & x)
{
    Laeng = x.Laeng;

    Vek = new(nothrow)  T[Laeng];
    if (Vek == NULL)
	VekFehler("Nicht genuegend Speicher!");

    for (int i = 0; i < Laeng; i++)
	(*this) (i) = x(i);
}


// ===========================================
//      Vektorelement schreiben und lesen
// ===========================================


// ----- Schreib- und Lesezugriff auf Vektorelemente -----
template < typename T >
T &TVektor<T>::operator () (const int i) {
	#ifndef NOBOUNDS
    if (i < 0 || i >= Laeng)
		VekFehler("Ungueltiger Index!");
	#endif
	
    return Vek[i];
}


// ----- Lesezugriff auf Elemente konstanter Vektoren -----
template < typename T >
T TVektor<T>::operator () (const int i) const {
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
template < typename T >
TVektor<T> & TVektor<T>::operator =(const TVektor<T> & x)
{
    if (Laeng != x.Laeng)
	VekFehler("Inkompatible Dimensionen fuer 'Vektor = Vektor'!");

    for (int i = 0; i < Laeng; i++)
	(*this) (i) = x(i);

    return *this;
}


// ----- Zuweisungsoperator mit Addition "+=" ----
template < typename T >
TVektor<T> & TVektor<T>::operator +=(const TVektor<T> & x)
{
	if(Laeng != x.Laeng) VekFehler("um zwei vektoren addieren zu können müssen sie die gleiche Dimension haben");
	
	for(int i = 0; i<Laeng; i++)
		(*this)(i) += x(i);
	return *this;
}


// ----- Zuweisungsoperator mit Subtraktion "-=" ----
template < typename T >
TVektor<T> & TVektor<T>::operator -=(const TVektor<T> & x)
{
	if(Laeng != x.Laeng) VekFehler("um zwei vektoren addieren zu können müssen sie die gleiche Dimension haben");
	
	for(int i = 0; i<Laeng; i++)
		(*this)(i) -= x(i);
	return *this;
}


// ----- Zuweisungsoperator mit Multiplikation "*=" ----
template < typename T >
TVektor<T> & TVektor<T>::operator *=(const T c)
{
	for(int i = 0; i<Laeng; i++)
		(*this)(i) *= c;
	return *this;
}


// ----- Zuweisungsoperator mit Divsion "/=" ----
template < typename T >
TVektor<T> & TVektor<T>::operator /=(const T c)
{	
	if (c==0)
		VekFehler("Teilen durch NULL nicht zulaessig!");
		
	for(int i = 0; i<Laeng; i++)
		(*this)(i) /= c;
	return *this;
}


// ==============================
//      Vektorlaenge aendern
// ==============================


// ----- Vektorlaenge aendern -----
template < typename T >
TVektor<T> & TVektor<T>::ReDim(const int l)
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
template < typename T >
long double TVektor<T>::Norm2() const
{
	T res = 0;
	for (int i = 0; i < Laeng; i++)
		res += (*this)(i)*(*this)(i);
	return sqrt(res);
}


// ----- Maximum-Norm -----
template < typename T >
T TVektor<T>::NormMax() const
{
	int max;
    return NormMax(max);
}

template < typename T >
T  TVektor<T>::NormMax (int& max) const{
	max = 0;								// Initialisierung von max
    for (int i = 0; i < Laeng; i++)
    	if(fabs((*this)(i))>fabs((*this)(max))) max = i;	// Vergleich der Absolute der einzelnen Eintraege
    														// Speichern der Stelle des bisher betragsgroessten Eintrags
    return fabs(Vek[max]);
}

// ==================================
//      arithmetische Operatoren
// ==================================


// ----- Addition "+" -----
template < typename T >
TVektor<T> operator +(const TVektor<T> & x, const TVektor<T> & y)
{
    if (x.Laeng != y.Laeng)
	TVektor<T>::VekFehler("Inkompatible Dimensionen fuer 'Vektor + Vektor'!");

    TVektor<T> z = x;
    return z += y;
}


// ----- Subtraktion "-" -----
template < typename T >
TVektor<T> operator -(const TVektor<T> & x, const TVektor<T> & y)
{
	if (x.Laeng != y.Laeng)
		TVektor<T>::VekFehler("Inkompatible Dimensionen fuer 'Vektor - Vektor'!");

    TVektor<T> z = x;
    return z -= y;}


// ----- Vorzeichen wechseln "-" -----
template < typename T >
TVektor<T> operator -(const TVektor<T> & x)
{
	TVektor<T> z = x;
	return z *= -1;
}


// ----- Skalarprodukt "*" -----
template < typename T >
T operator *(const TVektor<T> & x, const TVektor<T> & y)
{
	if (x.Laeng != y.Laeng)
		TVektor<T>::VekFehler("Inkompatible Dimensionen fuer 'Skalarprodukt'!");
	
	double res = 0;
	for(int i = 0; i < x.Laeng; i++)
		res += x(i)*y(i);
	
	return res;
}


// ----- Multiplikation Skalar*Vektor "*" -----
template < typename T >
TVektor<T> operator *(const T c, const TVektor<T> & x)
{
    TVektor<T> z = x;
    return z*=c;
}


// ----- Multiplikation Vektor*Skalar "*" -----
template < typename T >
TVektor<T> operator *(const TVektor<T> & x, const T c)
{
	return c*x;
}


// ----- Division Vektor/Skalar "/" -----
template < typename T >
TVektor<T> operator /(const TVektor<T> & x, const T c)
{
	if (c==0)
		TVektor<T>::VekFehler("Teilen durch NULL nicht zulaessig!");
		
	TVektor<T> z = x;
	return z /= c;
}


// ==============================
//      Vergleichsoperatoren
// ==============================


// ----- Test auf Gleichheit "==" -----
template < typename T >
bool operator ==(const TVektor<T> & x, const TVektor<T> & y)
{
    if (x.Laeng != y.Laeng)
	return false;

    for (int i = 0; i < x.Laeng; i++)
	if (x(i) != y(i))
	    return false;

    return true;
}


// ----- Test auf Ungleichheit "!=" -----
template < typename T >
bool operator !=(const TVektor<T> & x, const TVektor<T> & y)
{
	return !(x == y);
}


// ==========================
//      Ein- und Ausgabe
// ==========================


// ----- Ausgabe "<<" -----
template < typename T >
ostream & operator <<(ostream & s, const TVektor<T> & x)
{
    s << setiosflags(ios::right);
   	for (int i = 0; i < x.Laeng; i++)
		s << "\n(" << setw(4) << i << ") " << x(i);

    return s << endl;
}


// ----- Eingabe ">>" -----
template < typename T >
istream & operator >>(istream & s, TVektor<T> & x)
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
template < typename T >
void TVektor<T>::VekFehler(const char str[])
{
    cerr << "\nVektorfehler: " << str << '\n' << endl;
    exit(1);
}
