#include "ui2.h"

bool foo(void) {std::cout<<"func \n";return true;}

template <class T> std::function<bool(const T&)> ui2::check_true(){
	return [](const T& m) { return true; };
}
template <class T> std::function<bool(const T&)> ui2::check_range(const T& l, const T& u){
	return [&](const T& m){return l <=m && m <= u;};
}
template <class T> std::function<bool(const T&)> ui2::check_larger(const T& lbound){
	return [&](const T& m){return lbound <= m;};
}
template <class T> std::function<bool(const T&)> ui2::check_smaller(const T& ubound){
	return [&](const T& m){return m <= ubound;};
}
template <class T> T ui2::readarg(std::string arg, std::string failmsg, std::function<bool(const T&)> chkfnc){
	std::stringstream ss(arg);
	T eval;
	ss >> eval;
	if(ss.eof() && !ss.bad() && !ss.fail()) return eval;
	else{
		std::cout << "Fehler bei der Eingabe!\n"
			<< failmsg << "\n";
		exit(1);
	}
}
int main(int argc, char *argv[]){
	ui2::readarg<int>("hallo","x konnte nicht geparsed werden");
}

