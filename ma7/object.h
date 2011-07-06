#pragma once

#include <iostream>

struct Container;

struct Object{
public:
	int initcycle;
	unsigned int value;
	unsigned int weight;

	Object(unsigned int value, unsigned int weight);

	bool available() const;
	bool fits() const;
	
	Object& operator=(const Object& o);
};

bool operator<(const Object& o1, const Object& o2);
bool operator>(const Object& o1, const Object& o2);

std::ostream& operator<<(std::ostream& o, const Object& obj);
