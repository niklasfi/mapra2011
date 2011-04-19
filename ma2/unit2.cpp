#include "unit2.h"


typedef unsigned int uint;

int main(){
		uint* feld;
		for(uint i = 1; i <6;  i++){
			uint len = 1000;
			start( i, len, feld);
			selectionsort(len,feld);
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
