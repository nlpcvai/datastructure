//DLTree.h Ë«Á´¼üÊ÷Àà£¨DLTreeÀà£©
#ifndef _DLTREE_H_
#define _DLTREE_H_
#include "DLTNode.h"
template<typename D>class DLTree
{
private:
	DLTNode<D> *dst;
	int MinEmpt;
	Record<D> record[N];
	void DestroyDSTable(DLTNode<D>* &p)
	{
		if(p!=NULL)
		{
			if(p->kind==BRANCH)
				DestroyDSTable(p->first);
			DestroyDSTable(p->next);
			delete p;
			p=NULL;
		}
	}
public:
	DLTree()
	{
		dst=new DLTNode<D>;
		dst->first=dst->next=NULL;
		dst->kind=BRANCH;
		for(int i=0; i<N; i++)
		
			record[i].key.ch[0]=Nil;
		MinEmpt=0;
		
	}
	~DLTree()
	{
		DestroyDSTable(dst);
	}
	Record<D>* SearchDSTable(K Key)const
	{
		DLTNode<D> *p=dst->first;
		int i=0;
		while(p!=NULL && i<Key.num)
		{
			while(p!=NULL && p->symbol<Key.ch[i])
				p=p->next;
			if(p!=NULL && p->symbol==Key.ch[i])
			{
				p=p->first;
				++i;
			}
			else
				p=NULL;
		}
		if(p!=NULL && p->kind==LEAF)
			return p->rcptr;
		else
			return NULL;
	}
	bool InsertDSTable(Record<D> re)
	{
	 
		DLTNode<D> *q=dst, *p=dst->first, *ap;
		int i;
		K Key=re.key;
		Record<D> *pr=SearchDSTable(Key);
		if(pr!=NULL || MinEmpt==N)
		
			return false;
		record[MinEmpt]=re;
		pr=&record[MinEmpt];
		for(i=MinEmpt+1; i<N; i++)
			if(record[i].key.ch[0]==Nil)
			{
				MinEmpt=i;
				break;
			}
		if(i==N)
			MinEmpt=N;
		i=0;
		while(p!=NULL && i<Key.num)
		{
			while(p!=NULL && p->symbol<Key.ch[i])
			{
				q=p;
				p=p->next;
			}
			if(p!=NULL && p->symbol==Key.ch[i])
			{
				q=p;
				p=p->first;
				++i;
			}
			else
				break;
		}
		ap=new DLTNode<D>;
		if(q->first==p)
			q->first=ap;
		else
			q->next=ap;
		if(i==Key.num)
		{
			ap->next=p;
			ap->symbol=Nil;
			ap->kind=LEAF;
			ap->rcptr=pr;
			return true;
		}
		else
		{
			ap->next=p;
			ap->symbol=Key.ch[i];
			ap->kind=BRANCH;
			p=ap;
			ap=new DLTNode<D>;
			for(++i; i<Key.num; i++)
			{
				p->first=ap;
				ap->next=NULL;
				ap->symbol=Key.ch[i];
				ap->kind=BRANCH;
				p=ap;
				ap=new DLTNode<D>;
			}
			p->first=ap;
			ap->next=NULL;
			ap->symbol=Nil;
			ap->kind=LEAF;
			ap->rcptr=pr;
			return true;
		}
	}
	template<typename D>struct flagptr
	{
		DLTNode<D> *ptr;
		bool flag;
	};
	bool DeleteDSTable(K Key, Record<D> &R)
	{
	 
		DLTNode<D> *p=dst, *q=NULL;
		stack<flagptr<D> > S;
		flagptr<D> fp;
		Record<D> *rc=SearchDSTable(Key);
		if(rc==NULL)
			return false;
		fp.ptr=p;
		fp.flag=false;
		S.push(fp);
		for(int i=0; i<Key.num; ++i)
		{
			p=p->first;
			while(p->symbol<Key.ch[i])
			{
				fp.ptr=p;
				fp.flag=true;
				S.push(fp);
				p=p->next;
			}
			fp.ptr=p;
			fp.flag=false;
			S.push(fp);
		}
		p=p->first;
		R=*p->rcptr;
		p->rcptr->key.ch[0]=Nil;
		p->rcptr=NULL;
		if(p->rcptr-record<MinEmpt)
			MinEmpt=p->rcptr-record;
		while(!S.empty() && q==NULL)
		{
			q=p->next;
			fp=S.top();
			S.pop();
			if(fp.flag)
				fp.ptr->next=q;
			else
				fp.ptr->first=q;
			delete p;
			p=NULL;
			p=fp.ptr;
			if(p->first!=NULL)
				break;
		}
		return true;
	}
	DLTNode<D>* Root()const
	{
		return dst;
	}
	void TraverseDSTable(DLTNode<D>* p, void(*visit)(Record<D>))const
	{
		if(p!=NULL)
		{
			if(p->kind==BRANCH)
				TraverseDSTable(p->first, visit);
			else
			{
				j++;
				visit(*p->rcptr);
				if(j%h==0)
					cout<<endl;
			}
			TraverseDSTable(p->next, visit);
		}
	}
	void Print(void(*visit)(Record<D>))
	{
		int k=0;
		for(int i=0; i<N; i++)
			if(record[i].key.ch[0]!=Nil)
			{
				k++;
				visit(record[i]);
				if(k%h==0)
					cout<<endl;
			}
		cout<<endl;
	}
};
#endif

