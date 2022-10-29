// listType.cpp				S.W. Smith

#ifndef LISTTYPE_FLAG
#define LISTTYPE_FLAG
#include <iostream>
#include <cmath>
using namespace std;

template <class elementType>
class listType
{
	private:
		// the definition of the struct nodeType is private
		struct nodeType
		{
			elementType payLoad;
			nodeType *left, *right;

			nodeType()
			{
				left=NULL;
				right=NULL;
				return;
			}
		};

		int numNodes, numLvls;

		nodeType *root;

		nodeType **envPtr; // double Pointer!!!  (This is new.)

		//**************************************
		// called by create() and the destructor;
		void altDeleteTree(nodeType *p) // version with the recursion at end of the logic.
		{
			if( p )
			{
				altDeleteTree(p->left);
				altDeleteTree(p->right);
				delete p;
			}

			return;
		}

		//***********************************
		// wrapper method for print()
		void altPrint(nodeType *p, int level)
		{
			if(p)
			{
				cout<<"Level - "<<level<<'\t'<<p->payLoad<<'\n';
				altPrint(p->right, level+1);
				altPrint(p->left, level+1);
			}
			return;
		}
		//************************************
		// diagnostic routines

		int cntLvls(nodeType *p)
		{
			numLvls=0;
			altCntLvls(p, 1);
			return numLvls;
		}


		void altCntLvls(nodeType *p, int i)
		{
			if(!p)
				return;
			else
			{
				if(i>numLvls)
					numLvls=i; // numLvls is a class variable

				altCntLvls(p->left, i+1);
				altCntLvls(p->right, i+1);
			}
		}

		//***************************************

		int calcLvls()
		{
			return ceil( log(numNodes+1)/log(2));
		}




	public:
		listType()
		{
			numNodes=0;
			root=NULL;
			envPtr=NULL;

			return;
		} // constructor.

		//******************************

		~listType()
		{
			altDeleteTree(root); // this deletes an existing list

			return;
		} // destructor.

		//******************************

		void create()
		{
			altDeleteTree(root);
			root=NULL;
			numNodes=0;

			return;
		}

		//******************************

		bool isRoom()
		{
			// There is no standard way to do this with 100% certainty.
			// Here is one approach:

			nodeType *p;
			p=new nodeType;
			if( p ) // allocation failure returns NULL pointer
			{
				delete p;
				return true;
			}
			else return false;

		}

		//****************************************

		bool isThere(elementType &e)
		{
			envPtr=&root;
			while( *envPtr  &&  (*envPtr)->payLoad != e )
				if((*envPtr)->payLoad > e)
					envPtr=&(*envPtr)->left;
				else
					envPtr=&(*envPtr)->right;

			return *envPtr;
		}

		//******************************

		void showTreeStats()
		{
						cout<<"\n\nnumNodes = "<<numNodes<<"\tcalcLvls = "<<calcLvls()<<"\tcntLvls = "<<cntLvls(root)<<"\n\n";
						//<<'\t'<<(double)numLvls(root)/calcLvls()<<"\n\n";
		}


		void put(elementType &e)
		{
			// I should check isRoom() here.  Not sure what I'd do
			// if it failed to allocate.  I suppose ask the user?

			// inserting a node into a leaf of a binary tree:
			if(  !isThere(e) )
			{
				*envPtr=new nodeType;
				(*envPtr)->payLoad=e;  // note: always inserts at a "leaf" node.
				numNodes++;
			}

			return;
		}


		//******************************

		void remove(elementType &e)
		{
			/*
				The algorithm for remove in pseudocode:

				if isThere(e) - sets envPtr

					There are two possibilities: the node has two children or it does not.
					if !left || !right - if true, then NOT two children (write it as you please)

						if left
							then the right pointer is NULL; treat the left pointer as a linked list
							declare a pointer (I'll call it *p) and set it: p=*envPtr
							now, execute as if inserting into a linked list where "next" is "left".
						else
							same as above, but on the right.  Both children NULL just falls through this side.

					else - two children!

							We must find the largest node with a payLoad smaller than e.  Now, think!
							Where is the largest node in a binary tree as we have defined it?  Answer:
							As far right as you can go.  This value must be less than e; therefore, it
							must be in its left sub-tree.  To find that node, use a double pointer (**dp);
							go left once, then all the way right until you hit NULL right pointer.  That is
							the next smaller node.  (The algorithm will also work on the next larger node,
							and the algorithm is symmetric.)

							Now, it gets tricky: declare two single node pointers: *p and *q are mine.
								p=*envPtr
								q=*dp

								To test it at this point, take the tree as I built it in the driver and remove 60
								cout<<p->payLoad should be 60
								cout<<q->payLoad should be 55



								*dp adopts the left child of q
								q's left pointer adopts p's left child
								q's right pointer adopts p's right child
								*envPtr gets q

								both of p's children are set to NULL
								delete p

								Now, draw the tree and make sure 60 was removed and
								that you print 8 nodes.

								decrement numNodes here
			*/

			// Write your code to remove here

			return;

		}

		//******************************

		void print() // for diagnostics only
		{
			cout<<"\n\n*********************\n";

			altPrint(root, 0);

			cout<<"\n\n*********************\n";
			return;
		}
};
#endif

