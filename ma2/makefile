gpp=g++ -Wall
objects = quicksort.o bubblesort.o insertionsort.o selectionsort.o heapsort.o mergesort.o
dbg= -g

ifeq ($(shell uname -p | grep -o "64"),64)
	ARCH=64
else
	ARCH=32
endif

run.exe: unit2.cpp $(objects)
	$(gpp) $(dbg) -o run.exe unit2.cpp $(objects) gcc-${ARCH}bit/unit2.o
	
%.o: %.cpp
	$(gpp) $(dbg) -c $<

clean: 
	rm run.exe $(objects)
