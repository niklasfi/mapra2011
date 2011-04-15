#include "mergesort.h"

typedef unsigned int uint;

void mergesort(int length,uint* liste){

	if(length > 1){

		uint* h1 = new uint[length/2];
		uint* h2 = new uint[(length + 1)/2];
		int i;
		for(i = 0; i < length/2; ++i)
			h1[i] = liste[i];
		for(i = length/2; i < length; ++i)
			h2[i - length/2] = liste[i];

		mergesort(length/2,h1);
		mergesort((length + 1)/2,h2);

		uint *p1 = &h1[0];
		uint *p2 = &h2[0];
		bool fertig1 = false;
		bool fertig2 = false;
		for(i = 0; i < length; ++i){
			if(*p1 <= *p2 && !fertig1){
				liste[i] = *p1;
				if(p1 == &h1[length/2 - 1]){
					fertig1 = true;
				}
				else{
					++p1;
				}
			}
			else if (!fertig2){
				liste[i] = *p2;
				if(p2 == &h2[(length + 1)/2 - 1]){
					fertig2 = true;
				}
				else{
					++p2;
				}
			}
		}
	}
}


