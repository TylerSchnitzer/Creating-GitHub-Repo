#ifndef PQUEUETYPE_FLAG
#define PQUEUETYPE_FLAG
#include <iostream>
#include <string>
#include <cstddef>

using namespace std;

template <class elementType>
class pQueueType
{
	private:
		struct nodeType
		{
			elementType payLoad;
			nodeType *next,*right,*left;

			nodeType()
			{
				next=NULL;
				left=NULL;
				right=NULL;
				return;
			}
		};
		int numNodes;
		nodeType *root;
		nodeType **envPtr;
		void altDeleteTree(nodeType *p)
		{
			if( p )
			{
				altDeleteTree(p->left);
				altDeleteTree(p->right);
				delete p;
			}
			return;
		}

		void altcreate(nodeType *p)
		{
			if( p )
			{
				nodeType *q;
				q=p->next;

				p->next=NULL;
				delete p;
				altcreate( q );
			}
			return;
		}

		void altprint(nodeType *p)
		{
			if( p )
			{
				cout<<p->payLoad<<'\n';
				altprint(p->right);
				altprint(p->left);
				altprint(p->next);
			}
			return;
		}
		
	public:
		pQueueType()
		{
			root=NULL;
			
			return;
		}
		
		~pQueueType()
		{
			altcreate(root);

			return;
		}
		
		void create()
		{
			altcreate(root);
			root=NULL;

			return;
		}
		
		bool isRoom()
		{
			nodeType *p;
			p=new nodeType;
			if( p )
			{
				delete p;
				return true;
			}
			else
				return false;
		}
		
		void put(elementType &e)
		{
	
			if( !isThere(e) )
			{
				*envPtr=new nodeType;
				(*envPtr)->payLoad=e;
				numNodes++;
		
			}
			return;
		}
			
		bool isThere(elementType &e)
		{
			nodeType *p;
			envPtr=&root;
			while( *envPtr && (*envPtr)->payLoad != e )
				{
					if((*envPtr)->payLoad > e)
						envPtr=&(*envPtr)->left;
					else
						envPtr=&(*envPtr)->right;
				}
			
			return *envPtr;
		}
		
		void remove(elementType &e)
		{
			if( isThere(e) )
			{
				nodeType *p;
				p=*envPtr;
				*envPtr=(*envPtr)->next;

				p->next=NULL;
				delete p;
			}
		}
		
		void print()
		{
			cout<<"\n\n**************\n";
			if(root)
				altprint(root);
			else
				cout<<"Null root.\n";

			return;
		}
};
#endif