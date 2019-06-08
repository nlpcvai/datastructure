//BiThrTree.h 线索二叉链表结构的二叉树类（BiThrTree类）
#ifndef _BITHRTREE_H_
#define _BITHRTREE_H_
#include "BiThrNode.h"
template<typename T>class BiThrTree
{
private:
	BiThrNode<T> *Thrt, *pre;
	
	void CreateBiThrTreeFromFile(ifstream &f, BiThrNode<T>* &t)
	{
		T e;
		InputFromFile(f, e);
		if(e==Nil)
			t=NULL;
		else
		{
			t=new BiThrNode<T>;
			assert(t!=NULL);
			t->data=e;
			CreateBiThrTreeFromFile(f, t->lchild);
			if(t->lchild!=NULL)
				t->LTag=Link;
			else
				t->LTag=Thread;
			CreateBiThrTreeFromFile(f, t->rchild);
			if(t->rchild!=NULL)
				t->RTag=Link;
			else
				t->RTag=Thread;
		}
	}
	void DestroyBiTree(BiThrNode<T>* &t)
	{
		if(t!=NULL)
		{
			if(t->LTag==Link)
				DestroyBiTree(t->lchild);
			if(t->RTag==Link)
				DestroyBiTree(t->rchild);
			delete t;
			t=NULL;
		}
	}
	void InOrderThreading(BiThrNode<T>* p)
	{
		if(p!=NULL)
		{
			if(p->LTag==Link)
				InOrderThreading(p->lchild);
			else
				p->lchild=pre;
			if(pre->RTag==Thread)
				pre->rchild=p;
			pre=p;
			if(p->RTag==Link)
				InOrderThreading(p->rchild);
		}
	}
	void PreOrderThreading(BiThrNode<T>* p)
	{
		if(p!=NULL)
		{
			if(pre->RTag==Thread)
				pre->rchild=p;
			if(p->LTag==Thread)
				p->lchild=pre;
			pre=p;
			if(p->LTag==Link)
				PreOrderThreading(p->lchild);
			if(p->RTag==Link)
				PreOrderThreading(p->rchild);
		}
	}
	void PostOrderThreading(BiThrNode<T>* p)
	{
		if(p!=NULL)
		{
			if(p->LTag==Link)
				PostOrderThreading(p->lchild);
			if(p->RTag==Link)
				PostOrderThreading(p->rchild);
			if(p->LTag==Thread)
				p->lchild=pre;
			if(pre->RTag==Thread)
				pre->rchild=p;
			pre=p;
		}
	}
public:
	BiThrTree()
	{
		Thrt=new BiThrNode<T>;
		assert(Thrt!=NULL);
		Thrt->LTag=Link;
		Thrt->RTag=Thread;
		Thrt->rchild=Thrt->lchild=Thrt;
	}
	~BiThrTree()
	{
		if(Thrt!=NULL)
		{
			if(Thrt->lchild)
				DestroyBiTree(Thrt->lchild);
				
			delete Thrt;
		}
	}
	void CreateBiThrTreeFromFile(char* FileName)
	{
		ifstream fin(FileName);
		CreateBiThrTreeFromFile(fin, Thrt->lchild);
		
		fin.close();
	}
	void InOrderThreading()
	{
		if(Thrt->lchild!=Thrt)
		{
			pre=Thrt;
			InOrderThreading(Thrt->lchild);
			
			pre->rchild=Thrt;
			Thrt->rchild=pre;
		}
	}
	void InOrderTraverse(void(*visit)(BiThrNode<T>*))const
	{
		BiThrNode<T> *p=Thrt->lchild;
		while(p!=Thrt)
		{
			while(p->LTag==Link)
				p=p->lchild;
			visit(p);
			while(p->RTag==Thread && p->rchild!=Thrt)
			{
				p=p->rchild;
				visit(p);
			}
			p=p->rchild;
			
		}
	}
	void PreOrderThreading()
	{
		if(Thrt->lchild!=Thrt)
		{
			pre=Thrt;
			PreOrderThreading(Thrt->lchild);
			pre->rchild=Thrt;
			Thrt->rchild=pre;
		}
	}
	void PreOrderTraverse(void(*visit)(BiThrNode<T>*))const
	{
		BiThrNode<T> *p=Thrt->lchild;
		while(p!=Thrt)
		{
			visit(p);
			if(p->LTag==Link)
				p=p->lchild;
			else
				p=p->rchild;
		}
	}
	void PostOrderThreading()
	{
		if(Thrt->lchild!=Thrt)
		{
			Thrt->rchild=Thrt->lchild;
			pre=Thrt;
			PostOrderThreading(Thrt->lchild);
			if(pre->RTag!=Link)
				pre->rchild=Thrt;
		}
	}
};
#endif

