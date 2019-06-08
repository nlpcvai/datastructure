//�ļ���:exp8-9.cpp
#include <stdio.h>
#include "graph.h"
#define	MAXV  100				//��󶥵����
extern void DispMat1(MGraph g);	//�ⲿ������algo8-1.cpp��
void ppath(int path[],int i,int v) 
{
	int k;
	k=path[i];
	if (k==v)  return;
	ppath(path,k,v);
	printf("%d,",k);
}
void DisPath(int dist[],int path[],int s[],int n,int v) //��path�������·��
{
	int i;
	printf("  path:");		//���pathֵ
	for (i=0;i<n;i++)
		printf("%3d",path[i]);
	printf("\n");
	for (i=0;i<n;i++)
		if (s[i]==1)
		{
			if (i!=v) 
			{	
				printf("  ��%d��%d�����·������Ϊ:%d\t·��Ϊ:",v,i,dist[i]);
				printf("%d,",v);ppath(path,i,v);printf("%d\n",i);
			}
		}
		else  
			printf("  ��%d��%d������·��\n",v,i);
}
void Dijkstra(MGraph g,int v)	//�ҿ�˹�����㷨�Ӷ���v���������������·��
{
	int dist[MAXV],path[MAXV];
	int s[MAXV];
	int mindis,i,j,u,n=g.n;
	for (i=0;i<n;i++) 
	{	
		dist[i]=g.edges[v][i];   		//�����ʼ��
		s[i]=0;                			//s[]�ÿ�
		if (g.edges[v][i]<INF)			//·����ʼ��
			path[i]=v;
		else
		    path[i]=-1;
	}
	s[v]=1;path[v]=0;        			//Դ����v����s��
	for (i=0;i<n;i++)     				//ѭ��ֱ�����ж�������·�������
	{	
		mindis=INF;
		u=-1;
		for (j=0;j<n;j++)     			//ѡȡ����s���Ҿ�����С����Ķ���u
			if (s[j]==0 && dist[j]<mindis) 
			{ 	
				u=j;mindis=dist[j];	
			}
		s[u]=1;               			//����u����s��
		for (j=0;j<n;j++)      			//�޸Ĳ���s�еĶ���ľ���
			if (s[j]==0) 
				if (g.edges[u][j]<INF && dist[u]+g.edges[u][j]<dist[j]) 
				{	
					dist[j]=dist[u]+g.edges[u][j];
					path[j]=u;
				}  
	}
	printf("������·��:\n");
	DisPath(dist,path,s,n,v);  		//������·��
}
void main()
{
	int i,j,u=0;
	MGraph g;
	int A[MAXV][6]={
		{0,5,INF,7,INF,INF},
		{INF,0,4,INF,INF,INF},
		{8,INF,0,INF,INF,9},
		{INF,INF,5,0,INF,6},
		{INF,INF,INF,5,0,INF},
		{3,INF,INF,INF,1,0}};
	g.n=6;g.e=10;
	for (i=0;i<g.n;i++)		//����ͼ8.1���ڽӾ���
		for (j=0;j<g.n;j++)
			g.edges[i][j]=A[i][j];
	printf("����ͼG���ڽӾ���:\n");
	DispMat1(g);
	Dijkstra(g,u);
	printf("\n");
}
