#include <iostream>
#include "itemType.h"
#include "listType.cpp"
using namespace std;

int main()
{

	cout<<"Test routine:\n";

	listType<itemType> myTree;
	itemType i;

	myTree.create();

	i="10";
	myTree.put(i);

	i="10";
	myTree.put(i);

	i="20";
	myTree.put(i);

	i="30";
	myTree.put(i);

	i="40";
	myTree.put(i);

	i="50";
	myTree.put(i);

	i="10";
	myTree.put(i);

	i="10";
	myTree.put(i);

	i="60";
	myTree.put(i);

	i="70";
	myTree.put(i);

	i="80";
	myTree.put(i);

	i="90";
	myTree.put(i);


	


	myTree.print();
	myTree.showTreeStats();
	
	myTree.balance();
	cout<<"After balance:\n";
	myTree.print();
	myTree.showTreeStats();

	cout<<"\n\t*** Run Complete ***\n\n";
    return 0;
}
/*
	Expected Output:


Test routine:


*********************
Level - 0       10
Level - 1       20
Level - 2       30
Level - 3       40
Level - 4       50
Level - 5       60
Level - 6       70
Level - 7       80


*********************


numNodes = 8    calcLvls = 4    cntLvls = 8

After balance:


*********************
Level - 0       40
Level - 1       60
Level - 2       70
Level - 3       80
Level - 2       50
Level - 1       20
Level - 2       30
Level - 2       10


*********************


numNodes = 8    calcLvls = 4    cntLvls = 4


        *** Run Complete ***
*/
