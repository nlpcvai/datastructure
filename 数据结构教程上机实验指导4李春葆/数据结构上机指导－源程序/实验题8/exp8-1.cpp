//�ļ���:exp8-1.cpp
#include <stdio.h>
#include <malloc.h>
#include "graph.h"
extern void MatToList1(MGraph,ALGraph *&);	//�����ⲿ������algo8-1.cpp��
extern void ListToMat1(ALGraph *,MGraph &);
extern void DispMat1(MGraph);
extern void DispAdj1(ALGraph *);
void main()
{
	int i,j;
	MGraph g,g1;
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
	printf("����ͼG���ڽӾ���:\n");
	DispMat1(g);
	G=(ALGraph *)malloc(sizeof(ALGraph));
	printf("ͼG���ڽӾ���ת�����ڽӱ�:\n");
	MatToList1(g,G);
	DispAdj1(G);
	printf("ͼG���ڽӱ�ת�����ڽ�����:\n");
	ListToMat1(G,g1);
	DispMat1(g1);
}