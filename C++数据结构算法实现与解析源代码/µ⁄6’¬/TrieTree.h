//TrieTree.h Trie ˜¿‡£®TrieTree¿‡£©
#ifndef _TRIETREE_H_
#define _TRIETREE_H_
const int LENGTH=26;
#include "TrieNode.h"
template<typename D>class TrieTree
{
private:
	TrieNode<D> *root;
	int MinEmpt;
	Record<D> record[N];
	static int ord(char &c)
	{
		if(c==Nil)
			return -1;
		else
			return c-'A';
	}
	void DestroyTrie(TrieNode<D>* &p)
	{
		int i, j=0;
		
		if(p!=NULL)
		{
			for(i=0; j<p->pnum && i<LENGTH; i++)
				if(p->ptr[i]!=NULL)
				{
					DestroyTrie(p->ptr[i]);
					j++;
				}
			delete p;
			p=NULL;
		}
	}
public:
	TrieTree()
	{
		root=NULL;
		for(int i=0; i<N; i++)
			record[i].key.ch[0]=Nil;
		MinEmpt=0;
	}
	~TrieTree()
	{
		DestroyTrie(root);
	}
	Record<D>* SearchTrie(K Key)const
	{
		TrieNode<D> *p=root;
		for(int i=0; p!=NULL && i<Key.num; i++)
			p=p->ptr[ord(Key.ch[i])];
		if(p!=NULL && p->rcptr!=NULL)
			return p->rcptr;
		else
			return NULL;
	}
	bool InsertTrie(Record<D> r)
	{
		TrieNode<D> *p, *q;
		int i, k;
		Record<D> *rc=SearchTrie(r.key);
		if(rc!=NULL||MinEmpt==N)
			return false;
		record[MinEmpt]=r;
		rc=&record[MinEmpt];
		for(i=MinEmpt+1; i<N; i++)
			if(record[i].key.ch[0]==Nil)
			{
				MinEmpt=i;
				break;
			}
		if(i==N)
			MinEmpt=N;
		if(root==NULL)
		{
			p=root=new TrieNode<D>;
			for(i=0; i<r.key.num; i++)
			{
				p->pnum=1;
				for(k=0; k<LENGTH; k++)
					p->ptr[k]=NULL;
				p->rcptr=NULL;
				p=p->ptr[ord(r.key.ch[i])]=new TrieNode<D>;
			}
			p->pnum=0;
			for(k=0; k<LENGTH; k++)
				p->ptr[k]=NULL;
			p->rcptr=rc;
		}
		else
		{
			p=root;
			for(i=0; p!=NULL && i<r.key.num; ++i)
			{
				q=p;
				p=p->ptr[ord(r.key.ch[i])];
			}
			if(p==NULL)
			{
				p=q->ptr[ord(r.key.ch[i-1])]=new TrieNode<D>;
				q->pnum++;
				for(; i<r.key.num; i++)
				{
					p->pnum=1;
					for(k=0; k<LENGTH; k++)
						p->ptr[k]=NULL;
					p->rcptr=NULL;
					p=p->ptr[ord(r.key.ch[i])]=new TrieNode<D>;
				}
				p->pnum=0;
				for(k=0; k<LENGTH; k++)
					p->ptr[k]=NULL;
			}
			p->rcptr=rc;
		}
		return true;
	}
	template<typename D>struct orderptr
	{
		TrieNode<D> *ptr;
		int order;
	};
	bool DeleteTrie(K Key, Record<D> &R)
	{
		TrieNode<D> *p=root;
		stack<orderptr<D> > S;
		orderptr<D> op;
		Record<D> *rc=SearchTrie(Key);
		if(rc==NULL)
			return false;
		for(int i=0; i<Key.num; ++i)
		{
			if(p->ptr[ord(Key.ch[i])]->pnum>1)
				while(!S.empty())
					S.pop();
			else
			{
				op.ptr=p;
				op.order=ord(Key.ch[i]);
				S.push(op);
			}
			p=p->ptr[ord(Key.ch[i])];
		}
		R=*p->rcptr;
		p->rcptr->key.ch[0]=Nil;
		if(p->rcptr-record<MinEmpt)
			MinEmpt=p->rcptr-record;
		p->rcptr=NULL;
		while(!S.empty())
		{
			op=S.top();
			S.pop();
			if(op.ptr->ptr[op.order]->rcptr==NULL && op.ptr->ptr[op.order]->pnum==0)
			{
				delete op.ptr->ptr[op.order];
				op.ptr->ptr[op.order]=NULL;
				op.ptr->pnum--;
			}
		}
		if(root->pnum==0)
		{
			delete root;
			root=NULL;
		}
		return true;
	}
	TrieNode<D>* Root()const
	{
		return root;
	}
	void TraverseTrie(TrieNode<D>* p, void(*visit)(Record<D>))const
	{
		int k=0;
		if(p!=NULL)
		{
			if(p->rcptr!=NULL)
			{
				visit(*(p->rcptr));
				j++;
				if(j%h==0)
					cout<<endl;
			}
			for(int i=0; i<LENGTH && k<p->pnum; i++)
				if(p->ptr[i]!=NULL)
				{
					TraverseTrie(p->ptr[i], visit);
					k++;
				}
		}
	}
	void Print(void(*visit)(Record<D>))
	{
		int k=0;
		for(int i=0; i<N; i++)
			if(record[i].key.ch[0]!=Nil)
			{
				visit(record[i]);
				k++;
				if(k%h==0)
					cout<<endl;
			}
	}
};
#endif

