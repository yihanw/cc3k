#include <string>
#ifndef _NAME_
#define _NAME_

//Display Name and symbol
struct Name {
	std::string name;
	char symbol;


	Name() : name{ "" }, symbol{ '~' } {}
	Name(std::string myname, char sym) : name{myname }, symbol{ sym } {}
};


#endif
