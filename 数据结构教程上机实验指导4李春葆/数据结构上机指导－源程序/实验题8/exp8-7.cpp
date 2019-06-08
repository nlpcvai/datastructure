//�ļ���:exp8-7.cpp
#include <stdio.h>
#include "graph.h"
extern void DispMat1(MGraph);	//�ⲿ������algo8-1.cpp��

void Prim(MGraph g,int v)
{
	int lowcost[MAXV],min,n=g.n;
	int closest[MAXV],i,j,k;
	for (i=0;i<n;i++)          	//��lowcost[]��closest[]�ó�ֵ
	{	
		lowcost[i]=g.edges[v][i];
		closest[i]=v;
	}
	for (i=1;i<n;i++)          	//�ҳ�n-1������
	{   
		min=INF;
	    for (j=0;j<n;j++)       //��(V-U)���ҳ���U����Ķ���k
		   	if (lowcost[j]!=0 && lowcost[j]<min) 
			{	
				min=lowcost[j]; k=j;  
			}
		printf("  ��(%d,%d)ȨΪ:%d\n",closest[k],k,min);
		lowcost[k]=0;         	//���k�Ѿ�����U
		for (j=0;j<n;j++)   	//�޸�����lowcost��closest
           	if (g.edges[k][j]!=0 && g.edges[k][j]<lowcost[j]) 
			{	
				lowcost[j]=g.edges[k][j];closest[j]=k; 
			}
	}
}
void main()
{
	int i,j,u=3;
	MGraph g;
	int A[MAXV][MAXV]={{0,5,8,7,INF,3},
	{5,0,4,INF,INF,INF},
	{8,4,0,5,INF,9},
	{7,INF,5,0,5,INF},
	{INF,INF,INF,5,0,1},
	{3,INF,9,INF,1,0}};
	g.n=6;g.e=10;
	for (i=0;i<g.n;i++)		//����ͼ8.16���ڽӾ���
		for (j=0;j<g.n;j++)
			g.edges[i][j]=A[i][j];
	printf("ͼG���ڽӾ���:\n");
	DispMat1(g);
	printf("����ķ�㷨�����:\n");
	Prim(g,0);
	printf("\n");
}
