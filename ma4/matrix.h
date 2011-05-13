#pragma once
#include <iostream>

class Vektor;                             // fuer friend Matrix * Matrix etc.

class Matrix
{
  private:
    double* Mat;                          // Zeiger auf Feld fuer Matrixelemente
    int     Zeil, Spalt;                        // Matrixlaenge

  public:
    Matrix  (const int h=1, const int w = 1);              // Konstruktor mit Laengenangabe
    ~Matrix () {if (Mat) delete[] Mat; }  // Destruktor
    Matrix  (const Matrix&);     // Kopierkonstruktor

    double& operator () (const int, const int);        // Zugriff auf Einträge des Matrixs
    double  operator () (const int, const int) const;  // Zugriff auf falls Matrix const

    Matrix& operator =  (const Matrix&);  // Zuweisung
    Matrix& operator += (const Matrix&);  // Zuweisungen mit arithm. Operation
    Matrix& operator -= (const Matrix&);
    Matrix& operator *= (const double);
    Matrix& operator /= (const double);

    Matrix& ReDim   (const int, const int);                // neue Größe festlegen
    int     Zeilen  () const { return Zeil; }  // Zeilen
    int     Spalten  () const { return Spalt; }  // Zeilen
    double  Norm2   () const;                   // Euklidische Norm des Matrixs
    double  NormMax () const;                   // Maximum-Norm des Matrixs

    static void MatFehler (const char str[]);   // Fehlermeldung ausgeben

    friend Matrix   operator +  (const Matrix&, const Matrix&); // Addition
    friend Matrix   operator -  (const Matrix&, const Matrix&); // Subtraktion
    friend Matrix   operator -  (const Matrix&);                // Vorzeichen

    friend Matrix   operator *  (const double,  const Matrix&); // Vielfache
    friend Matrix   operator *  (const Matrix&, const double);
    friend Matrix   operator /  (const Matrix&, const double);

    friend bool     operator == (const Matrix&, const Matrix&); // Vergleich
    friend bool     operator != (const Matrix&, const Matrix&);

    friend std::istream& operator >> (std::istream&, Matrix&);       // Eingabe
    friend std::ostream& operator << (std::ostream&, const Matrix&); // Ausgabe

    friend Matrix   operator *  (const Matrix&, const Matrix&); // Matrix-Matrix-
    friend Vektor   operator *  (const Matrix&, const Vektor&); // Multiplikation
    friend Vektor   operator *  (const Vektor&, const Matrix&); // Multiplikation
};
