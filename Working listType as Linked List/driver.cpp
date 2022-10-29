#include <iostream>
#include "itemType.h"
/*	I would like to #include itemType.h only
	but that does not work for class templates.  */
#include "listType.cpp"   // for class templates, the source file (.cpp) is included
										// other methods exist; however, none are particularly graceful.
using namespace std;

/*
	The main point is to demonstrate abstraction.  The operations on an elementType
	are all properties of and defined by elementType.  The list template "knows"
	nothing of these, except that they must be defined.  In this example, a listType object
	is instantiated passing it type int:  listType<int> myList2;  It works fine because int
	has all of the required operators defined.  Type float, char, or string would also
	work.

	the job of "driver.cpp" [which contains main() ] is simply to test the listType.  The driver
	code has intimate knowledge of itemType... itemType might as well be defined within
	that file; it would work if it were so long as, whatever it is, has the six relational operators,
	assignment, and insertion defined upon it.

	This week, I will introduce the binary search.  We will change our isThere(elementType)
	method to use the binary search.  After I have developed that, we will consider the unstable
	sorting algorithms (e.g.: heapSort) that use a binary search.
*/

int main()
{
	// test code; modify as needed
    listType<itemType> myLinkedList;
	myLinkedList.create();

	itemType e;

	e="test value 2";
	myLinkedList.put(e);
	 myLinkedList.print();

	e="test value 3";
	myLinkedList.put(e);
	myLinkedList.print();

	e="test value 1";
	myLinkedList.put(e);
	myLinkedList.print();

	e="test value 6";
	myLinkedList.put(e);
	myLinkedList.print();

	e="test value 4";
	myLinkedList.put(e);
	myLinkedList.print();

	e="test value 5";
	myLinkedList.put(e);
	myLinkedList.print();

	cout<<"\n***** Removing ***\n";

	e="test value 1"; // delete at root
	myLinkedList.remove(e);
	myLinkedList.print();

	e="test value 4"; // delete mid-list
	myLinkedList.remove(e);
	myLinkedList.print();

	e="test value 6"; // delete at end
	myLinkedList.remove(e);
	myLinkedList.print();

// delete everything else

	e="test value 2"; // delete at root
	myLinkedList.remove(e);
	myLinkedList.print();

	e="test value 3"; // delete mid-list
	myLinkedList.remove(e);
	myLinkedList.print();

	e="test value 5"; // delete at end
	myLinkedList.remove(e);
	myLinkedList.print();


	cout<<"\n\t*** Run Complete ***\n\n";
    return 0;
}
