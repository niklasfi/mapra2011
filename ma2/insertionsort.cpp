#include "bubblesort.h"

typedef unsigned int uint;

void insertionsort(uint length, uint *f){
	for (uint i = 1; i < length; i++){
		uint tmp = f[i];
		uint j = i;
		while (j > 0 && f[j-1] > tmp){
			f[j] = f[j-1];
			--j;
		}
		f[j] = tmp;
	}
}
