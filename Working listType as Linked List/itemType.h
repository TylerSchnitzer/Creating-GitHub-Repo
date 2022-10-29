// itemType.h
#ifndef ITEMTYPE_FLAG
#define ITEMTYPE_FLAG

#include <string>
using namespace std;

struct itemType
{
	// Notice that I changed the name from "payLoad".  An itemType may have any
	// number of fields.
	string identifier;

	// itemType needs a constructor and a copy constructor
	itemType(); // constructor
	itemType(const itemType &); // copy constructor

	// itemType must implement the six relational operators
	bool operator ==	(itemType);
	bool operator >	(itemType );
	bool operator <	(itemType );
	bool operator !=	(itemType );
	bool operator <=	(itemType );
	bool operator >=	(itemType );

	// assignment of itemType=itemType must be defined
	itemType operator = (const itemType);
	// itemType=string is optional
	itemType operator = (const string);

	// insertion is used to print the list
	friend ostream &operator << (ostream &, const itemType);
};
#endif

