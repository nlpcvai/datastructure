//�ļ���:exp8-2.cpp
#include <stdio.h>
#include <malloc.h>
#include "graph.h"
extern void MatToList1(MGraph,ALGraph *&);	//�����ⲿ������algo8-1.cpp��
extern void DispAdj1(ALGraph *G);
extern void DFS(ALGraph *G,int v);			//�����ⲿ������algo8-2.cpp��
extern void DFS1(ALGraph *G,int v);
extern void DFS2(ALGraph *G,int v);
extern void BFS(ALGraph *G,int v);
void main()
{
	int i,j;
	MGraph g;
	ALGraph *G;
	int A[MAXV][6]={
		{0,5,INF,7,INF,INF},
		{INF,0,4,INF,INF,INF},
		{8,INF,0,INF,INF,9},
		{INF,INF,5,0,INF,6},
		{INF,INF,INF,5,0,INF},
		{3,INF,INF,INF,1,0}};
	g.n=6;g.e=10;			//����ͼ8.1���������ͼG���ڽӾ���
	for (i=0;i<g.n;i++)	
		for (j=0;j<g.n;j++)
			g.edges[i][j]=A[i][j];
	G=(ALGraph *)malloc(sizeof(ALGraph));
	MatToList1(g,G);					//ͼG���ڽӾ���ת�����ڽӱ�
	printf("ͼG���ڽӱ�:\n");
	DispAdj1(G);
	printf("�Ӷ���0��ʼ��DFS(�ݹ��㷨):\n");
	DFS(G,0);printf("\n");
	printf("�Ӷ���0��ʼ��DFS(�ǵݹ��㷨):\n");
	DFS1(G,0);
	printf("�Ӷ���0��ʼ��BFS(�ǵݹ��㷨):\n");
	BFS(G,0);printf("\n");
}
