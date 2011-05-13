/*****************************************************************
*  Name       : unit4.h                                          *
*  Verwendung : Schnittstelle zu Praktikumsumgebung (MAPRA),     *
*               Eigenwert/-vektorberechnung mit Potenzmethode    *
*  Autor      : V. Reichelt, IGPM RWTH Aachen                    *
*  Datum      : Nov '96 - Mai '00                                *
*****************************************************************/

class Matrix;
class Vektor;

extern const int AnzahlBeispiele;

void Start ( int Bsp, Matrix &A, Vektor &x0, double &eps );

void Ergebnis ( const Vektor &EigVek, double EigWert, long int Iterationen );
