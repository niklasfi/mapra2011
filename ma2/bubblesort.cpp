#include "bubblesort.h"

typedef unsigned int uint;

void bubblesort(uint length, uint *f){
	bool swapped;
	do{
		swapped = false;
		for( uint i = 1; i <= length -1; i++)
			if( f[i-1] > f[i]){
				tausche(f,i-1,i);
				swapped = true;
			}
		
	}while(swapped);
}
