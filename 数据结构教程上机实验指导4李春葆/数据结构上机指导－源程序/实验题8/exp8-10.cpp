//�ļ���:exp8-10.cpp
#include <stdio.h>
#define	MAXV  100				//��󶥵����
#include "graph.h"
extern void DispMat1(MGraph g);	//�ⲿ������algo8-1.cpp��
void ppath(int path[][MAXV],int i,int j) 
{
	int k;
	k=path[i][j];
	if (k==-1)  return;
	ppath(path,i,k);
	printf("%d,",k);
	ppath(path,k,j);
}
void DisPath(int A[][MAXV],int path[][MAXV],int n)
{
	int i,j;
	for (i=0;i<n;i++)
		for (j=0;j<n;j++) 
			if (A[i][j]!=INF && i!=j)
			{	
				printf("  ��%d��%d·��Ϊ:",i,j);
				printf("%d,",i);ppath(path,i,j);printf("%d",j);
				printf("\t·������Ϊ:%d\n",A[i][j]);
			}
} 
void Floyd(MGraph g)	//���������㷨��ÿ�Զ���֮������·��
{
	int A[MAXV][MAXV],path[MAXV][MAXV];
	int i,j,k,n=g.n;
	for (i=0;i<n;i++)						//��A�����ó�ֵ
		for (j=0;j<n;j++) 
		{	
			A[i][j]=g.edges[i][j];
			path[i][j]=-1;
		}
	for (k=0;k<n;k++)						//����Ak
	{
	for (i=0;i<n;i++)
		for (j=0;j<n;j++)
			if (A[i][j]>(A[i][k]+A[k][j])) 
				{	A[i][j]=A[i][k]+A[k][j];
					path[i][j]=k;
				}
	}
	printf("\n������·��:\n");
	DisPath(A,path,n);			//������·��
}
void main()
{	int i,j,u=0;
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
	printf("\n");
	printf("����ͼG���ڽӾ���:\n");
	DispMat1(g);
	Floyd(g);
	printf("\n");
}
