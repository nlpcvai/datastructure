#define NULL 0
class MinSpanTree;			//��С��������ǰ��������
template <class NameType, class DistType> class Graph;				//ͼ��ǰ���ඨ��

template <class NameType,class DistType> class Edge {				//�ߵĶ���
public:
   friend class Graph<NameType,DistType>;	
   int dest;							//�ߵ���һ����λ��, ��һ������λ������ʽ��
   DistType cost;						//���ϵ�Ȩֵ
   Edge<NameType,DistType> *link;						//��һ������ָ��
   Edge ( ) { }								//���캯��
   Edge ( int D, DistType C ) : dest (D), cost (C), link (NULL) { }	//���캯��
   int operator != ( const Edge &E ) const { return dest != E.dest; }
};

template <class NameType, class DistType> class Vertex {		//����Ķ���
public:
   friend class Graph<NameType,DistType>;	
   NameType data;							//���������
   Edge<NameType,DistType> *adj;							//���߱��ͷָ��
};
const MaxNumVertices=10;
const DefaultSize = 20;
template <class NameType, class DistType> class Graph
{		//ͼ���ඨ��
//friend class Vertex <NameType, DistType>;
//friend class Edge<DistType>;
protected:
   Vertex<NameType, DistType> *NodeTable;			//����� (���������ͷ���)
   int NumVertices;							//��ǰ�������
   int MaxNumVertices;							//��󶥵����
   int NumEdges;								//��ǰ����
   int GetVertexPos ( const NameType & vertex );				//��������vertex��ͼ�е�λ��
public:
   Graph (const int sz=DefaultSize );								//���캯��
   ~Graph ( );								//��������
   int GraphEmpty ( ) const { return NumVertices == 0; }		//����ͼ�շ�
   int GraphFull ( ) const							//����ͼ����
	  { return NumVertices == MaxNumVertices||NumEdges ==MaxNumEdges; }
   int NumberOfVertices ( ) { return NumVertices; }			//����ͼ�Ķ�����
   int NumberOfEdges ( ) { return NumEdges; }			//����ͼ�ı���
   NameType GetValue ( const int i )					//ȡλ��Ϊi�Ķ����е�ֵ
	  { return i >= 0 && i < NumVertices ? NodeTable[i].data : NULL; }
   void InsertVertex ( const NameType & vertex );			//��ͼ�в���һ������
   void RemoveVertex ( const int v );					//��ͼ��ɾ��һ������
   void InsertEdge ( const int v1, const int v2, const DistType weight );		//��ͼ�в���һ����
   void RemoveEdge ( const int v1, const int v2 );			//��ͼ��ɾ��һ����
   DistType GetWeight ( const int v1, const int v2 );			//���ر��ϵ�Ȩֵ
   int GetFirstNeighbor ( const int v );				//ȡ����v�ĵ�һ���ڽӶ���
   int GetNextNeighbor ( const int v1, const int v2 );		//ȡ����v1��ĳ�ڽӶ���v2����һ���ڽӶ���
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

