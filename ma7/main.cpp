#include <iostream>
#include <fstream>
#include <sstream>

#include "container.h"
#include "object.h"

int main(int argc, const char* argv[]){
	if(argc != 5){
		std::cout << "usage: <testdatei> <tabudauer> <lauflänge> <Ausgabeinterval>\n";
		std::exit(1);
	}
	
	std::fstream ifile(argv[1],std::ifstream::in);
	unsigned int obj_count, room_avail, cycles_freeze, cycles_max, output_interval;
	ifile >> obj_count;
	ifile >> room_avail;
	
	/* cycles_freeze einlesen */
	{
		std::stringstream ss(argv[2]);
		ss >> cycles_freeze;
	}
	
	/* cycles_max einlesen */
	{
		std::stringstream ss(argv[3]);
		ss >> cycles_max;
	}
	
	/* output_interval einlesen */
	{
		std::stringstream ss(argv[4]);
		ss >> output_interval;
	}
	
	/* objekte einlesen */
	std::vector<Object> objects;
	{
		std::string line;
		getline(ifile,line); //bis zum Zeilenende lesen
		while(getline(ifile,line)){
			std::stringstream ss(line);
			unsigned int gewinn, masse;
			ss >> gewinn >> masse;
			objects.push_back(Object(gewinn,masse));
		}

		ifile.close();
	}
	
	Container c(room_avail, cycles_max, cycles_freeze, output_interval, objects);

	//std::cout << c;

	c.iterate(std::cout);
}
