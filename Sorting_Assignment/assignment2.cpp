// programming assignment

/*
	In this assignment, we will implement four sorting algorithms.  I have stubbed
	the sorting routines.  Before each sort, my code calls loadArr.  The counts in
	the array should sum to 3946 after loading.  before sorting, the array index may
	be interpreted as an ASCII code; however, the character and its weight stay together.

	You may choose the direction of your sort.
*/

#include <iostream>
#include <fstream>
#include <cstddef>
#include <ctype.h>
using namespace std;

struct statType
{
	char ascii;
	int	weight;
	
	void operator =(statType &i)
	{
		ascii=i.ascii;
		weight=i.weight;
	};
	bool operator ==(statType&);
	bool operator >(statType&);
	bool operator <(statType&);
	bool operator !=(statType&);
	bool operator <=(statType&);
	bool operator >=(statType&);
	
	void operator =(string);
	friend ostream&operator << (ostream&, const statType&);
	/*
		This is what you will be sorting by weight.
        
        You may define any operators you need (or want) on these objects.
		(I would think that, since we're sorting, the six relational operators
         and assignment would come in real handy!)
         
        I have written the printArr routine without using insertion on statType.         
	*/
};

const int ARR_BOUND=256;

void loadArr(statType*);
void printArr(statType*, string="");

void selectionSort(statType*);
void bubbleSort(statType*);
void insertionSort(statType*);
void heapSort(statType*);

int main()
{
	statType* dataArr;
	dataArr=new statType[ARR_BOUND];

	loadArr(dataArr);			// counts the occurrences of each  UTF-8 character in 
                                // a file by using the character's ASCII code as an
                                // array index and incrementing that array position.
                                // Your code will sort the array by weight.
                                
	printArr(dataArr, "Unsorted Data");			// prints the non-zero array positions
	selectionSort(dataArr);
	printArr(dataArr, "Selection Sort");			// prints the non-zero positions of the sorted array

//	Uncomment the lines as you implement them

	loadArr(dataArr);
	bubbleSort(dataArr);
	printArr(dataArr, "Bubble Sort");

	loadArr(dataArr);
	insertionSort(dataArr);
	printArr(dataArr, "Insertion Sort");

	loadArr(dataArr);
	heapSort(dataArr);
	printArr(dataArr, "Heap Sort");


	return 0;
}

// *************************************************

void loadArr(statType* arr)
{
	ifstream inFile;
	inFile.open("assignment2.input.txt");  // The input file must be in same directory as source file
	if( inFile.fail() )
	{
		cout<<"file error\n";
		cin.get();
		exit(1);
	}

	for(int i=0; i<ARR_BOUND; i++) // initialize the array
	{
		arr[i].ascii=(char)i;
		arr[i].weight=0;
	}

	char ch;
	while(true)
	{
		ch=inFile.get();
		cout<<ch;  // stream to console (optional).  
                   // Comment this line to suppress the echo print.

		if( inFile.eof() )
			break;

		arr[(int)ch].weight++;
	}
	inFile.close();
	inFile.clear(); // resets the IO flags
	cin.get();
}

// **************************************************

void printArr(statType* arr, string caption)
{
	int chCnt=0;
	cout<<"\n\n\t"<<caption<<'\n';
	for(int i=0; i<ARR_BOUND; i++)
		if(arr[i].weight)
		{
			cout<<"\t*\t"<<i<<'\t'<<arr[i].ascii<<'\t'<<arr[i].weight<<" ~\n";
			chCnt+=arr[i].weight;
		}
		cout<<"\n\n\t"<<chCnt<<" characters processed.\n\tInput paused, press 'Enter'"; // I get 3946
		cin.get();
}

//***************************************************

void selectionSort(statType* arr)
{
	int min;
	for(int i=0; i<ARR_BOUND-1; i++)
	{
		min=i;
		for(int j=i+1; j<ARR_BOUND; j++)
			if(arr[j].weight<arr[min].weight)
				min=j;
		struct statType temp;
		temp=arr[min];
		arr[min]=arr[i];
		arr[i]=temp;
	}
	// implement selectionsort; add any helping routines you need.
}

void bubbleSort(statType* arr)
{
	struct statType temp;
	for(int i=0; i<ARR_BOUND; i++)
	{
		for(int j=1; j<ARR_BOUND; j++)
		{
			if(arr[j].weight<arr[j-1].weight)
			{
				temp=arr[j];
				arr[j]=arr[j-1];
				arr[j-1]=temp;
			}
		}
	}
	// implement bubblesort; add any helping routines you need.
	// Include the optimization "early exit" feature that detects a sorted array.
}

void insertionSort(statType* arr)
{
	for(int i=1; i<ARR_BOUND; i++)
	{
		struct statType key=arr[i];
		int j=i-1;
		while(j>=0 && arr[j].weight>key.weight)
		{
			arr[j+1]=arr[j];
			j=j-1;
		}
		arr[j+1]=key;
	}
	// implement heapsort; add any helping routines you need.
}

void heapSort(statType* arr)
{

	for(int i=ARR_BOUND/2-1; i>=0; i--)
	{
		int parent=i;
		int left=2*i+1;
		int right=2*i+2;
		if(left<ARR_BOUND && arr[left].weight>arr[parent].weight)
		{
			parent=left;
		}
		if(right<ARR_BOUND && arr[right].weight>arr[parent].weight)
		{
			parent=right;
		}
		if(parent!=i)
		{
			struct statType temp;
			temp=arr[i];
			arr[i]=arr[parent];
			arr[parent]=temp;			
		}
	}
	for(int i=ARR_BOUND-1; i>=0; i--)
	{
		struct statType temp;
		temp=arr[0];
		arr[0]=arr[i];
		arr[i]=temp;
		int parent=0;
		int left=2*0+1;
		int right=2*0+2;
		if(left<i && arr[left].weight>arr[parent].weight)
		{
			parent=left;
		}
		if(right<i && arr[right].weight>arr[parent].weight)
		{
			parent=right;
		}
		if(parent!=0)
		{
			struct statType temp;
			temp=arr[0];
			arr[0]=arr[i];
			arr[i]=temp;
		}
	}
	// implement heapsort; add any helping routines you need.
}
