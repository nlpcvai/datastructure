//�ļ���:exp8-5.cpp
#include <stdio.h>
#include <malloc.h>
#include "graph.h"
extern void MatToList(MGraph,ALGraph *&);	//�����ⲿ������algo8-1.cpp��
extern void DispAdj(ALGraph *);
int visited[MAXV];							//ȫ������
void PathAll1(ALGraph *G,int u,int v,int path[],int i)
//���ͼG�дӶ���u��v�����м�·��
{
	ArcNode *p;
	int j,n;
	visited[u]=1;
	p=G->adjlist[u].firstarc;  			//pָ�򶥵�m�ĵ�һ����
	while (p!=NULL)
	{
		n=p->adjvex;					//nΪm���ڽӶ���
		if (n==v)
		{
			path[i+1]=v;
			for (j=0;j<=i+1;j++)
				printf("%3d",path[j]);
			printf("\n");
		}
		else if (visited[n]==0 ) 		//���ö���δ��Ƿ���,��ݹ����֮
		{
			path[i+1]=n;
			PathAll1(G,n,v,path,i+1);
		}
		p=p->nextarc;					//��u����һ���ڽӶ���
	}
	visited[u]=0;
}
void PathAll2(ALGraph *G,int u,int v,int l,int path[],int d)
//���ͼG�дӶ���u��v�ĳ���Ϊl�����м�·��,d�ǵ���ǰΪֹ���߹���·������,����ʱ��ֵΪ-1
{
	int m,i;
	ArcNode *p;
	visited[u]=1;
	d++;							//·��������1
	path[d]=u;						//����ǰ������ӵ�·����
	if (u==v && d==l)				//���һ��·��
	{
		for (i=0;i<=d;i++)
			printf("%3d",path[i]);
		printf("\n");
	}
	p=G->adjlist[u].firstarc;  		//pָ�򶥵�u�ĵ�һ����
	while (p!=NULL)
	{
		m=p->adjvex;				//mΪu���ڽӶ���
		if (visited[m]==0)			//���ö���δ��Ƿ���,��ݹ����֮
			PathAll2(G,m,v,l,path,d);
		p=p->nextarc;				//��u����һ���ڽӶ���
	}
	visited[u]=0;					//ȡ�����ʱ��,��ʹ�ö��������ʹ��
}
int ShortPath(ALGraph *G,int u,int v,int path[])
//�󶥵�u������v(u��v)�����·��
{
	struct 
	{
		int vno;						//��ǰ������
		int level;						//��ǰ����Ĳ��
		int parent;						//��ǰ����ĵ�һ���ڵ���
	} qu[MAXV];							//����˳���ѭ������
	int front=-1,rear=-1,k,lev,i,j;
	ArcNode *p;
	visited[u]=1;
	rear++;								//����u�ѷ���,�������
	qu[rear].vno=u;
	qu[rear].level=0;
	qu[rear].parent=-1;
	while (front<rear)					//�ӷǿ���ִ��
	{
		front++;
		k=qu[front].vno;				//����
		lev=qu[front].level;
		if (k==v) 
		{
			i=0;
			j=front;
			while (j!=-1)
			{
				path[lev-i]=qu[j].vno;	//�����·������path��
				j=qu[j].parent;
				i++;
			}
			return lev;					//�ҵ�����v,����
		}
		p=G->adjlist[k].firstarc;		//ȡk�ı߱�ͷָ��           
		while (p!=NULL)                 //���������ɵ��ڽӵ�
		{
			if (visited[p->adjvex]==0)  //��δ���ʹ�
			{
				visited[p->adjvex]=1;
				rear++;
				qu[rear].vno=p->adjvex;	//���ʹ����ڽӵ����
				qu[rear].level=lev+1;
				qu[rear].parent=front;
			}
			p=p->nextarc;				//�Ҷ���i����һ�ڽӵ�
		}
	}
	return -1;     //���δ�ҵ�����j,����һ����ֵ-1
}
void main()
{ 
	int i,j;
	int u=5,v=2,d=3;
	int path[MAXV];
	MGraph g;
	ALGraph *G;
	int A[MAXV][6]={
		{0,1,0,1,0,0},
		{0,0,1,0,0,0},
		{1,0,0,0,0,1},
		{0,0,1,0,0,1},
		{0,0,0,1,0,0},
		{1,1,0,1,1,0}};
	g.n=6;g.e=10;
	for (i=0;i<g.n;i++)		//����ͼ9.10���ڽӾ���
		for (j=0;j<g.n;j++)
			g.edges[i][j]=A[i][j];
	G=(ALGraph *)malloc(sizeof(ALGraph));
	MatToList(g,G);					//ͼG���ڽӾ���ת�����ڽӱ�
	printf("ͼG���ڽӱ�:\n");
	DispAdj(G);
	for (i=0;i<g.n;i++) 
		visited[i]=0;
	printf("�Ӷ���%d��%d������·��:\n",u,v);
	path[0]=u;visited[u]=1;
	PathAll1(G,u,v,path,0);
	printf("�Ӷ���%d��%d�����г���Ϊ%d·��:\n",u,v,d);
	PathAll2(G,u,v,d,path,-1);printf("\n");
	for (i=0;i<g.n;i++) 
		visited[i]=0;
	printf("�Ӷ���%d��%d�����·��:\n",u,v);
	for (i=0;i<g.n;i++) 
		visited[i]=0;
	j=ShortPath(G,u,v,path);
	for (i=0;i<=j;i++)
		printf("%3d",path[i]);
	printf("\n");
}