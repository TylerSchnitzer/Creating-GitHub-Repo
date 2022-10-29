#include <iostream>
#include "listType.cpp"
#include "itemType.h"
using namespace std;

int main()
{
	cout<<"Begin\n";

	itemType myItem;
	listType<itemType> myList;

	string s;


	while(true)
	{
		cout<<"Enter a name: ";
		getline(cin, s);
		if(s=="")
			break;
		myItem = s;
	    myList.isThere( myItem );
	}

	cout<<"Process Complete\n";
	return 0;
}
