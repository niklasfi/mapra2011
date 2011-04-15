#include "unit2.h"


typedef unsigned int uint;

int main(){

	bool* results = new bool[5*5];

	uint slowlen;
	std::cout << "länge für langsme algorithmen\n";
	std::cin >> slowlen;
	
	uint fastlen;
	std::cout << "länge für schnelle algorithmen\n";
	std::cin >> fastlen
	
	for(uint bsp = 1; bsp < 6; bsp++){
		uint *feld;
		start( bsp, slowlen, feld); selectionsort(l,feld); results[bsp*5] = ergebnis(feld);
		
		
		insertionsort(l,feld); results[bsp*5 + 1] = ergebnis(feld);
		
		//heapsort(l,feld);
		//print(l,feld);
		
		quicksort(l,feld,true);
		ergebnis(feld);
	}
}

void print(const uint &l, uint *&feld, uint *markers){
	if (l == 0){
		std::cout << "[]\n";
		return;
	}

	std::cout << "[ ";
	for(uint i = 0; i < l-1; i++)
		std::cout << std::setw(3) << feld[i] << ", ";
	std::cout << feld[l-1] << "]\n";
	
	if(markers)
	{
		std::cout << " ";
		uint col=0;
		uint i = 0;
		while(i <= l && markers[i] != 333 ){
			if(markers[i]>=col){
				for(uint j = 0; j<markers[i]-col; j++)
					std::cout << "     ";
				std::cout << " ^^^ ";
				col = markers[i]+1;
			}
			i++;
		}
		std::cout << "\n";
	}
	
	return;
}
