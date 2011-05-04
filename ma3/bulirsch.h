#pragma once

#include "unit3.h"
#include "main.h"

#include <cmath>

class Bul{
	int index;
	bool minus;
	double a, h0, eps;
	Vektor extrapol;
	Funktion f;
	double odd,even, all;

	int numparts(int i);
	
	double stepOnce();
	double stepInit();
	double stepOdd();
	double stepEven();
	
	double extrapolate();

	void print();
public:

	static bool grafik;
	static bool ausgabe;
	Bul(Funktion f);	
	double integrate(double a, double b, double eps);
};
