//BTree.h B ˜¿‡£®BTree¿‡£©
#ifndef _BTREE_H_
#define _BTREE_H_
#include "BTNode.h"
template<typename D>class BTree
{
private:
	BTNode<D> *root;
	int s;
	int MinEmpt;
	Record<D> record[N];
	void DestroyBTree(BTNode<D>* t)
	{
		if(t!=NULL)
		{
			for(int i=0; i<=t->keynum; i++)
			
				DestroyBTree(t->children[i]);
				
			delete t;
			t=NULL;
		}
	}
	int Search(BTNode<D>* p, KeyType k)const
	{
		int i=0, j;
		for(j=1; j<=p->keynum; j++)
			if LQ(p->key[j], k)
				i=j;
			else
				break;
			return i;
	}
	void MoveItim2(BTNode<D>* p, int i, BTNode<D>* q, int j)
	{
		p->key[i]=q->key[j];
		p->recptr[i]=q->recptr[j];
	}
	void MoveItim3(BTNode<D>* p, int i, BTNode<D>* q, int j)
	{
		p->key[i]=q->key[j];
		p->recptr[i]=q->recptr[j];
		p->children[i]=q->children[j];
	}
	void Copy(BTNode<D>* q, int i, Record<D>* r)
	{
		q->key[i]=r->key;
		q->recptr[i]=r;
	}
	void Insert(BTNode<D>* q, int i, Record<D>* r, BTNode<D>* ap)
	{
	 
		for(int j=q->keynum; j>i; j--)
			MoveItim3(q, j+1, q, j);
		Copy(q, i+1, r);
		q->children[i+1]=ap;
		if(ap!=NULL)
			ap->parent=q;
		q->keynum++;
	}
	void split(BTNode<D>* q, BTNode<D>* &ap)
	{
	 
		ap=new BTNode<D>;
		ap->children[0]=q->children[s];
		if(ap->children[0]!=NULL)
			ap->children[0]->parent=ap;
		for(int i=s+1; i<=m; i++)
		{
			MoveItim3(ap, i-s, q, i);
			if(ap->children[i-s]!=NULL)
				ap->children[i-s]->parent=ap;
		}
		ap->keynum=m-s;
		q->keynum=s-1;
	}
	void NewRoot(Record<D>* r, BTNode<D>* ap)
	{
		BTNode<D> *p=new BTNode<D>;
		p->parent=NULL;
		p->keynum=1;
		Copy(p, 1, r);
		p->children[0]=root;
		if(root!=NULL)
			root->parent=p;
		p->children[1]=ap;
		if(ap!=NULL)
			ap->parent=p;
		root=p;
	}
	void InsertBTree(Record<D>* r, BTNode<D>* q, int i)
	{
	 
		BTNode<D> *ap=NULL;
		bool finished=false;
		while(q && !finished)
		{
			Insert(q, i, r, ap);
								
			if(q->keynum<m)
				finished=true;
			else
			{
				r=q->recptr[s];
				split(q, ap);
				
				
				q=q->parent;
				if(q!=NULL)
					i=Search(q, r->key);
			}
		}
		if(!finished)
			NewRoot(r, ap);
	}
	bool Move(BTNode<D>* &p)
	{
	 
		BTNode<D> *a, *f=p->parent;
		int i, j;
		for(i=0; f->children[i]!=p; i++);
		if(i>0 && f->children[i-1]->keynum>(m-1)/2)
		{
			a=f->children[i-1];
			for(j=p->keynum; j>0; j--)
				MoveItim3(p, j+1, p, j);
			p->children[1]=p->children[0];
			MoveItim2(p, 1, f, i);
			p->keynum++;
			MoveItim2(f, i, a, a->keynum);
			p->children[0]=a->children[a->keynum];
			if(a->children[a->keynum]!=NULL)
				a->children[a->keynum]->parent=p;
			a->keynum--;
			return true;
		}
		else if(i<f->keynum && f->children[i+1]->keynum>(m-1)/2)
		{
			a=f->children[i+1];
			MoveItim2(p, p->keynum+1, f, i+1);
			MoveItim2(f, i+1, a, 1);
			p->children[p->keynum+1]=a->children[0];
			p->keynum++;
			if(a->children[0]!=NULL)
				a->children[0]->parent=p;
			for(int j=1; j<a->keynum; j++)
			{
				MoveItim2(a, j, a, j+1);
				a->children[j-1]=a->children[j];
			}
			a->children[a->keynum-1]=a->children[a->keynum];
			a->keynum--;
			return true;
		}
		return false;
	}
	BTNode<D>* Merge(BTNode<D>* &p)
	{
		BTNode<D> *b, *f=p->parent;
		int i, j;
		for(i=0; f->children[i]!=p; i++);
		if(i>0)
		{
			b=f->children[i-1];
			for(j=0; j<=p->keynum; j++)
				if(p->children[j]!=NULL)
					p->children[j]->parent=b;
			++b->keynum;
			MoveItim2(b, b->keynum, f, i);
			b->children[b->keynum]=p->children[0];
			for(j=1; j<=p->keynum; j++)
			{
				++b->keynum;
				MoveItim3(b, b->keynum, p, j);
			}
			delete p;
			for(j=i+1; j<=f->keynum; j++)
				MoveItim3(f, j-1, f, j);
			f->keynum--;
		}
		else
		{
			b=p;
			p=f->children[i+1];
			for(j=0; j<=p->keynum; j++)
				if(p->children[j]!=NULL)
					p->children[j]->parent=b;
			++b->keynum;
			MoveItim2(b, b->keynum, f, i+1);
			b->children[b->keynum]=p->children[0];
			for(j=1; j<=p->keynum; j++)
			{
				++b->keynum;
				MoveItim3(b, b->keynum, p, j);
			}
			delete p;
			for(j=i+1; j<f->keynum; j++)
				MoveItim3(f, j, f, j+1);
			f->keynum--;
		}
		return b;
	}
public:
	BTree()
	{
		root=NULL;
		for(int i=0; i<N; i++)
			record[i].key=EMPTY;
		MinEmpt=0;
		s=(m+1)/2;
	}
	~BTree()
	{
		DestroyBTree(root);
	}
	BTNode<D>* Root()const
	{
		return root;
	}
	void TraverseBTree(BTNode<D>* t, void(*visit)(Record<D>))const
	{
		if(t!=NULL)
			for(int i=0; i<=t->keynum; i++)
			{
				if(i>0)
					visit(*(t->recptr[i]));
				if(t->children[i]!=NULL)
					TraverseBTree(t->children[i], visit);
					
			}
	}
	Result<D> SearchBTree(KeyType k)const
	{
	 
	 
		BTNode<D> *p=root, *q=NULL;
		bool found=false;
		int i=0;
		Result<D> r;
		while(p!=NULL && !found)
		{
			i=Search(p, k);
			if(i>0 && p->key[i]==k)
				found=true;
			else
			{
				q=p;
				p=p->children[i];
			}
		}
		if(found)
		{
			r.pt=p;
			r.tag=true;
		}
		else
		{
			r.pt=q;
			r.tag=false;
		}
		r.i=i;
		return r;
	}
	bool InsertRecord(Record<D> re)
	{
	 
		Result<D> u=SearchBTree(re.key);
		if(u.tag)
			return false;
		if(MinEmpt<N)
		{
			record[MinEmpt]=re;
			InsertBTree(&record[MinEmpt], u.pt, u.i);
			
			for(int k=MinEmpt+1; k<N; k++)
				if(record[k].key==EMPTY)
				{
					MinEmpt=k;
					break;
				}
			if(k==N)
				MinEmpt=N;
			return true;
		}
		else
			return false;
	}
	bool DeleteBTree(Record<D> &re, KeyType k)
	{
		int i, j;
		BTNode<D> *p, *q;
		Result<D> u=SearchBTree(k);
		if(u.tag==0)
			return false;
		i=u.i;
		p=u.pt;
		re=*(p->recptr[i]);
		p->recptr[i]->key=EMPTY;
		if(p->recptr[i]-record<MinEmpt)
			MinEmpt=p->recptr[i]-record;
		if(p->children[i-1]!=NULL)
		{
			q=p->children[i-1];
			while(q->children[q->keynum]!=NULL)
				q=q->children[q->keynum];
			if(q->keynum>(m-1)/2)
			{
				MoveItim2(p, i, q, q->keynum);
				p=q;
				i=q->keynum;
			}
			else
			{
				q=p->children[i];
				while(q->children[0]!=NULL)
					q=q->children[0];
				MoveItim2(p, i, q, 1);
				p=q;
				i=0;
			}
		}
		for(j=i+1; j<=p->keynum; j++)
			MoveItim2(p, j-1, p, j);
		p->keynum--;
		while(p->keynum<(m-1)/2 && (p!=root))
		{
			if(!Move(p))
				p=Merge(p);
			p=p->parent;
		}
		if(p==root && root->keynum==0)
		{
			root=root->children[0];
			if(root!=NULL)
				root->parent=NULL;
			delete p;
		}
		return true;
	}
	void Print()
	{
		for(int i=0; i<N; i++)
			if(record[i].key!=EMPTY)
				Visit(record[i]);
	}
};
#endif

