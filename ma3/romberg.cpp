#include "romberg.h"

bool Rom::grafik;
bool Rom::ausgabe;

Rom::Rom(Funktion f):f(f){}

int Rom::numparts(int i){ //spart speicher :)
	return 1<<i;
}
	
double Rom::stepOnce(){
	int till = numparts(index);
	double h = h0/numparts(index);
	
	for(int j = 1; j < till; j+= 2)
		all+=f(a+j*h);
		
	return all*h;
}

double Rom::stepInit(){
	all = (f(a)+f(a+h0))/2;
	return all*h0;
}
	
double Rom::extrapolate(){
	index ++;

	double tdiag[2];
	
	tdiag[0] = extrapol[0];
	extrapol[0] = stepOnce();
	
	for(int j = 1; j<=index; j++){
		tdiag[j % 2] = extrapol[j];
		double hpart = double(numparts(index))/numparts(index-j);
		
		extrapol[j] = extrapol[j-1] + (extrapol[j-1]-tdiag[(j-1)%2])/(hpart*hpart -1);
	}
	
	print();
	
	return fabs(extrapol[index]-extrapol[index-1]);
}

void Rom::print(){
	if (ausgabe){
		Ausgabe(index,extrapol);
	}
}

double Rom::integrate(double a, double b, double eps, bool extrapolate){
	if(b==a) return 0;
	
	index = 0;
	
	this->eps = eps;
	this->minus = b < a;
	
	if(minus){
		this->a = b;
		this->h0 = a-b;
	}
	else{
		this->a = a;
		this->h0 = b-a;
	}
	
	double res;
	if(extrapolate) res= integrate_wisely(a,b,eps);
	else res = integrate_dumb(a,b,eps);
	
	if(minus) res *= -1;
	
	Schluss (res,eps,extrapol,index);
	
	return res;	
}

double Rom::integrate_wisely(double a, double b, double eps){
	extrapol[0]=stepInit();
	
	print();
	
	while(extrapolate() > eps);
	
	return extrapol[index];
}
double Rom::integrate_dumb(double a, double b, double eps){
	
	extrapol[0] = stepInit();
	extrapol[1] = 1.0/0.0;
	
	print();
	
	while( fabs(extrapol[0] - extrapol[1]) > 3 * eps ){
		index ++;
		extrapol[1] = extrapol[0];
		extrapol[0] = stepOnce();
		print();
	}
	
	return extrapol[0];
}
