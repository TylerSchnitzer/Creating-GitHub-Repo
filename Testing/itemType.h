
// itemType.h
#ifndef ITEMTYPE_FLAG
#define ITEMTYPE_FLAG

#include <string>
#include "md5.h"
#include <iostream>
using namespace std;

struct itemType
{
	string identifier;
	// Notice that I changed the name from "payLoad".  An itemType may have any
	// number of fields.

	itemType(); // constructor
	itemType(const itemType &); // copy constructor

	void operator =(itemType &);

	bool operator ==(itemType &);
	bool operator >(itemType &);
	bool operator <(itemType &);
	bool operator !=(itemType &);
	bool operator <=(itemType &);
	bool operator >=(itemType &);

	void operator =(string);
	friend ostream &operator << (ostream &, const itemType &);
	unsigned long getHash();
};
#endif
