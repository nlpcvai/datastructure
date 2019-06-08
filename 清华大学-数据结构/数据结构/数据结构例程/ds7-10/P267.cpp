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
   NodeTable = new Vertex<NameType,DistType>[MaxNumVertices];			//创建顶点表数组
   cin >> n;										//输入顶点个数   
   assert(n<=sz);   
   for ( int i=0; i<n; i++)
   {
     cin >> name;
     InsertVertex ( name );
   }		//依次输入顶点, 插入图中

   cin >> e;										//输入边数   
   assert(e<=MaxNumEdges);   
   for ( i=0; i<e; i++) {								//依次输入边信息
	 cin >> tail >> head >> weight;						//输入各边
	 k = GetVertexPos ( tail );  j = GetVertexPos ( head );			//取两顶点位置
	 InsertEdge ( k, j, weight );							//插入图中
   }
}

template <class NameType, class DistType> Graph<NameType, DistType>::~Graph ( ) {
   for ( int i=0; i<NumVertices; i++ ) {						//删除各边链表中的结点
	 Edge<NameType,DistType> *p = NodeTable[i].adj;
	 while ( p != NULL ) 							//循环删除
	   {	NodeTable[i].adj = p->link;  delete p;  p = NodeTable[i].adj; }
   }
   delete [ ] NodeTable;								//删除顶点数组
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
//给出顶点位置为v的第一个邻接顶点的位置, 如果找不到, 则函数返回-1。
   if ( v != -1 ) {							//v存在
	 Edge<NameType,DistType> *p = NodeTable[v].adj;				//边链表第一个结点地址
	 if ( p != NULL ) return p->dest;				//有, 返回该边另一个顶点
   }
   return -1;								//没有边
}

template <class NameType, class DistType>
int Graph<NameType, DistType>::GetNextNeighbor ( const int v1, const int v2 ) {
//给出顶点v1的某邻接顶点v2的下一个邻接顶点的位置, 若没有下一个邻接顶点, 则函数返回-1。
   if ( v1 != -1 ) {									//v1存在
	 Edge<NameType,DistType> *p = NodeTable[v1].adj;				//边链表第一个结点地址
	 while ( p != NULL ) {							//寻找第v2个邻接顶点
	   if ( p->dest == v2 && p->link != NULL ) return p->link->dest;
	   else p = p->link;
	 }
   }
   return -1;
}

template <class NameType, class DistType>
DistType Graph<NameType, DistType>::GetWeight ( const int v1, const int v2) {
//函数返回边(v1, v2)上的权值, 若该边不在图中, 则函数返回权值0。
   if ( v1 != -1 && v2 != -1 ) {
	 Edge<NameType,DistType> *p = NodeTable[v1].adj;				//边链表头指针
	 while ( p != NULL ) {
	   if ( p->dest == v2 ) return p->cost;				//找到此边, 返回权值
	   else p = p->link;							//否则找下一条边
	 }
   }
   return 0;										//边不在图中
}

