#include "bubblesort.h"
typedef unsigned int uint;

void bubblesort(uint num, uint* f){
	for (uint i=0; i<num; i++)
		for (uint j=num-1; j>i; j--)
			if (f[j]<f[j-1]) tausche(f, j, j-1);
}
