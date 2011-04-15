#include "quicksort.h"

typedef unsigned int uint;

void quicksort(int lbound, int rbound, uint* f, bool median){
	if(lbound>=rbound) return;

	if( median && lbound < lbound){
		int center = (rbound-lbound)/2;

		uint markers[]={lbound,center,rbound,333};
		print(14,f,markers);

		if(f[lbound] > f[rbound]) tausche(f,lbound,rbound);		
		if(f[center] < f[lbound]) tausche(f,center,lbound); // jetzt sind die ersten beiden Werte sortiert
		if(f[center] < f[rbound]) tausche(f,center,rbound); // falls f[center] wirklich mittlerer wert, ans ende tauschen
		print(14,f);
	}

	int l = lbound; int r = rbound -1;
	
	uint pivot = f[rbound];

	do{
		while(f[l]<=pivot && l<rbound) l++;
		while(f[r]>=pivot && r>lbound) r--;
		if(l<r)	tausche(f,l,r);
	}while(l<r);

	if(f[l]>pivot) tausche(f,l,rbound);

	quicksort(lbound,l-1,f,median);
	quicksort(l+1,rbound,f,median);
}

void quicksort(uint length, uint *feld,bool median){
	quicksort(0,length-1,feld,median);
}
