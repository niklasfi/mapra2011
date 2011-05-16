#pragma once

/*****************************************************************
*  Name       : unit4.h                                          *
*  Verwendung : Schnittstelle zu Praktikumsumgebung (MAPRA),     *
*               Eigenwert/-vektorberechnung mit Potenzmethode    *
*  Autor      : V. Reichelt, IGPM RWTH Aachen                    *
*  Datum      : Nov '96 - Mai '00                                *
*****************************************************************/

#include "matrix.h"
#include "vektor.h"
#include "ui2.h"

extern const int AnzahlBeispiele;

void Start ( int Bsp, Matrix &A, Vektor &x0, double &eps );

void Ergebnis ( const Vektor &EigVek, double EigWert, long int Iterationen );
