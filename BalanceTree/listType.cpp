// listType.cpp		Tyler Schnitzer

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
		void altDelete(nodeType *p) // recursive procedure with a public wrapper: void listType::delete();
		{
			if( p )
			{
				altDelete(p->left);
				altDelete(p->right);
				delete p;
			}

			return;
		}

		//***********************************
		// recursive method for print()
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

		// diagnostic routines for balance routine follow.  Counting levels is used
		// extensively in balancing a binary tree

		int cntLvls(nodeType *p) // counts the number of levels in a tree or subtree
		{
			numLvls=0;
			altCntLvls(p, 1);
			return numLvls;
		}


		void altCntLvls(nodeType *p, int i) //  recursive, called by int cntLvls(nodeType)
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


		int calcLvls() // calculates the number of levels in a perfect tree (could be made public)
		{
			return ceil( log(numNodes+1)/log(2)); // ceiling(  log2( numNodes+1)  )    #include <cmath>
		}

// Routines to manipulate tree for balance:

		void rotL(nodeType **dp) // rotates a simple, three-node, two-level tree left while
		{											// preserving the logical structure of the subtrees.
			nodeType *p;  p=*dp;
			*dp=p->right;
			p->right=(*dp)->left;
			(*dp)->left=p;
		}

		void rotR(nodeType **dp) // same as above, but rotates right.  Note the double pointer parameter
		{
			nodeType *p;  p=*dp;
			*dp=p->left;
			p->left=(*dp)->right;
			(*dp)->right=p;
		}

/*
	The working definition of "balanced" is:

	-->if the pointer is NULL, it's balanced.

	-->else, it's balanced when both its left and right subtrees are balanced and differ in
	height by on more than one level.

	While this definition won't always produce a *perfect* binary tree, it will be within 10%
	of perfect.  I.e.: a 1000-node tree might have 11 levels.  Using this definition lends
	itself to a concise, recursive balancing algorithm:

	balance(&p)
		if *p is NULL
			return; it's balanced
		else
			balance( &left child )
			balance( &right child )
			count the levels in both
			if they are within one, we're done
			else
				is there an inside grandchild?  Rotate the child to the outside.
				rotate the tree toward the smaller side
				balance( &p )

	See the Word file "rotations.docx" for a graphical
	discussion of one issue not covered here.
*/

	void balanceTree(nodeType **root)
	{
		int height; 
		nodeType *p; p = *root;
		if(p->left == NULL && p->right == NULL){
			return;
		}
		else{
			cntLvls(p->left);
			cntLvls(p->right);
			if(cntLvls(p->left) <= 1 && cntLvls(p->right) <=1){
				return;
			}
			else{
				if(cntLvls(rotL(&p)) <= 1 && cntLvls(rotR(&p))){
					return;
				}
			}
		}
	


		/*
			Here is where you will put your code to balance the tree.
		*/

	}

	public:

	
	void testRotL() // test routine; test only.
	{
		if(  root->right->left )
			rotR( &(root->right) );

		rotL(&root);
	}

	void testRotR() // test routine; test only.
	{
//		if(  root->left->right )
//			rotL( &(root->left) );

		rotR(&root); // tests rotating root
	}

	void balance() // executes balance routine
	{

		balanceTree(&root);
			

	}

	void showTreeStats()  // a handy routine to see what you have.
	{
		cout<<"\n\nnumNodes = "<<numNodes<<"\tcalcLvls = "<<calcLvls()<<"\tcntLvls = "<<cntLvls(root)<<"\n\n";
	}


		listType()
		{
			root=NULL;
			envPtr=NULL;
			numNodes=0;
			return;
		} // constructor.

		//******************************

		~listType()
		{
			altDelete(root); // this deletes an existing list

			return;
		} // destructor.

		//******************************

		void create()
		{
			altDelete(root);
			root=NULL;

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

		/*
			isThere sets a double pointer to where the element
			was found or where it would have been found were
			it there.
		*/
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

		void put(elementType e)
		{
			// I should check isRoom() here.  Not sure what I'd do
			// if it failed to allocate.  I suppose ask the user?

			// inserting a node into a leaf of a binary tree:
			if(  !isThere(e) )
			{
				*envPtr=new nodeType;
				(*envPtr)->payLoad=e;  // note: always inserts at a "leaf".

				numNodes++;
			}
			return;
		}


		//******************************

		void remove(elementType &e)
		{
			/*
				remove(elementType &) isn't called for in this assignment.
				If it's here, fine; if not, also fine.



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

								To test it at this point, take the tree as I built it in the driver and remove

								*dp adopts the left child of q
								q's left pointer adopts p's left child
								q's right pointer adopts p's right child
								*envPtr gets q

								both of p's children are set to NULL
								delete p

								Now, draw the tree and make sure

								numNodes--;
			*/


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

