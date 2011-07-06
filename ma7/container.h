#pragma once
#include <queue>
#include <vector>
#include <exception>
#include <iostream>

struct Object;

struct Container{
	unsigned int room_avail;
	unsigned int room_used;
	unsigned int cash_inside;
	int cycles_max;
	int cycles_cur;
	int cycles_freeze;
	unsigned int output_interval;

	std::vector<Object> objects_available;
	//die ersten incount() Objekte in objects_available sind im Rucksack
	std::vector<Object>::iterator inside;
	std::vector<Object>::iterator outside;
	
	std::vector<Object> best_sln;
	unsigned int best_sln_cash;

	Container(unsigned int room_avail, unsigned int cycles_max, unsigned int cycles_freeze,
		unsigned int output_interval, const std::vector<Object>& objects);
	//pair<gewinn,masse>
		
	unsigned int room_remaining() const;
		
	bool frozen(const Object&) const;
	bool fits(const Object&) const;
	
	Object& pick_outside_best();
	Object& pick_inside_worst();
	
	bool drop();
	bool add(bool initial = false);

	unsigned int incount();
	
	Container& iterate();
	Container& iterate(std::ostream& o);
	Container& save_result();

	class allFrozenException: public std::exception{
		virtual const char* what() const throw(){
			return "All objects were frozen";
		}
	};
	
	class nothingFitsException: public std::exception{
		virtual const char* what() const throw(){
			return "none of the given Objects fitted the Container";
		}
	};
	
	class alreadyEmptyException: public std::exception{
		virtual const char* what() const throw(){
			return "you called drop, but the Container was already empty!";
		}
	};
	
	class alreadyPickedEverythingException: public std::exception{
		virtual const char* what() const throw(){
			return "you called add, but all available elements were in the Container already";
		}
	};
};

std::ostream& operator<<(std::ostream& o, const Container&);
