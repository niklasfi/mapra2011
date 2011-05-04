#pragma once

#include "unit3.h"
#include "main.h"

#include <cmath>

class Rom{
	int index;
	bool minus;
	double a, h0, eps;
	Vektor extrapol;
	Funktion f;
	double all;

	int numparts(int i);
	
	double stepOnce();
	double stepInit();
	
	double extrapolate();

	void print();
	
	double integrate_wisely(double a, double b, double eps);
	double integrate_dumb(double a, double b, double eps);
public:

	static bool grafik;
	static bool ausgabe;
	Rom(Funktion f);	
	double integrate(double a, double b, double eps, bool extrapolate = true);
};
