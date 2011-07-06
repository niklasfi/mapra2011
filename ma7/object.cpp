#include "container.h"
#include "object.h"
#include "limits.h"

Object::Object(unsigned int value, unsigned int weight):
	initcycle(INT_MIN), value(value), weight(weight){};

Object& Object::operator=(const Object& o){
	initcycle = o.initcycle;
	value = o.value;
	weight = o.weight;
	return *this;
}

bool operator<(const Object& o1, const Object& o2){
	if(o1.value != o2.value) return o1.value  < o2.value;
	                         return o1.weight > o2.weight;
}
bool operator>(const Object& o1, const Object& o2){
	return o2 < o1;
}

std::ostream& operator<<(std::ostream& o, const Object& obj){
	o << "\t {"
		<< "\t\"value\": "  << obj.value << ","
		<< "\t\"weight\": " << obj.weight << ","
		<< "\t\"cycle\": " << obj.initcycle
		<< "\t}";
	return o;
}
