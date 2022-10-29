#include <iostream>
//#include "itemType.h"
using namespace std;

template <class elementType>
class listType
{

	private:
		static const int HASH_SPACE = 0x80; // 128 in hex

		// the definition of the struct nodeType is private
		struct nodeType
		{
			elementType payLoad;
			nodeType* next;

			nodeType()
			{
				next=NULL;

				return;
			}
		};

		nodeType **roots, **envPtr;


		int getHashIndex(unsigned long k)
		{
			return k%HASH_SPACE;
		}


	public:
		listType()
		{
			roots = new nodeType*[HASH_SPACE];

			for(int i=0; i<HASH_SPACE; i++)
				roots[i]=NULL;

			envPtr=NULL;
		}



		bool isThere(elementType &e)  // demonstrating getHashIndex
		{
			unsigned long h = e.getHash();

			int i = getHashIndex(h);

			cout<<"The long int (in hex) returned from itemType is: "
				<<hex<<h<<'\n'<<"The index for "<<e.identifier
				<<" will be "<<hex<<i<<" in hex or "<<dec<<i
				<<" in decimal.\n\n";


			// This would work just fine:
			// int index = getHashIndex( e.getHash() );


			return true;
		}


};


