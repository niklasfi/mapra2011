#include "quicksort.h"

typedef unsigned int uint;

void quicksort(int lbound, int rbound, uint* f, bool median){
	if(lbound>=rbound) return; //trivialer Fall

	if( median && lbound < rbound){ //berechne den median
		int center = (rbound-lbound)/2;
		int &a = lbound; //benutze referenzen um weniger zu denken
		int &b = center;
		int &c = rbound;
		if(a>b) //siehe median tabelle
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
		while(f[l]<=pivot && l<rbound) l++; //bewege linken zeiger
		while(f[r]>=pivot && r>lbound) r--; //bewege rechten zeiger
		if(l<r)	tausche(f,l,r); //tausche
	}while(l<r);

	if(f[l]>pivot) tausche(f,l,rbound); //tausche pivot element an die richtige stelle

	quicksort(lbound,l-1,f,median); //recurse!
	quicksort(l+1,rbound,f,median);
}

void quicksort(uint length, uint *feld,bool median){
	quicksort(0,length-1,feld,median);
}
