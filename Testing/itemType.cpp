#ifndef ITEM_TYPE_FLAG
#define ITEM_TYPE_FLAG

#include "itemType.h"
#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
using namespace std;

	itemType::itemType()
	{
		identifier="~~~";
	} // stubbed constructor

	itemType::itemType(const itemType &p)
	{
		identifier = p.identifier;
	} // copy constructor

	void itemType::operator =(itemType &i)
	{
		identifier=i.identifier;
	}

	bool itemType::operator ==(itemType &i)
	{
		return identifier==i.identifier;
	}

	bool itemType::operator >(itemType &i)
	{
		return identifier>i.identifier;
	}

	bool itemType::operator <(itemType &i)
	{
		return identifier<i.identifier;
	}

	bool itemType::operator !=(itemType &i)
	{
		return identifier!=i.identifier;
	}

	bool itemType::operator >=(itemType &i)
	{
		return identifier>=i.identifier;
	}

	bool itemType::operator <=(itemType &i)
	{
		return identifier<=i.identifier;
	}

	void itemType::operator =(string s) // included only for the programmer's convieniance
	{
		identifier=s;
	}

	ostream &operator << (ostream &out, const itemType &c) // needed to print the list
	{
    	out << c.identifier;
    	return out;
	}

	unsigned long itemType::getHash()
	{
    	stringstream ss;
		unsigned int n;

	// delete this part
	cout<<"The identifier is: "<<identifier
		<<"\nand the MD5 string is:  "<<md5(identifier)<<'\n';
	// end delete.

		string s= md5(identifier).substr(0,8);

    	ss << hex << s;
    	ss >> n;
    	bitset<32> b(n);

		//???
    	return b.to_ulong();
	}
#endif
