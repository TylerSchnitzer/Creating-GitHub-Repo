#include  <iostream>
#include "itemType.h"
#include "pQueueType.cpp"

using namespace std;

int main()
{
    pQueueType<itemType> myLinkedList;
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

    cout<<"\n***Removing***\n";

    e="test value 1";
    myLinkedList.remove(e);
    myLinkedList.print();

    e="test value 4";
    myLinkedList.remove(e);
    myLinkedList.print();

    e="test value 6";
    myLinkedList.remove(e);
    myLinkedList.print();

    e="test value 2";
    myLinkedList.remove(e);
    myLinkedList.print();

    e="test value 3";
    myLinkedList.remove(e);
    myLinkedList.print();

    e="test value 5";
    myLinkedList.remove(e);
    myLinkedList.print();

    cout<<"\n\t***Run Complete**\n\n";
    return 0;
}

