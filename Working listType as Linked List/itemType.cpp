/*
	I have placed this code on a rigorous footing.  One might get away with:

		void itemType::operator =(const itemType i)
		{
			identifier=i.identifier;
		}

	but that's sloppy coding and won't work in some settings where you're
	returning an itemType from a function.  The code:

		itemType itemType::operator =(const itemType i)
		{
			this->identifier=i.identifier;
			return *this;
		}

	is a much stronger programming paradigm.   "this->identifier" explicitly refers to the
	hand side.  Returning the target of the "this" pointer is the correct way to write it.
*/

#include "itemType.h"
#include <iostream>
using namespace std;

itemType::itemType()
{
	identifier="~~~"; // I like to give a printable value.
} // stubbed constructor

itemType::itemType(const itemType &p)
{
	this->identifier = p.identifier;
} // copy constructor
//***************************************************
bool itemType::operator ==(itemType i)
{
	return this->identifier==i.identifier;
}

bool itemType::operator >(itemType i)
{
	return this->identifier>i.identifier;

}

bool itemType::operator <(itemType i)
{
	return this->identifier<i.identifier;
}

bool itemType::operator !=(itemType i)
{
	return this->identifier!=i.identifier;
}

bool itemType::operator >=(itemType i)
{
	return this->identifier>=i.identifier;
}

bool itemType::operator <=(itemType i)
{
	return this->identifier<=i.identifier;
}
//***********************************************************
itemType itemType::operator =(const itemType i)
{
	this->identifier=i.identifier;
	return *this;
}

itemType itemType::operator =(const string s) // included only for the programmer's convieniance
{
	this->identifier=s;
	return *this;
}

ostream &operator << (ostream &out, const itemType i) // needed to print the list
{
    out << i.identifier;
    return out;
}

/*
	// The item for the priority queue will look a lot like this.
	//
	//	= (assignment) will be:
	//
	//		itemType itemType::operator =(const itemType i)
	//		{
	//			this->payLoad_name = i.payLoad_name;
	//			this->payLoad_weight = i.payLoad_weight;
	//			return *this;
	//		}						// it no longer increments weight; that was a bad idea.
	//
	//  == and != are the same in the priority queue as here.  They only depend on payLoad_name.
	//
	// > says:		if( this->payLoad_weight==i.payLoad_weight)
	//						return this->payLoad_name > i.payLoad_name;
	//					else
	//						return this->payLoad_weight > i.payLoad_weight;
	//
	//	<, <=, and >= will all work like that.
	//
	//  And, to this, we will add one more operator: prefix increment.
	//	It looks like this:
	//
	//	itemType itemType::operator++()  // prefix ++ added
	//	{
	//		++(this->payLoad_weight);
	//		return *this;
	//	}
	//
	//		Thus, if:
	//						itemType i.payLoad_weight = 5;	// a perfectly  legal statement,
	//		then:
	//						++i;		// makes it be 6
*/
