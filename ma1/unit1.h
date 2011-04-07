/****************************************************************
*  Name       : unit1.h                                         *
*  Verwendung : Schnittstelle zu Praktikumsumgebung (MAPRA),    *
*               Nullstellen eines quadratischen Polynoms        *
*               Demonstration von Ausloeschung und Ueberlauf    *
*  Autor      : V. Reichelt, IGPM RWTH Aachen                   *
*  Datum      : Okt '96                                         *
*  Aenderung  : Okt '99                                         *
*  Sprache    : C++                                             *
****************************************************************/

// Zugriff auf mathematische Funktionen ermoeglichen:

#include <cmath>

// Falls DBL_MAX noch nicht definiert ist, gibt's den Wert vielleicht
// in values.h.

#ifndef DBL_MAX
#include <values.h>
#endif

const double DBL_ROOT = sqrt(DBL_MAX);

// In der Praktikumsumgebung definierte Konstanten, die durch das
// C++-Schluesselwort "extern" beim Einbinden dieses Header-Files
// in "meina1.cpp" sichtbar werden:

extern const int AnzahlBeispiele;
extern const int Unendlich;

// Funktionen aus der Praktikumsumgebung, die durch Einbinden der
// Funktionskoepfe fuer das Programm "meina1.cpp" zugreifbar werden:

void Start ( int Bsp, double &a, double &b, double &c );
void Ergebnis ( int Anzahl, bool IstKomplex=false, double x1=0, double x2=0 );

void print(const int& bsp, const double &a, const double &b, const double &c);
void find(double &a, double &b, double &c);
void quadsolv(double p, double q);
