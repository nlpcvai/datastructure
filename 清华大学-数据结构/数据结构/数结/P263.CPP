#include "p278.cpp"
#include "IOSTREAM.H"
#include "p43&47.cpp"



const int MaxNumEdges = 50;							//最大边数
#ifndef SetMaxVertices
#define SetMaxVertices
const int MaxNumVertices=10;							//最大顶点数
#endif						
template <class NameType, class DistType> class Graph {			//图的类定义
private:
   SeqList<NameType> VerticesList;//( MaxNumVertices );			//顶点表
   DistType Edge[MaxNumVertices][MaxNumVertices];			//邻接矩阵
   int CurrentEdges;								//当前边数
   int FindVertex ( SeqList<NameType> & L, const NameType & vertex )
     { return L.Find (vertex); }     //在顶点表L中搜索顶点vertex
   int GetVertexPos ( const NameType & vertex )
     { return FindVertex (VerticesList, vertex ); }
     //给出顶点vertex在图中的位置
public:
   Graph ( const int sz=MaxNumEdges );					//构造函数
   int GraphEmpty ( ) const { return VerticesList.IsEmpty ( ); }		//判图空否
   int GraphFull ( ) const { return VerticesList.IsFull ( ) || CurrentEdges ==MaxNumEdges; }
   int NumberOfVertices ( ) { return VerticesList.Length(); }			//返回当前顶点数
   int NumberOfEdges ( ) { return CurrentEdges; }				//返回当前边数
   NameType GetValue ( const int i )						//取顶点i的值, i不合理则返回空
      { return VerticesList.Get(i); }
   DistType GetWeight ( const int v1, const int v2 );		//给出以顶点v1和v2为两端点的边上的权值
   int GetFirstNeighbor ( const int v );				//给出顶点位置为v的第一个邻接顶点的位置
   int GetNextNeighbor ( const int v1, const int v2 );		//给出顶点位置v1的某邻接顶点v2的下一个邻接顶点
   void InsertVertex (  NameType & vertex );		//插入一个顶点vertex, 该顶点没有入边
   void InsertEdge ( const int v1, const int v2, DistType weight );	//插入一条边(v1, v2), 该边上的权值为weight
   void RemoveVertex ( const int v );				//在图中删去顶点vertex和所有与它相关联的边
   void RemoveEdge ( const int v1, const int v2 );		//在图中删去边(v1,v2)
   void Prim ( MinSpanTree &T ) ;
   friend istream& operator >>(istream& , Graph&);
};

template <class NameType, class DistType> Graph<NameType, DistType>::Graph ( const int sz ) {
//构造函数
   for ( int i=0; i<sz; i++ )					//邻接矩阵初始化
	 for ( int j=0; j<sz; j++ ) Edge[i][j] = 0;
   CurrentEdges = 0;						//图中当前边数初始化
};

template <class NameType, class DistType>
DistType Graph<NameType, DistType>::GetWeight ( const int v1, const int v2 ) 
{
//给出以顶点v1和v2为两端点的边上的权值
   if ( v1 != -1 && v2 != -1 ) return Edge[v1][v2];
   else return NULL;							//带权图中权值为0, 表示无权值
};


template <class NameType, class DistType> 
int Graph<NameType, DistType>::GetFirstNeighbor ( const int v ) {
//给出顶点位置为v的第一个邻接顶点的位置, 如果找不到, 则函数返回-1。
   if ( v != -1 ) {
	 for ( int col=0; col<VerticesList.Length(); col++ ) if ( Edge[v][col] > 0 ) return col;
   }
   return -1;
};

template <class NameType, class DistType>
int Graph<NameType, DistType>::GetNextNeighbor ( const int v1, const int v2 ) {
//给出顶点v1的某邻接顶点v2的下一个邻接顶点
   if ( v1 != -1 && v2 != -1 )
   {
     for ( int col=v2+1; col<VerticesList.Length(); col++ )
       if ( Edge[v1][col] > 0 ) return col;
   }
   return -1;
};

template <class NameType, class DistType>
void Graph<NameType, DistType>::InsertVertex (  NameType & vertex )		//插入一个顶点vertex, 该顶点没有入边
{
	assert (VerticesList.Insert ( vertex, VerticesList.Length() ));		
};

template <class NameType, class DistType>
void Graph<NameType, DistType>:: InsertEdge ( const int v1, const int v2, DistType weight )	//插入一条边(v1, v2), 该边上的权值为weight
{
	CurrentEdges++;
	Edge[v1][v2]=weight;
};
template <class NameType, class DistType>
istream& operator >>(istream& is, Graph<NameType,DistType>& g)
{
   int n,e,k,j;
   NameType head,tail,name;
   DistType weight;
   is >> n;										//输入顶点个数
   for ( int i=0; i<n; i++)
   {
     is >> name;
     g.InsertVertex ( name );
   }		//依次输入顶点, 插入图中

   is >> e;										//输入边数

   for ( i=0; i<e; i++) {								//依次输入边信息
	 is >> tail >> head >> weight;						//输入各边
	 k = g.GetVertexPos ( tail );  j = g.GetVertexPos ( head );			//取两顶点位置
	 g.InsertEdge ( k, j, weight );							//插入图中
   }
   return is;

}