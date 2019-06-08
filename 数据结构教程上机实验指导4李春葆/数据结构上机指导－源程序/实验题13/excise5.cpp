#include <stdio.h>
#include <malloc.h>
#include <math.h>
typedef struct node
{
	long index;						//��ǰ�ڵ��Ӧ�ļ�¼�±�
	int level;						//��ǰ�ڵ�Ĳ��
	struct node *lchild,*rchild;	//���Һ���ָ��
} BTree;							//�ж����ڵ�����
void CreateBTree1(BTree *&b,long low,long high,int h) //��CreateBTree�����Խ����ж���
{
	int mid;
	if (low<=high)
	{
		mid=(low+high)/2;
		b=(BTree *)malloc(sizeof(BTree));
		b->index=mid;
		b->level=h; 
		CreateBTree1(b->lchild,low,mid-1,h+1);
		CreateBTree1(b->rchild,mid+1,high,h+1);
	}
	else
		b=NULL;
}
void CreateBTree(BTree *&b,long n)		//�����ж���
{
	CreateBTree1(b,0,n-1,1);
}
	
void DispBTree(BTree *b)	//�����ű�ʾ�����������
{
	if (b!=NULL)
	{
		printf("%d[%d]",b->index,b->level);
		if (b->lchild!=NULL || b->rchild!=NULL)
		{
			printf("(");
			DispBTree(b->lchild);
			if (b->rchild!=NULL) printf(",");
			DispBTree(b->rchild);
			printf(")");
		}
	}
}
void Release(BTree *&b)		//�ͷ��ж���
{
	if (b!=NULL)
	{
		Release(b->lchild);
		Release(b->rchild);
		free(b);
	}
}
int Sum(BTree *b)		//���ж����бȽϵ��ܴ���
{
	if (b!=NULL)
	{
		if (b->lchild==NULL && b->rchild==NULL)
			return b->level;
		else
			return Sum(b->lchild)+Sum(b->rchild)+b->level;
	}
	else
		return 0;
}
double Asl(BTree *b,long n)		//��ɹ�����µ�ƽ�����ҳ���
{
	return 1.0*Sum(b)/n;
}
void main()
{
	BTree *b;
	long n=11;
	double d,asl1,asl2;
	CreateBTree(b,n);
	printf("R[0..%d]�ж���:\n\t",n-1);
	DispBTree(b);
	printf("\n\tASL=%g\n",Asl(b,n));
	Release(b);
	printf("�ɹ�ƽ�����ҳ��ȷ���:\n");
	printf("\tn\t\tASL1\t\tASL2\t\t��ֵ\n");  
	for (n=10;n<=1000000;n*=10)
	{
		CreateBTree(b,n);
		asl1=Asl(b,n);
		asl2=log(n+1)-1;
		d=asl1-asl2;
		printf("  %10d\t\t%g\t\t%g\t\t%g\n",n,asl1,asl2,d);
		Release(b);
	}
}