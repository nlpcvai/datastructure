#define NULL 0
class MinSpanTree;			//最小生成树的前视类声明
template <class NameType, class DistType> class Graph;				//图的前视类定义

template <class NameType,class DistType> class Edge {				//边的定义
public:
   friend class Graph<NameType,DistType>;	
   int dest;							//边的另一顶点位置, 第一个顶点位置是隐式的
   DistType cost;						//边上的权值
   Edge<NameType,DistType> *link;						//下一条边链指针
   Edge ( ) { }								//构造函数
   Edge ( int D, DistType C ) : dest (D), cost (C), link (NULL) { }	//构造函数
   int operator != ( const Edge &E ) const { return dest != E.dest; }
};

template <class NameType, class DistType> class Vertex {		//顶点的定义
public:
   friend class Graph<NameType,DistType>;	
   NameType data;							//顶点的名字
   Edge<NameType,DistType> *adj;							//出边表的头指针
};
const MaxNumVertices=10;
const DefaultSize = 20;
template <class NameType, class DistType> class Graph
{		//图的类定义
//friend class Vertex <NameType, DistType>;
//friend class Edge<DistType>;
protected:
   Vertex<NameType, DistType> *NodeTable;			//顶点表 (各边链表的头结点)
   int NumVertices;							//当前顶点个数
   int MaxNumVertices;							//最大顶点个数
   int NumEdges;								//当前边数
   int GetVertexPos ( const NameType & vertex );				//给出顶点vertex在图中的位置
public:
   Graph (const int sz=DefaultSize );								//构造函数
   ~Graph ( );								//析构函数
   int GraphEmpty ( ) const { return NumVertices == 0; }		//测试图空否
   int GraphFull ( ) const							//测试图满否
	  { return NumVertices == MaxNumVertices||NumEdges ==MaxNumEdges; }
   int NumberOfVertices ( ) { return NumVertices; }			//返回图的顶点数
   int NumberOfEdges ( ) { return NumEdges; }			//返回图的边数
   NameType GetValue ( const int i )					//取位置为i的顶点中的值
	  { return i >= 0 && i < NumVertices ? NodeTable[i].data : NULL; }
   void InsertVertex ( const NameType & vertex );			//在图中插入一个顶点
   void RemoveVertex ( const int v );					//在图中删除一个顶点
   void InsertEdge ( const int v1, const int v2, const DistType weight );		//在图中插入一条边
   void RemoveEdge ( const int v1, const int v2 );			//在图中删除一条边
   DistType GetWeight ( const int v1, const int v2 );			//返回边上的权值
   int GetFirstNeighbor ( const int v );				//取顶点v的第一个邻接顶点
   int GetNextNeighbor ( const int v1, const int v2 );		//取顶点v1的某邻接顶点v2的下一个邻接顶点
   void DFS ( );
   void DFS ( const int v, int visited [ ] );
   void BFS ( int v );
   void DfnLow ( const int x );
   void DfnLow ( const int u, const int v );
   void Components ( );
   void Biconnected ( );
   void Biconnected ( const int u, const int v );
   void Kruskal ( MinSpanTree &T );
   void CriticalPath();
};

