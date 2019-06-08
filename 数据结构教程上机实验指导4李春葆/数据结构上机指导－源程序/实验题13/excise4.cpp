//�ļ���:excise44.cpp
#include <stdio.h>
#include <malloc.h>
#include "graph.h"
int visited[MAXV],path[MAXV];		//ȫ������
int V1[MAXV],V2[MAXV],n,m; 
int count=0;
bool Cond(int path[],int d)			//�ж�����
{
	int flag1=0,f1,flag2=0,f2,i,j;
	for (i=0;i<n;i++)		//�ж�·�����Ƿ��бؾ���
	{
		f1=1;
		for (j=0;j<=d;j++)
			if (path[j]==V1[i])
			{
				f1=0;break;
			}
		flag1+=f1;
	}

	for (i=0;i<m;i++)		//�ж�·�����Ƿ��бرܵ�
	{
		f2=0;
		for (j=0;j<=d;j++)
			if (path[j]==V2[i])
			{
				f2=1;break;
			}
		flag2+=f2;
	}
	if (flag1==0 && flag2==0)	//������������true
		return true;
	else						//��������������false
		return false;
}
void TravPath(ALGraph *G,int vi,int vj,int d)
{
	int v,i;
	ArcNode *p;
	visited[vi]=1;
	d++;
	path[d]=vi;
	if (vi==vj && Cond(path,d))
	{
		printf("  ·��%d: ",++count);
		for (i=0;i<d;i++)
			printf("%d->",path[i]);
		printf("%d\n",path[i]);
	}
    p=G->adjlist[vi].firstarc;      //��vi�ĵ�һ���ڽӶ���
	while (p!=NULL)
	{
		v=p->adjvex;                //vΪvi���ڽӶ���
		if (visited[v]==0)          //���ö���δ��Ƿ���,��ݹ����֮
			TravPath(G,v,vj,d);
		p=p->nextarc;               //��vi����һ���ڽӶ���
	}
	visited[vi]=0;                  //ȡ�����ʱ��,��ʹ�ö��������ʹ��
	d--;
}
void MatToList(MGraph g,ALGraph *&G)
//���ڽӾ���gת�����ڽӱ�G
{
	int i,j;
	ArcNode *p;
	G=(ALGraph *)malloc(sizeof(ALGraph));
	for (i=0;i<g.n;i++)					//���ڽӱ�������ͷ�ڵ��ָ�����ó�ֵ
		G->adjlist[i].firstarc=NULL;
	for (i=0;i<g.n;i++)					//����ڽӾ�����ÿ��Ԫ��
		for (j=g.n-1;j>=0;j--)
			if (g.edges[i][j]!=0)		//�ڽӾ���ĵ�ǰԪ�ز�Ϊ0
			{   
			   	p=(ArcNode *)malloc(sizeof(ArcNode));	//����һ���ڵ�*p
				p->adjvex=j;
				p->nextarc=G->adjlist[i].firstarc;		//��*p���������
				G->adjlist[i].firstarc=p;
			}
	G->n=g.n;G->e=g.e;
}
void DispAdj(ALGraph *G)	//����ڽӱ�G
{
	int i;
	ArcNode *p;
	for (i=0;i<G->n;i++)
	{
		p=G->adjlist[i].firstarc;
		printf("%3d: ",i);
		while (p!=NULL)
		{
			printf("%3d",p->adjvex);
			p=p->nextarc;
		}
		printf("\n");
	}
}
void main()
{ 
	int i,j,u,v;
	MGraph g;
	ALGraph *G;
	int A[MAXV][15]={
		{0,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,1,0,1,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,1,0,0,0,0,0},
		{0,1,0,1,0,0,0,1,0,1,0,0,0,0,0},
		{0,0,0,0,1,0,1,0,0,0,1,1,0,0,0},
		{0,1,0,0,0,1,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,1,1,0,0,0,1,0,1,0,0},
		{0,0,0,0,0,0,0,1,0,1,0,0,0,1,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,1,0},
		{0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,1,1,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0}};
	g.n=15;g.e=21;
	for (i=0;i<g.n;i++)	
		for (j=0;j<g.n;j++)
			g.edges[i][j]=A[i][j];
	G=(ALGraph *)malloc(sizeof(ALGraph));
	MatToList(g,G);
	printf("ͼG���ڽӱ�:\n");
	DispAdj(G);
	for (i=0;i<g.n;i++) 
		visited[i]=0;
	printf("���������յ�:");
	scanf("%d%d",&u,&v);
	printf("����ؾ������:");
	scanf("%d",&n);
	printf("����ؾ��㼯��:");
	for (i=0;i<n;i++)
		scanf("%d",&V1[i]);
	printf("����رܵ����:");
	scanf("%d",&m);
	printf("����رܵ㼯��:");
	for (i=0;i<m;i++)
		scanf("%d",&V2[i]);
	printf("\n���е�̽��·������:\n");
    TravPath(G,u,v,-1);
}