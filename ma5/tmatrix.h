#ifndef _TMATRIX_H		// tmatrix.h nicht doppelt benutzen
#define _TMATRIX_H

#include <iostream>


#include "tvektor.h" // einige Operatoren müssen auf TVektoren operieren, darum muss dieses Klassentemplate hier schon bekannt sein


// Vorwärts-Deklaration der Klasse TMatrix, notwendig für die Vorwärts-Deklaration der Friend-Operatoren, da diese schon auf Objekten vom Typ TMatrix arbeiten sollen.
template < typename T > class TMatrix;


// Vorwärts-Deklaration der Friend-Operatoren, notwendig, weil sie schon bekannt sein müssen, damit sie innerhalb der Klassendeklaration als Freunde angegeben werden können.
template < typename T > TMatrix < T > operator + (const TMatrix < T > &,
					       const TMatrix < T > &);
template < typename T > TMatrix < T > operator - (const TMatrix < T > &,
					       const TMatrix < T > &);
template < typename T > TMatrix < T > operator - (const TMatrix < T > &);

template < typename T > TMatrix < T > operator * (const TMatrix < T > &,
					       const TMatrix < T > &);
template < typename T > TMatrix < T > operator * (const T c,
					       const TMatrix < T > &);
template < typename T > TMatrix < T > operator * (const TMatrix < T > &,
					       const T c);
template < typename T > TMatrix < T > operator / (const TMatrix < T > &,
					       const T c);

template < typename T > int operator == (const TMatrix < T > &,
				      const TMatrix < T > &);
template < typename T > int operator != (const TMatrix < T > &,
				      const TMatrix < T > &);

template < typename T > std::istream & operator >> (std::istream &, TMatrix < T > &);
template < typename T > std::ostream & operator << (std::ostream &, const TMatrix < T > &);

template < typename T > TVektor < T > operator * (const TMatrix < T > &,
					       const TVektor < T > &);
template < typename T > TVektor < T > operator * (const TVektor < T > &,
					       const TMatrix < T > &);

// Hier beginnt die eigentliche Deklaration des Klassentemplates

template < typename T > class TMatrix
{
private:
  T * Mat;			// Zeiger auf Feld fuer Matrixelemente; 'mat' in 'Mat' geaendert
  int Zeil, Spalt;		// Matrixdimension; 'rows' und 'cols' in 'Zeil' bzw. 'Spalt' geaendert

public:
  TMatrix (int ro = 1, int co = 1);	// Konstruktor mit Laengenangabe
  ~TMatrix ()
  {
    delete[]Mat;		// 'mat' in 'Mat' geaendert
  }				// Destruktor
  TMatrix (const TMatrix < T > &);	// Kopierkonstruktor

  T & operator  ()(int, int);	// Matrixelement schreiben
  T operator  () (int, int) const;	// Matrixelement lesen

  TMatrix < T > &operator = (const TMatrix < T > &);	// Zuweisung
  TMatrix < T > &operator += (const TMatrix < T > &);	// Zuweisungen mit arithm. Operation
  TMatrix < T > &operator -= (const TMatrix < T > &);
  TMatrix < T > &operator *= (const TMatrix < T > &);
  TMatrix < T > &operator *= (const T);
  TMatrix < T > &operator /= (const T);

  TMatrix < T > &ReDim (int, int);	// neue Dimensionen festlegen
  TMatrix < T > &Copy (const TMatrix < T > &);	// Matrix kopieren (neu fuer A5)
  int Zeilen () const
  {
    return Zeil;		// 'rows' in 'Zeil' geaendert
  }				// Zeilen
  int Spalten () const
  {
    return Spalt;		// 'cols' in 'Spalt' geaendert
  }				// Spalten



  friend TMatrix < T > operator + <> (const TMatrix < T > &, const TMatrix < T > &);	// Addition
  friend TMatrix < T > operator - <> (const TMatrix < T > &, const TMatrix < T > &);	// Subtraktion
  friend TMatrix < T > operator - <> (const TMatrix < T > &);	// Vorzeichen

  friend TMatrix < T > operator * <> (const TMatrix < T > &, const TMatrix < T > &);	// Matrix mult.
  friend TMatrix < T > operator * <> (const T c, const TMatrix < T > &);	// Vielfache
  friend TMatrix < T > operator * <> (const TMatrix < T > &, const T c);
  friend TMatrix < T > operator / <> (const TMatrix < T > &, const T c);

  friend int operator == <> (const TMatrix < T > &, const TMatrix < T > &);	// Vergleich
  friend int operator != <> (const TMatrix < T > &, const TMatrix < T > &);

  friend std::istream & operator >> <> (std::istream &, TMatrix < T > &);	// Eingabe
  friend std::ostream & operator << <> (std::ostream &, const TMatrix < T > &);	// Ausgabe

  friend TVektor < T > operator * <> (const TMatrix < T > &, const TVektor < T > &);	// Matrix-Vektor-
  friend TVektor < T > operator * <> (const TVektor < T > &, const TMatrix < T > &);	// Multiplikation

  void MatFehler (const char str[]) const;	// Fehlermeldung ausgeben


};



#include "tmatrix.tpp"		// wegen Templates notwendig!


#endif
