// listType.cpp				S.W. Smith
#ifndef LISTTYPE_FLAG
#define LISTTYPE_FLAG
#include <iostream>
using namespace std;

template <class elementType>
class listType
{
	private:
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

		nodeType *root;

		//	nodeType *envPtr; // we will have *much* to say about this!

		//**************************************
/*
		void altCreate(nodeType *p)
		{
			if(p)
			{
				altCreate(p->next);
				delete p;
			}   // we'd like to have the recursive call after delete.

			return;
		}
*/
		//***********************************
		// wrapper method for create()
		void altCreate(nodeType *p) // a better version with recursion at end of the logic.
		{
			if( p )
			{
				nodeType *q;
				q=p->next; // maybe q is NULL, maybe not.

				p->next=NULL;
				delete p;
				altCreate( q );
			}

			return;
		}

		//***********************************
		// wrapper method for print()
		void altPrint(nodeType *p)
		{
			if(p)
			{
				cout<<p->payLoad<<'\n';
				altPrint(p->next);
			}

			return;
		}
		//************************************
	public:
		listType()
		{
			root=NULL;

			return;
		} // constructor.

		//******************************

		~listType()
		{
			altCreate(root); // this deletes an existing list

			return;
		} // destructor.

		//******************************

		void create()
		{
			altCreate(root);
			root=NULL;

			return;
		}

		//******************************

		bool isRoom()
		{
			return true; // this will do for now; more to come later on this.
		}

		//****************************************

		bool isThere(elementType &e)
		{
			nodeType *p;
			p=root;
			while( p  &&  p->payLoad != e )
				p=p->next;

			return p;
		}

		//******************************
/*
		// one option for example:

		void put(elementType &e)
		{
			// inserting a node at the beginning of a linked list:
			if( !isThere(e) )
			{
				nodeType* p;
				p=new nodeType;
				p->payLoad=e;

				p->next=root;
				root=p;
			}

			return;
		}
*/
		//******************************
/*
		// A second example option:
		void put(elementType &e)
		{
			// inserting a node at the end of a linked list:
			if( !isThere(e) )
			{
				if(!root) // if root is NULL
				{
					root=new nodeType;
					root->payLoad=e;
				}
				else
				{
					nodeType* p;
					p=root;

					while(p->next)
						p=p->next;	// loop exits on last node

					p->next=new nodeType;
					p=p->next;
					p->payLoad=e;
				}
			}

			return;
		}
*/
		//****************************************
		// inserting a node into an ordered list.  This will be the class' working example
		// This logic will also be used in the enQueue method of the priority queue
		void put(elementType &e)
		{
			if( !isThere(e) )
			{
				nodeType *p, *q;
				p = root;
				q = NULL;

				while( p && p->payLoad>e) // >e sorts in descending order
				{											 // <e sorts in ascending order
					q=p;
					p=p->next;
				}

				if( !q )  // when q is NULL, we're inserting at root
				{			// p can be NULL.
					root=new nodeType;
					root->payLoad=e;
					root->next=p;  // p==NULL doesn't hurt it anything
				}
				else // inserting further on beyond root
				{		// p could still be NULL
					q->next=new nodeType;
					q=q->next;
					q->payLoad=e;
					q->next=p;  // p==NULL: OK
				}
			}

			return;
		}

		//******************************

		void remove(elementType &e)
		{
		// Removes a node from a linked list and preserves the order of the rest of the nodes.
		// This logic will be used in the enQueue method of the priority queue
			if( isThere(e) )
			{
				nodeType *p, *q;
				p = root;
				q = NULL;


				while( p->payLoad != e ) // since we know it's there,
														// we'll find it before p is NULL
				{	// step through the list keeping a pointer to the previous node.
					q=p;
					p=p->next;
				}

				if( !q )  // when q is NULL, we're deleting the root node
							// and that p==root; we know that p is not NULL.
					root=root->next;
				else // deleting p; p is not NULL
					q->next=p->next;

				p->next=NULL;
				delete p;
			}

			return;
		}

		//******************************

		void print() // for diagnostics only
		{
			cout<<"\n\n*********************\n";
			if(root)
				altPrint(root); // this line is all that's needed; everything else is optional
									// altPrint is recursive
			else
				cout<<"Null root.\n";

			return;
		}
};
#endif

