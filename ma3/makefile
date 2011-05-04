CC    = g++
FLAGS = -g -Wall

OBJECTS = main.o unit3.o bulirsch.o romberg.cpp

ifeq ($(shell uname -p | grep -o "64"),64)
	ARCH=64
else
	ARCH=32
endif

LIBS  = -L/usr/lib{ARCH} -L. -lIGL -lX11 -lXi -lXmu -lGL -lGLU -lglut -lpthread 

all: run.exe

run.exe: $(OBJECTS)
	$(CC) $(FLAGS) -o run.exe $(OBJECTS) $(LIBS)

main.o: main.cpp main.h unit3.h bulirsch.h romberg.h
	$(CC) $(FLAGS) -c main.cpp

bulirsch.o: bulirsch.cpp bulirsch.h main.h unit3.h
	$(CC) $(FLAGS) -c bulirsch.cpp
	
romberg.o: romberg.cpp romberg.h main.h unit3.h
	$(CC) $(FLAGS) -c romberg.cpp
	
.PHONY : clean
clean : 
	rm -f run.exe main.o bulirsch.o romberg.o
