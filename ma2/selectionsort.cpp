#include "selectionsort.h"

typedef unsigned int uint;

void selectionsort(uint length, uint *f){
	for (uint i = 0; i < length; i++){
		uint minind = i;
		
		for(uint j = i+1; j < length; j++)
			if(f[j] < f[minind]) minind = j;
			
		if(i!=minind) tausche(f,minind,i);
	}
}
