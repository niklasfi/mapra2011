#ifndef _TVEKTOR_H
#include "tvektor.h"
#endif

#ifndef _TMATRIX_H
#include "tmatrix.h"
#endif

typedef long double real;
typedef TVektor < real > Vektor;
typedef TMatrix < real > Matrix;


// Anzahl der Beispielfunktionen
extern const int AnzahlBeispiele;

// Gravitationskonstante
const real Grav = 6.67e-11;

// Koeffizienten fuer das Runge-Kutta-Verfahren
extern Vektor Alpha, Gamma, Delta;
extern Matrix Beta;
extern int Ordnung;
extern real eps;

// Funktionstyp zum Uebergeben der rechten Seite der DGL
typedef Vektor (*FunktionVF) (real t, const Vektor & y);

// siehe Uebungsblatt

void Start (int Bsp, Vektor & Masse, FunktionVF & f, Vektor & y0,
	    real & tAnf, real & tEnd, real & h0, int Grafik, int Ausgabe = 1);

void Schritt_Ausgabe (real t, const Vektor & y, int Grafik, int Ausgabe = 1);

void Ergebnis (real t, const Vektor & y, int Ausgabe = 1);
