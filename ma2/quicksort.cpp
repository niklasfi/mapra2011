#include "quicksort.h"

typedef unsigned int uint;

void quicksort(int lbound, int rbound, uint* f, bool median){
	if(lbound>=rbound) return;

	if( median && lbound < rbound){
		int center = (rbound-lbound)/2;
		int &a = lbound;
		int &b = center;
		int &c = rbound;
		if(a>b)
			if(b>c)
				tausche(f,b,rbound);
			else
				if(a>c)
					tausche(f,c,rbound);
				else
					tausche(f,a,rbound);
		else
			if(b>c)
				if(a>c)
					tausche(f,a,rbound);
				else
					tausche(f,c,rbound);
			else
				tausche(f,b,rbound);
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
