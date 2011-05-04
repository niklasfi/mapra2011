#include "bulirsch.h"

bool Bul::grafik, Bul::ausgabe;

Bul::Bul(Funktion f):f(f){}

double Bul::integrate(double a, double b, double eps){
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
	
	extrapol[0]=stepInit();
	
	print();
	
	while(extrapolate() > eps);
	
	double res = (minus?-1:1)*extrapol[index];
	
	Schluss (res,eps,extrapol,index);
	
	return res;
}

int Bul::numparts(int i){ //spart speicher :)
	if(i==0) return 1;
	if(i%2) return 1<<((i+1)/2); //odd
	else return 3*(1<<(i/2-1)); //even
}

double Bul::stepOnce(){
	if(index==0)
		return stepInit();
	if(index % 2)
		return stepOdd();
	else
		return stepEven();
}

double Bul::stepInit(){
	double l = f(a);
	double r = f(a+h0);
	all = (l+r)/2;
	even=0;
	return all*h0;
}

double Bul::stepEven(){ //wird ausgeführt, wenn index % 2 == 0
	int till = numparts(index);
	double h = h0/till;

	for(int j = 1; j < till; j+=(index>2?2:1)){
		if( j % 3 == 0) continue;
		double fx = f(a+h*j);
		even+= fx;
	}
	
	double sigma = even + all;
	all += odd;
	return h * sigma;
}

double Bul::stepOdd(){ //wird ausgeführt, wenn index % 2 == 1
	int till = numparts(index);
	double h = h0/till;
	
	odd = 0;
	
	for(int j = 1; j < till; j+= 2){
		double fx = f(a+h*j);
		odd += fx;
	}
	
	return h*(odd + all);
}

double Bul::extrapolate(){
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

void Bul::print(){
	if (ausgabe){
		Ausgabe(index,extrapol);
	}
}
