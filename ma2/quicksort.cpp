#include "quicksort.h"

typedef unsigned int uint;

void quicksort(int lbound, int rbound, uint* f){
	if(lbound>=rbound) return;

	int l = lbound; int r = rbound -1;

	uint pivot = f[rbound];

	do{
		while(f[l]<=pivot && l<rbound) l++;
		while(f[r]>=pivot && r>lbound) r--;
		if(l<r)	tausche(f,l,r);
	}while(l<r);

	if(f[l]>pivot) tausche(f,l,rbound);

	quicksort(lbound,l-1,f);
	quicksort(l+1,rbound,f);
}

void quicksort(uint length, uint *feld){
	quicksort(0,length-1,feld);
}
