//�ļ���:exp8-8.cpp
#include <stdio.h>
#include "graph.h"
#define MAXE 100		//������
typedef struct 
{	int u;				//�ߵ���ʼ����
    int v;				//�ߵ���ֹ����
    int w;				//�ߵ�Ȩֵ		
} Edge;
extern void DispMat1(MGraph);		//�ⲿ������algo8-1.cpp��
void SortEdge(MGraph g,Edge E[])	//���ڽӾ������Ȩֵ�����ı߼�
{
	int i,j,k=0;
	Edge temp;
	for (i=0;i<g.n;i++)
		for (j=0;j<g.n;j++)
			if (g.edges[i][j]<INF)
			{
				E[k].u=i;
				E[k].v=j;
				E[k].w=g.edges[i][j];
				k++;
			}
	for (i=1;i<k;i++)	//��Ȩֵ�����������ֱ�Ӳ������� 
	{
		temp=E[i];
		j=i-1;			//����������������E[0..i-1]����E[i]�Ĳ���λ��
		while (j>=0 && temp.w<E[j].w) 
		{ 	
			E[j+1]=E[j]; //��Ȩֵ����E[i].w�ļ�¼����
			j--;
		}
		E[j+1]=temp;      //��j+1������E[i]
	}
}
void Kruskal(Edge E[],int n,int e)
{
	int i,j,m1,m2,sn1,sn2,k;
	int vset[MAXE];
	for (i=0;i<n;i++) vset[i]=i;	//��ʼ����������
	k=1;                 			//k��ʾ��ǰ������С�������ĵڼ�����,��ֵΪ1
	j=0;                 			//E�бߵ��±�,��ֵΪ0
	while (k<n)       				//���ɵı���С��nʱѭ��
	{	
		m1=E[j].u;m2=E[j].v;        //ȡһ���ߵ�ͷβ����
		sn1=vset[m1];sn2=vset[m2]; 	//�ֱ�õ��������������ļ��ϱ��
		if (sn1!=sn2)     			//���������ڲ�ͬ�ļ���,�ñ�����С��������һ����
		{	
			printf("  (%d,%d):%d\n",m1,m2,E[j].w);
			k++;                    //���ɱ�����1
			for (i=0;i<n;i++)      	//��������ͳһ���
				if (vset[i]==sn2)  	//���ϱ��Ϊsn2�ĸ�Ϊsn1
				    vset[i]=sn1;
		}
		j++;   						//ɨ����һ����
	}
}
void main()
{
	int i,j,u=3;
	MGraph g;
	Edge E[MAXE];
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
	SortEdge(g,E);
	printf("ͼG���ڽӾ���:\n");
	DispMat1(g);
	printf("��³˹�����㷨�����:\n");
	Kruskal(E,g.n,g.e);
	printf("\n");
}
