//Algo9-1.cpp 边界标识法类
#include "C.h"
#include "DLinkListNH.h"
#define FootLoc(p) p+p->data.size-1
//带参数的宏定义，指向p所指结点的底部域（最后一个结点）
const int e=10;
#define uplink prior
class BoundaryLogo
{
private:
	struct T
	{
		bool tag;
		int size;
	};
	DLNode<T> *t;
	int MAX;
	DLinkListNH<T> pav;
	list<DLNode<T>*> occ;
	void Distribute(DLNode<T>* p)
	{
		pav.ListDelete(p);
		p->data.tag=(FootLoc(p))->data.tag=true;
	}
	void DistributePart(DLNode<T>* p, int n)
	{
		DLNode<T> *f=FootLoc(p);
		f->data.tag=true;
		p->data.size-=n;
		f=FootLoc(p);
		f->data.tag=false;
		f->uplink=p;
		f=f+1;
		f->data.tag=true;
		f->data.size=n;
	}
	void InsertByAscend(DLNode<T>* p)
	{
		DLNode<T> *s=pav.Head;
		int i=1;
		while(i<=pav.ListLength() && s->data.size<p->data.size)
		{
			i++;
			s=s->next;
		}
		pav.ListInsert(i, p);
	}
	void AmendDomain(DLNode<T>* p)
	{
		p->data.tag=false;
		(FootLoc(p))->uplink=p;
		(FootLoc(p))->data.tag=false;
	}
	void MergeLeft(DLNode<T>* p, DLNode<T>* &s)
	{
		s=(p-1)->uplink;
		s->data.size+=p->data.size;
		DLNode<T> *f=FootLoc(p);
		f->uplink=s;
		f->data.tag=false;
	}
public:
	BoundaryLogo(int m)
	{
		MAX=m;
		DLNode<T> *p;
		t=new DLNode<T>[MAX+2];
		
		assert(t!=NULL);
		t->data.tag=true;
		
		p=t+1;
		p->data.tag=false;
		p->data.size=MAX;
		pav.ListInsert(1, p);
		p=FootLoc(p);
		p->uplink=pav.Head;
		p->data.tag=false;
		(p+1)->data.tag=true;
		cout<<"双循环链表结点DLNode<T>为"<<sizeof(DLNode<T>)<<"个字节"<<endl;
		Print();
	}
	~BoundaryLogo()
	{
		delete[]t;
		pav.Head=NULL;
	}
	bool AllocBoundTag(int i, int n)
	{
	 
		DLNode<T> *p;
		switch(i)
		{
		case 1: 
				for(p=pav.Head; p!=NULL&&p->data.size<n&&p->next!=pav.Head; p=p->next);
				
				if(p==NULL || p->data.size<n)
					p=NULL;
				else
				{
					pav.Head=p->next;
					if(p->data.size-n<e)
						Distribute(p);
					else
					{
						DistributePart(p, n);
						p=p+p->data.size;
					}
				}
				break;
		case 2: 
				for(p=pav.Head; p!=NULL&&p->data.size<n&&p->next!=pav.Head; p=p->next);
				
				if(p==NULL || p->data.size<n)
					p=NULL;
				else
				{
					if(p->data.size-n<e)
						Distribute(p);
					else
					{
						DistributePart(p, n);
						if(p->data.size<p->prior->data.size)
						{
							pav.ListDelete(p);
							InsertByAscend(p);
						}
						p=p+p->data.size;
					}
				}
				break;
		case 3: 
				if(pav.Head==NULL)
					p=NULL;
				else
					p=pav.Head->prior;
				if(p->data.size<n)
					p=NULL;
				else
				{
					if(p->data.size-n<e)
						Distribute(p);
					else
					{
						DistributePart(p, n);
						if(p->data.size<p->prior->data.size)
						{
							pav.ListDelete(p);
							InsertByAscend(p);
						}
						p=p+p->data.size;
					}
				}
				break;
		default:p=NULL;
		}
		if(p!=NULL)
		{
			occ.push_back(p);
			return true;
		}
		else
			return false;
	}
	void Reclaim(int i, int k)
	{
	 
		list<DLNode<T>*>::iterator ip=occ.begin();
		advance(ip, k-1);
		DLNode<T> *p, *s, *f;
		p=*ip;
		occ.erase(ip);
		f=p+p->data.size;
		bool lft=(p-1)->data.tag, r=(p+p->data.size)->data.tag;
		
		switch(i)
		{
		case 1: 
				if(lft && r)
				{
					pav.ListInsert(1, p);
					AmendDomain(p);
				}
				else if(!lft && r)
					MergeLeft(p, s);
					
				else if(lft && !r)
				{
					p->data.tag=false;
					p->prior=f->prior;
					p->prior->next=p;
					p->next=f->next;
					p->next->prior=p;
					p->data.size+=f->data.size;
					(FootLoc(f))->uplink=p;
					if(pav.Head==f)
						pav.Head=p;
				}
				else
				{
					pav.ListDelete(f);
					s=(p-1)->uplink;
					s->data.size+=p->data.size+f->data.size;
					(FootLoc(f))->uplink=s;
				}
				break;
		case 2: 
		case 3: 
				if(lft && r)
				{
					InsertByAscend(p);
					AmendDomain(p);
				}
				else if(!lft && r)
				{
					MergeLeft(p, s);
					
					if(s->data.size>s->next->data.size)
					{
						pav.ListDelete(s);
						InsertByAscend(s);
					}
				}
				else if(lft && !r)
				{
					pav.ListDelete(f);
					p->data.tag=false;
					p->data.size+=f->data.size;
					(FootLoc(f))->uplink=p;
					InsertByAscend(p);
				}
				else
				{
					pav.ListDelete(f);
					s=(p-1)->uplink;
					s->data.size+=p->data.size+f->data.size;
					(FootLoc(f))->uplink=s;
					if(s->data.size>s->next->data.size)
					{
						pav.ListDelete(s);
						InsertByAscend(s);
					}
				}
		}
	}
	void Print()
	{
		DLNode<T> *h, *f;
		list<DLNode<T>*>::iterator ip;
		int i;
		if(pav.Head!=NULL)
		{
			h=pav.Head;
			f=FootLoc(h);
			do
			{
				cout<<"空闲块的大小="<<h->data.size<<" 块的首地址="<<f->uplink
				<<" 块标志="<<boolalpha<<h->data.tag<<" 邻块首地址="<<f+1<<endl;
				h=h->next;
				f=FootLoc(h);
			}while(h!=pav.Head);
		}
		for(i=1, ip=occ.begin(); ip!=occ.end(); ip++, i++)
		{
			cout<<"第"<<i<<"个占用块的首地址="<<*ip<<" 块的大小=";
			cout<<(*ip)->data.size<<" 块标志="<<(*ip)->data.tag<<endl;
		}
	}
};
void main()
{
	BoundaryLogo bl(100);
	int n, i, j, k;
	bool dis, flag=true;
	cout<<"请选择分配策略（1. 首次拟合法；2. 最佳拟合法；3. 最差拟合法）：";
	cin>>i;
	while(flag)
	{
		cout<<"请选择操作命令（1. 分配空间；2. 回收释放块；0. 退出）：";
		cin>>j;
		switch(j)
		{
		case 0: flag=false;
				break;
		case 1: cout<<"请输入待分配空间大小n（以DLNode<T>为单位）：";
				cin>>n;
				dis=bl.AllocBoundTag(i, n);
				if(dis)
				{
					cout<<"分配"<<n<<"个空间后，存储空间状况为"<<endl;
					bl.Print();
				}
				else
					cout<<"分配失败"<<endl;
				break;
		case 2: cout<<"请输入要回收的块k：";
				cin>>k;
				bl.Reclaim(i,k);
				cout<<"回收第"<<k<<"个占用块后，存储空间状况为"<<endl;
				bl.Print();
		}
	}
}

