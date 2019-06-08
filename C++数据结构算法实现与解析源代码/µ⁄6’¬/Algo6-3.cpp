//Algo6-3.cpp 静态树表类
#include "C.h"
#include "C4-1.h"
#include "BiTNode.h"
#include "BiTree.h"
typedef char KeyType;
#include "SqTable.h"
template<typename D>class SOSTree:public SqTable<D>
{
private:
	void FindSW()
	{
		if(length>0)
		{
			elem[0].sw=0;
			cout<<endl<<"sw=0 ";
			for(int i=1; i<=length; i++)
			{
				elem[i].sw=elem[i-1].sw+elem[i].weight;
				cout<<setw(6)<<elem[i].sw;
			}
		}
	}
	void SecondOptimal(BiTNode<D>* &p, int low, int high)
	{
		int j, i=low;
		int dw=elem[high].sw+elem[low-1].sw;
		int min=abs(elem[high].sw-elem[low].sw);
		for(j=low+1; j<=high; ++j)
			if(abs(dw-elem[j].sw-elem[j-1].sw)<min)
			{
				i=j;
				min=abs(dw-elem[j].sw-elem[j-1].sw);
			}
		p=new BiTNode<D>;
		assert(p!=NULL);
		p->data=elem[i];
		if(i==low)
			p->lchild=NULL;
		else
			SecondOptimal(p->lchild, low, i-1);
		if(i==high)
			p->rchild=NULL;
		else
			SecondOptimal(p->rchild, i+1,high);
	}
	BiTNode<D>* Search_SOSTree(BiTNode<D>* p, KeyType k)const
	{
	 
		if(p==NULL || EQ(k, p->data.key))
			return p;
		else if LT(k, p->data.key)
			return Search_SOSTree(p->lchild, k);
		else
			return Search_SOSTree(p->rchild, k);
	}
public:
	BiTree<D> t;
	void CreateSOSTree()
	{
		if(length>0)
		{
			FindSW();
			SecondOptimal(t.root, 1, length);
			
		}
	}
	BiTNode<D>* Search_SOSTree(KeyType k)const
	{
	 
		return Search_SOSTree(t.root, k);
	}
};
#include "Func6-2.cpp"
void main()
{
	SOSTree<S> st;
	KeyType k;
	BiTNode<S> *p;
	st.Creat_SeqFromFile("F6-3.txt");
	cout<<"       ";
	st.Traverse(Visit);
	st.CreateSOSTree();
	cout<<endl<<"先序遍历次优查找树st.t：";
	st.t.PreOrderTraverse(VisitT);
	cout<<endl<<"中序遍历次优查找树st.t：";
	st.t.InOrderTraverse(VisitT);
	cout<<"请输入待查找的字符：";
	InputKey(k);
	p=st.Search_SOSTree(k);
	if(p!=NULL)
		VisitT(p);
	else
		cout<<"表中不存在此字符";
	cout<<endl;
}

