/********************************************************************
*  Name       : unit2.h                                             *
*  Verwendung : Umgebung zu Praktikumsaufgabe (MAPRA),              *
*               Sortieralgorithmen                                  *
*  Autor      : K. Brix, IGPM RWTH Aachen                           *
*  Datum      : Mar '08                                             *
*  Sprache    : C++                                                 *
********************************************************************/

#pragma once

typedef unsigned int uint;

#include <iostream>
#include <iomanip> //for setw

#include "quicksort.h"
#include "bubblesort.h"
#include "insertionsort.h"
#include "selectionsort.h"
#include "heapsort.h"

// Konstanten

extern const int AnzahlBeispiele;

// Funktionen

void start(const unsigned int beispiel, unsigned int &laenge, unsigned int *&feld);
bool ergebnis(unsigned int *feld);
void tausche(unsigned int *feld, const long int i, const long int j);

void print(const uint &l, uint *&feld, uint *markers = 0);
