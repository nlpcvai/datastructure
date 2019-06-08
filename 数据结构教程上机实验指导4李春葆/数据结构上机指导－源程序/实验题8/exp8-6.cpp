//�ļ���:exp8-6.cpp
#include <stdio.h>
#include <malloc.h>
#include "graph.h"
extern void MatToList(MGraph,ALGraph *&);	//�����ⲿ������algo8-1.cpp��
extern void DispAdj(ALGraph *);
int visited[MAXV];							//ȫ������
void DFS(ALGraph *G,int v) 
{
	ArcNode *p;
	visited[v]=1;                   		//���ѷ��ʱ��
	p=G->adjlist[v].firstarc;      			//pָ�򶥵�v�ĵ�һ����
	while (p!=NULL) 
	{	
		if (visited[p->adjvex]==0)			//��p->adjvex����δ����,�ݹ������
		{
			printf("<%d,%d> ",v,p->adjvex);	//�����������һ����
			DFS(G,p->adjvex);    
		}
		p=p->nextarc;              			//pָ�򶥵�v����һ����
	}
}
void BFS(ALGraph *G,int v)  
{
	ArcNode *p;
	int queue[MAXV],front=0,rear=0;			//����ѭ�����в���ʼ��
	int w,i;
	for (i=0;i<G->n;i++) 
		visited[i]=0;						//���ʱ�־�����ʼ��
	visited[v]=1;              				//���ѷ��ʱ��
	rear=(rear+1)%MAXV;
	queue[rear]=v;             				//v����
	while (front!=rear)       				//�����в���ʱѭ��
	{	
		front=(front+1)%MAXV;
		w=queue[front];       				//���Ӳ�����w
		p=G->adjlist[w].firstarc; 			//���붥��w�ڽӵĵ�һ������
		while (p!=NULL) 
		{	
			if (visited[p->adjvex]==0) 		//����ǰ�ڽӶ���δ������
			{	
				printf("<%d,%d> ",w,p->adjvex);	//�����������һ����
				visited[p->adjvex]=1;		//�øö����ѱ����ʵı�־
				rear=(rear+1)%MAXV;			//�ö������
				queue[rear]=p->adjvex; 		
           	}
           	p=p->nextarc;              		//����һ���ڽӶ���
		}
	}
	printf("\n");
}
void main()
{ 
	int i,j;
	MGraph g;
	ALGraph *G;
	int A[MAXV][11]={{0,1,1,1,0,0,0,0,0,0,0},
	{1,0,0,0,1,1,0,0,0,0,0},
	{1,0,0,1,0,1,1,0,0,0,0},
	{1,0,1,0,0,0,0,1,0,0,0},
	{0,1,0,0,0,0,0,0,0,0,0},
	{0,1,1,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,1,1,1,0},
	{0,0,0,1,0,0,1,0,0,0,1},
	{0,0,0,0,0,0,1,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0}};
	g.n=11;g.e=13;					//����ͼ8.13���ڽӾ���
	for (i=0;i<g.n;i++)	
		for (j=0;j<g.n;j++)
			g.edges[i][j]=A[i][j];
	G=(ALGraph *)malloc(sizeof(ALGraph));
	MatToList(g,G);
	printf("ͼG���ڽӱ�:\n");
	DispAdj(G);
	printf("\n");
	for (i=0;i<g.n;i++) 
		visited[i]=0;
	printf("�������������:");
	DFS(G,3);printf("\n");
	for (i=0;i<g.n;i++) 
		visited[i]=0;
	printf("�������������:");
	BFS(G,3);printf("\n");
}
