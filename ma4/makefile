CC    = g++
CPPFLAGS = -g -Wall -std=c++0x

OBJECTS = vektor.o matrix.o

ifeq ($(shell uname -p | grep -o "64"),64)
	ARCH=64
else
	ARCH=32
endif

.PHONY : all
all: ui2.exe test4.exe

%.exe: %.o ${OBJECTS}
	${CXX} ${LDFLAGS} -o $@ $< ${OBJECTS}

%.o: %.cpp %.h
	${CXX} ${CPPFLAGS} -c $<

.PHONY : clean
clean : 
	rm -f *.exe ${OBJECTS}
