//PBiTree.h 三叉链表结构的二叉树类（PBiTree类）
#ifndef _PBITREE_H_
#define _PBITREE_H_
#define BiTNode PBiTNode
#include "BiTree.h"
template<typename T>class PBiTree:public BiTree<T>
{
public:
	void CreateBiTreeFromFile(ifstream &f)
	{
		T e;
		InputFromFile(f, e);
		if(e==Nil)
			return;
		root=new PBiTNode<T>;
		assert(root!=NULL);
		root->data=e;
		root->parent=NULL;
		PBiTree<T> left, right;
		left.CreateBiTreeFromFile(f);
		right.CreateBiTreeFromFile(f);
		root->lchild=left.root;
		if(left.root!=NULL)
		{
			left.root->parent=root;
			left.root=NULL;
		}
		root->rchild=right.root;
		if(right.root!=NULL)
		{
			right.root->parent=root;
			right.root=NULL;
		}
	}
	bool InsertChild(PBiTNode<T>* &p, bool LR, PBiTree<T> &c)
	{
	 
	 
		PBiTNode<T> *q=c.Root();
		c.root=NULL;
		if(p!=NULL)
		{
			if(!LR)
			{
				q->rchild=p->lchild;
				p->lchild->parent=q;
				p->lchild=q;
			}
			else
			{
				q->rchild=p->rchild;
				p->rchild->parent=q;
				p->rchild=q;
			}
			q->parent=p;
			return true;
		}
		return false;
	}
	BiTNode<T>* Parent(BiTNode<T>* p)const
	{
	 
		return p->parent;
	}
	bool Sibling(BiTNode<T>* p, BiTNode<T>* &sib, bool &LR)const
	{
	 
		if(p->parent==NULL)
			return false;
		if(p->parent->lchild==p)
		{
			sib=p->parent->rchild;
			LR=true;
		}
		else
		{
			sib=p->parent->lchild;
			LR=false;
		}
		return sib!=NULL;
	}
};
#endif

