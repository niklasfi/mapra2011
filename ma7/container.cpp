#include "object.h"
#include "container.h"

typedef std::vector<Object>::iterator vit;

Container::Container(unsigned int room_avail, unsigned int cycles_max, unsigned int cycles_freeze, unsigned int output_interval, const std::vector<Object>& objects):
	room_avail(room_avail),
	room_used(0),
	cash_inside(0),
	cycles_max(cycles_max),
	cycles_cur(1),
	cycles_freeze(cycles_freeze), 
	output_interval(output_interval),
	objects_available(objects),
	inside(objects_available.begin()),
	outside(objects_available.begin()),
	best_sln(),
	best_sln_cash(0){}

unsigned int Container::room_remaining() const{
	return (unsigned int)(room_avail - room_used);
}

bool Container::frozen(const Object& o) const{
	return o.initcycle > 0 && cycles_cur - o.initcycle <= cycles_freeze;
}

bool Container::fits(const Object& o) const{
	
	return room_avail - room_used >= o.weight;
}

Object& Container::pick_outside_best(){
	if(outside == objects_available.end())
		throw alreadyPickedEverythingException();

	bool allFrozen = true;
	Object* best = 0;
	
	for(vit it = outside; it < objects_available.end(); it++){
		Object& obj = *it;
		if(frozen(obj)) continue;
		
		allFrozen = false;
		if(fits(obj) && (!best || obj > *best))
			best = &obj;
	}
	
	if(allFrozen)
		throw allFrozenException();
	if(!best)
		throw nothingFitsException();
	
	return *best;
}

Object& Container::pick_inside_worst(){
	if(outside == objects_available.begin())
		throw alreadyEmptyException();

	Object* worst = 0;
	
	for(vit it = inside; it < outside; it++){
		Object& obj = *it;
		if(frozen(obj)) continue;
		
		if(!worst || obj < *worst)
			worst = &obj;
	}

	if(!worst)
		throw allFrozenException();
	
	return *worst;
}

bool Container::drop(){
	Object* worst_inside;
	try{
		worst_inside = &pick_inside_worst();
	}
	catch(allFrozenException e){
		return false;
	}
	
	room_used -= worst_inside->weight;
	cash_inside -= worst_inside->value;

	worst_inside->initcycle = cycles_cur;
	
	Object& last = *(--outside);
	Object tmp = last;
	       last = *worst_inside;
	       *worst_inside = tmp;
	
	return true;
}

bool Container::add(bool initial){
	Object* best_outside;
	try{
		best_outside = &pick_outside_best();
	}
	catch(allFrozenException e){
		return false;
	}
	catch(nothingFitsException){
		return false;	
	}
	
	room_used += best_outside->weight;
	cash_inside += best_outside->value;

	if(!initial) best_outside->initcycle = cycles_cur;       
	
	Object& first = *(outside++);
	Object tmp = first;
	       first = *best_outside;
	       *best_outside = tmp;
	       
	return true;
}

unsigned int Container::incount(){
	return outside - inside;
}

Container& Container::iterate(std::ostream& o){
	while(add(true));

	save_result();
	o << "[\n";
	o << *this << ",\n"	;

	while(cycles_cur < cycles_max){
		if(!add()) drop();
		else if (best_sln_cash < cash_inside){
			save_result();
		}
		cycles_cur++;
		if(cycles_cur % output_interval == 0)
			 o << *this << ",\n";
	}
	if(cycles_cur % output_interval != 0) o << *this << ",\n";
	else o << "[]\n";
	
	o << "]";	
	
	return *this;
}

Container& Container::save_result(){
	best_sln_cash = cash_inside;
	best_sln = std::vector<Object>(inside,outside);
	return *this;
}

std::ostream& operator<<(std::ostream& o, const Container& c){
	o << "{\"cycle\": " << c.cycles_cur << ",\n";
	o << "\t\"used\":\t\"" << c.room_used << "/" << c.room_avail <<"\",\n";
	o << "\t\"c$\":\t" << c.cash_inside << ",\n";
	o << "\t\"inside\": [\n";
	for(vit it = c.inside; it < c.outside;){
		o << "\t";
		o << *it;
		o << ((++it == c.outside)?"\n":",\n");
	}
	o << "\t],\n";
	
	o << "\t\"outside\": [\n";
	for(vit it = c.outside ; it < c.objects_available.end();){
		o << "\t";
		o << *it;
		o << ((++it == c.objects_available.end())?"\n":",\n");
	}
	o << "\t],\n";
	o << "\t\"b$\":\t" << c.best_sln_cash << ",\n";
	o << "\t\"best\": [\n";
	for(unsigned int i = 0; i < c.best_sln.size(); i++)
		o << "\t" << c.best_sln[i] << ((i+1 == c.best_sln.size())?"\n":",\n");
	o << "\t]\n";
	
	o << "}\n";
	return o;
}
