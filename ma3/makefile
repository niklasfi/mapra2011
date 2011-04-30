CC    = g++
FLAGS = -g -Wall

ifeq ($(shell uname -p | grep -o "64"),64)
	ARCH=64
else
	ARCH=32
endif

LIBS  = -L/usr/lib{ARCH} -L. -lIGL -lX11 -lXi -lXmu -lGL -lGLU -lglut -lpthread 

all: meina3

meina3: meina3.o unit3.o
	$(CC) $(FLAGS) -o meina3 meina3.o unit3.o $(LIBS)

meina3.o: meina3.cpp meina3.h unit3.h
	$(CC) $(FLAGS) -c meina3.cpp

.PHONY : clean
clean : 
	rm -f meina3 meina3.o
