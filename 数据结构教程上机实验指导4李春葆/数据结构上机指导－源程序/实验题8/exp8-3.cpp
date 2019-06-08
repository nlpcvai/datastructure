//�ļ���:exp8-3.cpp
#include <stdio.h>
#include <malloc.h>
#include "graph.h"
extern void MatToList(MGraph,ALGraph *&);	//�����ⲿ������algo8-1.cpp��
extern void DispAdj(ALGraph *);
int visited[MAXV];
void DFSALL(ALGraph *G,int v,int path[],int d)  
{
	ArcNode *p;
	visited[v]=1;                   //���ѷ��ʱ��
	path[d]=v;
	d++;
	if (d==G->n)					//����ѷ������ж��㣬�������������
	{
		for (int k=0;k<d;k++)
			printf("%2d",path[k]);
		printf("\n");
	}
	p=G->adjlist[v].firstarc;      	//pָ�򶥵�v�ĵ�һ�����Ļ�ͷ���
	while (p!=NULL) 
	{
		if (visited[p->adjvex]==0)	//��p->adjvex����δ����,�ݹ������
			DFSALL(G,p->adjvex,path,d);    
		p=p->nextarc;              	//pָ�򶥵�v����һ�����Ļ�ͷ���
	}
	visited[v]=0;
}
void DFS(ALGraph *G,int v)
{	ArcNode *p;
	visited[v]=1;						//���ѷ��ʱ��
	printf("%d  ",v);					//��������ʶ���ı��
	p=G->adjlist[v].firstarc;			//pָ�򶥵�v�ĵ�һ���߽ڵ�
	while (p!=NULL)
	{	if (visited[p->adjvex]==0)		//��p->adjvex����δ����,�ݹ������
			DFS(G,p->adjvex);
		p=p->nextarc;					//pָ�򶥵�v����һ���߽ڵ�
	}
	visited[v]=0;
}
void main()
{
	int path[MAXV],i,j,v=1;
	MGraph g;
	ALGraph *G;
	g.n=5;g.e=8;
	int A[MAXV][MAXV]={
		{0,1,0,1,1},
		{1,0,1,1,0},
		{0,1,0,1,1},
		{1,1,1,0,1},
		{1,0,1,1,0}};	
	for (i=0;i<g.n;i++)				//�������̡̳���ͼ8.1(a)���ڽӾ���
		for (j=0;j<g.n;j++)
			g.edges[i][j]=A[i][j];
	MatToList(g,G);
	for (i=0;i<g.n;i++) 			//visited�����ó�ֵ
		visited[i]=0;
	printf("ͼG���ڽӱ�:\n");DispAdj(G);	//����ڽӱ�
	printf("�Ӷ���%d���������������������:\n",v);
	DFSALL(G,v,path,0);
	printf("\n");
}
