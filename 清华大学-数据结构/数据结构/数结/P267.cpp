#include "P265.cpp"
#include "iostream.h"
#include "assert.h"

const int MaxNumEdges=100;
template <class NameType, class DistType>
Graph <NameType, DistType>::
Graph ( const int sz=DefaultSize ) : NumVertices (0), MaxNumVertices (sz), NumEdges (0) {
   int n, e, k, j;
   NameType name, tail, head;
   DistType weight;
   NodeTable = new Vertex<NameType,DistType>[MaxNumVertices];			//�������������
   cin >> n;										//���붥�����   
   assert(n<=sz);   
   for ( int i=0; i<n; i++)
   {
     cin >> name;
     InsertVertex ( name );
   }		//�������붥��, ����ͼ��

   cin >> e;										//�������   
   assert(e<=MaxNumEdges);   
   for ( i=0; i<e; i++) {								//�����������Ϣ
	 cin >> tail >> head >> weight;						//�������
	 k = GetVertexPos ( tail );  j = GetVertexPos ( head );			//ȡ������λ��
	 InsertEdge ( k, j, weight );							//����ͼ��
   }
}

template <class NameType, class DistType> Graph<NameType, DistType>::~Graph ( ) {
   for ( int i=0; i<NumVertices; i++ ) {						//ɾ�����������еĽ��
	 Edge<NameType,DistType> *p = NodeTable[i].adj;
	 while ( p != NULL ) 							//ѭ��ɾ��
	   {	NodeTable[i].adj = p->link;  delete p;  p = NodeTable[i].adj; }
   }
   delete [ ] NodeTable;								//ɾ����������
}

template <class NameType, class DistType>
int Graph<NameType, DistType>::GetVertexPos
( const NameType & vertex )
{
   for ( int i=0; i< NumVertices; i++) {

	 if ( NodeTable[i].data == vertex ) return i;
   }

   return -1;
}

template <class NameType, class DistType> int Graph<NameType, DistType>::GetFirstNeighbor ( const int v ) {
//��������λ��Ϊv�ĵ�һ���ڽӶ����λ��, ����Ҳ���, ��������-1��
   if ( v != -1 ) {							//v����
	 Edge<NameType,DistType> *p = NodeTable[v].adj;				//�������һ������ַ
	 if ( p != NULL ) return p->dest;				//��, ���ظñ���һ������
   }
   return -1;								//û�б�
}

template <class NameType, class DistType>
int Graph<NameType, DistType>::GetNextNeighbor ( const int v1, const int v2 ) {
//��������v1��ĳ�ڽӶ���v2����һ���ڽӶ����λ��, ��û����һ���ڽӶ���, ��������-1��
   if ( v1 != -1 ) {									//v1����
	 Edge<NameType,DistType> *p = NodeTable[v1].adj;				//�������һ������ַ
	 while ( p != NULL ) {							//Ѱ�ҵ�v2���ڽӶ���
	   if ( p->dest == v2 && p->link != NULL ) return p->link->dest;
	   else p = p->link;
	 }
   }
   return -1;
}

template <class NameType, class DistType>
DistType Graph<NameType, DistType>::GetWeight ( const int v1, const int v2) {
//�������ر�(v1, v2)�ϵ�Ȩֵ, ���ñ߲���ͼ��, ��������Ȩֵ0��
   if ( v1 != -1 && v2 != -1 ) {
	 Edge<NameType,DistType> *p = NodeTable[v1].adj;				//������ͷָ��
	 while ( p != NULL ) {
	   if ( p->dest == v2 ) return p->cost;				//�ҵ��˱�, ����Ȩֵ
	   else p = p->link;							//��������һ����
	 }
   }
   return 0;										//�߲���ͼ��
}

