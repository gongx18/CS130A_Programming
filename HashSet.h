#ifndef HASHSET_H
#define HASHSET_H

#include "IntegerHashes.h"
#include "StringHashes.h"
#include <string>

class HashSet{
	int nitems;
	int nslots;
	IntegerHash* intfn;
	StringHash* strfn;
	StringHash* strfn2;
	std::string** slots; 
	
	void rehash();

public:
	HashSet();
	~HashSet(); 

	void insert(const std::string& value); 
	bool lookup(const std::string& value) const; 
};

#endif
