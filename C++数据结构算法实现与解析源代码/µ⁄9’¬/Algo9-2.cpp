//Algo9-2.cpp 伙伴系统类
#include "C.h"
#include "DLinkListNH.h"
const int m=5;
const int N=16;
class BuddySystem
{
private:
	struct T
	{
		bool tag;
		int kval;
	};
	struct HeadNode
	{
		int size;
		DLinkListNH<T> first;
	};
	HeadNode FreeList[m+1];
	DLNode<T> *t;
	list<DLNode<T>*> occ;
	DLNode<T>* buddy(DLNode<T>* p)
	{
		if((p-t)%(int)pow(2, p->data.kval+1)==0)
			return p+(int)pow(2, p->data.kval);
		else
			return p-(int)pow(2, p->data.kval);
	}
public:
	BuddySystem()
	{
		int i;
		t=new DLNode<T>[(int)pow(2, m)];
		
		assert(t!=NULL);
		t->data.tag=false;
		t->data.kval=m;
		for(i=0; i<=m; i++)
		{
			FreeList[i].size=(int)pow(2, i);
			FreeList[i].first.Head=NULL;
		}
		FreeList[m].first.ListInsert(1,t);
		cout<<"双循环链表结点DLNode<T>为"<<sizeof(DLNode<T>)<<"个字节"<<endl;
		cout<<"m="<<m<<" 存储管理空间="<<(int)pow(2, m);
		cout<<" 占用块个数的最大值N="<<N<<endl;
		Print();
	}
	~BuddySystem()
	{
		int i;
		delete[]t;
		for(i=0; i<=m; i++)
			FreeList[i].first.Head=NULL;
	}
	bool AllocBuddy(int n)
	{
		int i, k;
		DLNode<T> *pa, *pi;
		for(k=0; k<=m && (FreeList[k].size<n||FreeList[k].first.Head==NULL); ++k);
		
		if(k>m)
			pa=NULL;
		else
		{
			pa=FreeList[k].first.Head;
			FreeList[k].first.ListDelete(pa);
			
			for(i=1; FreeList[k-i].size>=n; ++i)
			{
				pi=pa+(int)pow(2, k-i);
				FreeList[k-i].first.ListInsert(1, pi);
				
				pi->data.tag=false;
				pi->data.kval=k-i;
			}
			pa->data.tag=true;
			pa->data.kval=k-(--i);
		}
		if(pa!=NULL)
		{
			occ.push_back(pa);
			return true;
		}
		else
			return false;
	}
	void Reclaim(int i)
	{
		list<DLNode<T>*>::iterator ip=occ.begin();
		advance(ip, i-1);
		DLNode<T> *s, *p;
		p=*ip;
		occ.erase(ip);
		s=buddy(p);
		while(s>=t && s<t+FreeList[m].size && !s->data.tag && 
		s->data.kval==p->data.kval)
		{
			FreeList[s->data.kval].first.ListDelete(s);
			if((p-t)%(int)pow(2, p->data.kval+1)==0)
				p->data.kval++;
			else
			{
				s->data.kval=p->data.kval+1;
				p=s;
			}
			s=buddy(p);
		}
		p->data.tag=false;
		FreeList[p->data.kval].first.ListInsert(1, p);
		
	}
	void Print()
	{
		int i;
		DLNode<T> *h;
		list<DLNode<T>*>::iterator ip;
		for(i=0; i<=m; i++)
			if(FreeList[i].first.Head!=NULL)
			{
				h=FreeList[i].first.Head;
				do
				{
					cout<<"空闲块的大小="<<(int)pow(2, h->data.kval)<<" 块的首地址="<<h;
					cout<<" 块标志="<<boolalpha<<h->data.tag<<endl;
					h=h->next;
				}while(h!=FreeList[i].first.Head);
			}
		for(i=1, ip=occ.begin(); ip!=occ.end(); ip++, i++)
		{
			cout<<"第"<<i<<"个占用块的首地址="<<*ip<<" 块的大小=";
			cout<<(int)pow(2, (*ip)->data.kval)<<" 块标志="<<(*ip)->data.tag<<endl;
		}
	}
};
void main()
{
	BuddySystem bs;
	int i, j, n;
	bool dis, flag=true;
	while(flag)
	{
		cout<<"请选择操作命令（1. 分配空间；2. 回收释放块；0. 退出）：";
		cin>>j;
		switch(j)
		{
		case 0: 
				flag=false;
				break;
		case 1: 
				cout<<"请输入待分配空间大小n（以DLNode<T>为单位）：";
				cin>>n;
				dis=bs.AllocBuddy(n);
				if(dis)
				{
					cout<<"申请分配"<<n<<"个空间后，存储空间状况为"<<endl;
					bs.Print();
				}
				break;
		case 2: 
				cout<<"请输入要回收的块i：";
				cin>>i;
				bs.Reclaim(i);
				cout<<"回收第"<<i<<"个占用块后，存储空间状况为"<<endl;
				bs.Print();
		}
	}
}

