#pragma once

#include "unit3.h"
#include "bulirsch.h"
#include "romberg.h"
#include <iostream>

typedef unsigned int uint;
typedef double Vektor[MaxTiefe+1];
typedef double (*Funktion) (double x);

int main(int argc, char* argv[]);
