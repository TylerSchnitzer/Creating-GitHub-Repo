#include "itemType.h"
#include <iostream>
#include <string>

using namespace std;

itemType::itemType()
{
	queue_Name="none";
	queue_Weight=0;	
}

itemType::itemType(const itemType &p)
{
	queue_Name=p.queue_Name;
	queue_Weight=p.queue_Weight;
}

void itemType::operator =(itemType &i)
{
	if(queue_Name==i.queue_Name)
	{
		queue_Weight++;
	}
	else
	{
		queue_Name=i.queue_Name;
		queue_Weight=i.queue_Weight;
	}
}

bool itemType::operator ==(itemType &i)//this is the search button
{
	return queue_Name==i.queue_Name;
}


bool itemType::operator >(itemType &i)
{
	if(queue_Weight==i.queue_Weight)
		return queue_Name>i.queue_Name;
	else
		return queue_Weight>i.queue_Weight;
}

bool itemType::operator <(itemType &i)
{
	if(queue_Weight==i.queue_Weight)
		return queue_Name<i.queue_Name;
	else
		return queue_Weight<i.queue_Weight;
}

bool itemType::operator !=(itemType &i)
{
	return queue_Name!=i.queue_Name;
}

bool itemType::operator >=(itemType &i)
{
	return queue_Name>=i.queue_Name;
}

bool itemType::operator <=(itemType &i)
{
	return queue_Name<=i.queue_Name;
}

void itemType::operator =(string s)
{
	queue_Name=s;
}

ostream &operator <<(ostream &out, const itemType &c)
{
	out<<c.queue_Name<<"\t"<<c.queue_Weight;
	return out;
}

