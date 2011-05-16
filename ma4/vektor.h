/***********************************************
*  Name        : vektor.h                      *
*  Verwendung  : Header zu Vektorklasse        *
*  Autor       : V. Reichelt, IGPM RWTH Aachen *
*  Datum       : Nov '96 - Mai '00             *
*  Aktualisiert: K. Brix, Apr '07              *
***********************************************/

#ifndef _VEKTOR_H                         // vektor.h nicht doppelt benutzen
#define _VEKTOR_H

#include <iostream>

class Matrix;                             // fuer friend Matrix * Vektor etc.

class Vektor
{
  private:
    double* Vek;                          // Zeiger auf Feld fuer Vektorelemente
    int     Laeng;                        // Vektorlaenge

  public:
    Vektor  (const int l=1);              // Konstruktor mit Laengenangabe
    ~Vektor () {if (Vek) delete[] Vek; }  // Destruktor
    Vektor  (const Vektor&);              // Kopierkonstruktor

    double& operator () (const int);        // Zugriff auf Einträge des Vektors
    double  operator () (const int) const;  // Zugriff auf falls Vektor const

    Vektor& operator =  (const Vektor&);  // Zuweisung
    Vektor& operator += (const Vektor&);  // Zuweisungen mit arithm. Operation
    Vektor& operator -= (const Vektor&);
    Vektor& operator *= (const double);
    Vektor& operator /= (const double);

    Vektor& ReDim   (const int);                // neue Laenge festlegen
    int     Laenge  () const { return Laeng; }  // Laenge
    double  Norm2   () const;                   // Euklidische Norm des Vektors
    double  NormMax () const;                   // Maximum-Norm des Vektors
    double  NormMax (int& maxIndex) const;                   // Maximum-Norm des Vektors

    static void VekFehler (const char str[]);   // Fehlermeldung ausgeben

    friend Vektor   operator +  (const Vektor&, const Vektor&); // Addition
    friend Vektor   operator -  (const Vektor&, const Vektor&); // Subtraktion
    friend Vektor   operator -  (const Vektor&);                // Vorzeichen

    friend double   operator *  (const Vektor&, const Vektor&); // Skalarprodukt
    friend Vektor   operator *  (const double,  const Vektor&); // Vielfache
    friend Vektor   operator *  (const Vektor&, const double);
    friend Vektor   operator /  (const Vektor&, const double);

    friend bool     operator == (const Vektor&, const Vektor&); // Vergleich
    friend bool     operator != (const Vektor&, const Vektor&);

    friend std::istream& operator >> (std::istream&, Vektor&);       // Eingabe
    friend std::ostream& operator << (std::ostream&, const Vektor&); // Ausgabe

    friend Vektor   operator *  (const Matrix&, const Vektor&); // Matrix-Vektor-
    friend Vektor   operator *  (const Vektor&, const Matrix&); // Multiplikation
};

#endif
