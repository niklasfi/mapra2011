#include "mergesort.h"

typedef unsigned int uint;

void mergesort(uint length,uint* liste){

	if(length <= 1)
		return;
	
	uint llen = length / 2;
	uint rlen = length - llen;
	
	mergesort(llen,liste);
	mergesort(rlen,liste+llen);
	
	uint* llist = new uint[llen];
	for(uint i = 0; i<llen; i++)
		llist[i] = liste[i];
		
	uint* rlist = new uint[rlen];
	for(uint i = 0; i<rlen; i++)
		rlist[i] = liste[i+llen];

	uint l = 0; uint r = 0;
	for(uint i = 0; i < length; i++)
		if((l<llen && llist[l]<rlist[r]) || r>=rlen)
			liste[i]=llist[l++];
		else
			liste[i]=rlist[r++];
			
}


