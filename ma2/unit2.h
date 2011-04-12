/********************************************************************
*  Name       : unit2.h                                             *
*  Verwendung : Umgebung zu Praktikumsaufgabe (MAPRA),              *
*               Sortieralgorithmen                                  *
*  Autor      : K. Brix, IGPM RWTH Aachen                           *
*  Datum      : Mar '08                                             *
*  Sprache    : C++                                                 *
********************************************************************/

#pragma once
#include <iostream>

// Konstanten

extern const int AnzahlBeispiele;

// Funktionen

void start(const unsigned int beispiel, unsigned int &laenge, unsigned int *&feld);
bool ergebnis(unsigned int *feld);
void tausche(unsigned int *feld, const long int i, const long int j);
