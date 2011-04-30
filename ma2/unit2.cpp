#include "unit2.h"


typedef unsigned int uint;

int main(){
		uint* feld;
		
		uint l,algo;
		std::cout << "laenge?\n";
		std::cin >> l;
		std::cout << "algorithmus:\n"
			<< "\t 1: insertionsort\n"
			<< "\t 2: selectionsort\n"
			<< "\t 3: bubblesort\n"
			<< "\t 4: mergesort\n"
			<< "\t 5: quicksort\n"
			<< "\t 6: heapsort\n"
			<< "\t 7: quicksort median\n";
		
		std::cin >> algo;

		for(uint i = 1; i <6;  i++){
			uint len = l;
			start( i, len, feld);
			switch(algo){
				case 1:
					insertionsort(len,feld);
					break;
				case 2:
					selectionsort(len,feld);
					break;
				case 3:
					bubblesort(len,feld);
					break;
				case 4:
					mergesort(len,feld);
					break;
				case 5:
					quicksort(len,feld);
					break;
				case 6:
					heapsort(len,feld);
					break;
				case 7:
					quicksort(len,feld,true);
					break;
				default:
					std::cout << "fehlerhafte eingabe!\n";
					return 1;

			}
			bubblesort(len,feld);
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
