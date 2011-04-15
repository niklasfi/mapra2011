#include "heapsort.h"

typedef unsigned int uint;

void versickern(uint length, uint *f, uint root){ //wert von root 1-basiert!
	while(root*2 - 1 < length){
		uint child = root * 2 - 1;
	
		uint swap = root-1; //swap & child 0-basiert
		if( f[child] > f[swap])
			swap = child;
		if( child + 1 < length && f[child + 1] > f[swap])
			swap = child +1;
		
		if(root-1==swap) return;
		
		tausche(f,root-1,swap);
		root = swap+1;
	}
}

void heapify(uint length, uint *f){
	uint index = length / 2;
	
	while ( index > 0){
		versickern(length, f, index--);
	}
}

void heapsort(uint length, uint *f){
	heapify(length,f);
	
	std::cout << "\nheapify zu Ende\n";
	
	uint left = length;
	while (left > 0){
		--left;
		tausche(f,0, left);
		versickern(left,f,1);
	}
}
