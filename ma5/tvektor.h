#ifndef _TVEKTOR_H		// damit der Header nicht mehrfach
#define _TVEKTOR_H		// eingelesem wird

#include <iostream>
#include <cmath>

// je nach Datentyp verwende (richtige) Betragsfunktion
template < typename T > inline T Norm (T x)
{
  return T (fabs (x));
}

inline long double
Norm (long double x)
{
  return fabsl (x);
}

// Vorwärts-Deklaration der Klasse TVektor, notwendig für die Vorwärts-Deklaration der Friend-Operatoren, da diese schon auf Objekten vom Typ TVektor arbeiten sollen.
template < typename T > class TVektor;

// Vorwärts-Deklaration der Friend-Operatoren, notwendig, weil sie schon bekannt sein müssen, damit sie innerhalb der Klassendeklaration als Freunde angegeben werden können.
template < typename T > TVektor < T > operator + (const TVektor < T > &, const TVektor < T > &);
template < typename T > TVektor < T > operator - (const TVektor < T > &, const TVektor < T > &);
template < typename T > TVektor < T > operator - (const TVektor < T > &);

template < typename T >  T operator * (const TVektor < T > &, const TVektor < T > &);

template < typename T > TVektor < T > operator * (T c, const TVektor < T > &);
template < typename T > TVektor < T > operator * (const TVektor < T > &, T c);
template < typename T > TVektor < T > operator / (const TVektor < T > &, T c);

template < typename T >  int operator == (const TVektor < T > &, const TVektor < T > &);
template < typename T >  int operator != (const TVektor < T > &, const TVektor < T > &);

template < typename T > std::istream & operator >> (std::istream &, TVektor < T > &);
template < typename T > std::ostream & operator << (std::ostream &, const TVektor < T > &);


// Hier beginnt die eigentliche Deklaration des Klassentemplates

template < typename T >		// T steht hier fuer den Parameter, z.B.
  class TVektor			// int, float, double
{
private:
  T * Vek;			// Zeiger auf Feld fuer Vektorelemente; 'vec' in 'Vek' geaendert
  int Laeng;			// Vektorlaenge; 'len' in 'Laeng' geaendert

public:
  TVektor (int i = 1);		// Konstruktor mit Laengenangabe
  ~TVektor ()
  {
    delete[]Vek;		// 'vec' in 'Vek' geaendert
  }				// Destruktor
  TVektor (const TVektor &);	// Kopierkonstruktor

  T & operator  ()(int);	// Vektorelement schreiben
  T operator  () (int) const;	// Vektorelement lesen

  TVektor < T > &operator = (const TVektor < T > &);	// Zuweisung
  TVektor < T > &operator += (const TVektor < T > &);	// Zuweisungen mit arithm. Operation
  TVektor < T > &operator -= (const TVektor < T > &);
  TVektor < T > &operator *= (T c);
  TVektor < T > &operator /= (T c);

  TVektor < T > &ReDim (int);	// neue Laenge festlegen
  int Laenge () const
  {
    return Laeng;		// 'len' in 'Laeng' geaendert
  }				// Laenge
  long double Norm2 () const;	// Euklidische Norm des Vektors
  T NormMax () const;		// Maximum-Norm des Vektors
  T NormMax (int &) const;	// Hilfsprogram


  // Addition, Subtraktion, Aendern des Vorzeichens
  friend TVektor < T > operator + <> (const TVektor < T > &, const TVektor < T > &);
  friend TVektor < T > operator - <> (const TVektor < T > &, const TVektor < T > &);
  friend TVektor < T > operator - <> (const TVektor < T > &);

  // Skalarprodukt
  friend T operator * <> (const TVektor < T > &, const TVektor < T > &);

  friend TVektor < T > operator * <> (T c, const TVektor < T > &);	// konstante Vielfache
  friend TVektor < T > operator * <> (const TVektor < T > &, T c);
  friend TVektor < T > operator / <> (const TVektor < T > &, T c);

  friend int operator == <> (const TVektor < T > &, const TVektor < T > &);	// Vergleich
  friend int operator != <> (const TVektor < T > &, const TVektor < T > &);

  friend std::istream & operator >> <> (std::istream &, TVektor < T > &);	// Eingabe
  friend std::ostream & operator << <> (std::ostream &, const TVektor < T > &);	// Ausgabe

  static void VekFehler (const char str[]);	// Fehlermeldung ausgeben; static

};

#include "tvektor.tpp"		// wichtig fuer Template!


#endif
