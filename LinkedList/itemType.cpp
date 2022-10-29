
#include "itemType.h"
#include <iostream>
#include <cstring>
using namespace std;

itemType::itemType()        // Constructor
{
	payLoad_name="~~~";
	payLoad_weight=0;
} // constructor

itemType::itemType(const itemType &i)   // Copy Constructor
{
	this->payLoad_name = i.payLoad_name;
	this->payLoad_weight = i.payLoad_weight;
} // copy constructor

itemType itemType::operator =(const itemType i)  // assignment  ( ***** CHANGED ***** )
{
	this->payLoad_name=i.payLoad_name;		// copy all fields
	this->payLoad_weight=i.payLoad_weight;
	return *this;
}

bool itemType::operator ==(itemType i) // equality
{
	return this->payLoad_name==i.payLoad_name;	// they're equal if the names are equal
}

bool itemType::operator >(itemType i)  // greater than
{
	if(this->payLoad_weight==i.payLoad_weight)			// if the names are equal
		return this->payLoad_name>i.payLoad_name;	// 		then the inequality is a function of the name
	else
		return this->payLoad_weight>i.payLoad_weight;//		else it's a function of the weight
}

bool itemType::operator <(itemType i)  // Less Than
{
	if(this->payLoad_weight==i.payLoad_weight)			// if the names are equal
		return this->payLoad_name<i.payLoad_name;	// 		then the inequality is a function of the name
	else
		return this->payLoad_weight<i.payLoad_weight;//		else it's a function of the weight
}

bool itemType::operator !=(itemType i)
{
	return this->payLoad_name!=i.payLoad_name;		// they're not equal if the names are not equal
}

bool itemType::operator >=(itemType i)
{
	if(this->payLoad_weight==i.payLoad_weight)			// if the names are equal
		return this->payLoad_name>=i.payLoad_name;	// 		then the inequality is a function of the name
	else
		return this->payLoad_weight>=i.payLoad_weight;//		else it's a function of the weight
}

bool itemType::operator <=(itemType i)
{
	if(this->payLoad_weight==i.payLoad_weight)			// if the names are equal
		return this->payLoad_name<=i.payLoad_name;	// 		then the inequality is a function of the name
	else
		return this->payLoad_weight<=i.payLoad_weight;//		else it's a function of the weight
}

itemType itemType::operator++()  // prefix ++ added      ***** NEW *****
{
	++(this->payLoad_weight);
	return *this;
}

itemType itemType::operator =(const string s) // included only for the programmer's conveniance
{
	this->payLoad_name=s;
	this->payLoad_weight=0;
	return *this;
}

ostream &operator << (ostream &out, const itemType c) // needed to print the list; modify as needed
{
    out << c.payLoad_name<<'\t'<<c.payLoad_weight;
    return out;
}

//int main(){return 0;}
