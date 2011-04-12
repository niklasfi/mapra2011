objects = quicksort.o

run.exe: unit2.cpp $(objects)
	g++ -o run.exe unit2.cpp $(objects) gcc-32bit/unit2.o
	
quicksort.o: quicksort.cpp quicksort.h
	g++ -c quicksort.cpp
	
clean: 
	rm run.exe $(objects)
