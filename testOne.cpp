#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */
#include <iostream>
using namespace std;

const int MAX=128;  // size of the array

bool binSearch(int *intArray, int left, int right, int search); // add whatever parameters you need

int main ()
{
    // Do not modify main().

    int* intArray;
    intArray=new int[MAX];  // do *not* make the array global!!!
    intArray[0]=1;

    // loads the array with unique "random" integers in ascending order

    srand (time(NULL));
    for(int i=1; i<MAX; i++)
        intArray[i]=intArray[i-1]+rand()%5+1;

    // the intArray now contains MAX integers such that, for all i in the range 0..MAX-2,
    // intArray[i] < intArray[i+1].  I.e.: the values are sorted.  If "less than" holds,
    // then there can be no duplicate values.  It is not possible to have any value greater
    // than 512 in the array.

    // the search runs 512 (MAX*4) iterations; it should find 128 (MAX) values.

    int cnt=0;
    for(int i=0; i<4*MAX; i++)
        if( binSearch(intArray, 0, MAX, i) )// add parameters you need to the call
            cnt++;

    cout<<"\n\nThe expected count is 128.\nYour count is: "<<cnt;

    cout<<"\n\nRun Complete.\n\n";

  return 0;
}

//************************************

bool binSearch(int *intArray, int left, int right, int search)  // Add the parameters you need.
{
    if(right>=left)
    {
        int mid=left+(right-left)/2;

        if(intArray[mid]==search)
        {
            return true;
        } 
        if(intArray[mid]>search)
        {
            return binSearch(intArray, left, mid-1, search);
        }
        return binSearch(intArray, mid+1, right, search);
    }
    return false;


/*
    Test One Instructions:  You will modify the Boolean function binSearch
    to search the array of size MAX named "intArray" where intArray is already
    loaded & sorted and the search term is passed in as a parameter
*/
}

