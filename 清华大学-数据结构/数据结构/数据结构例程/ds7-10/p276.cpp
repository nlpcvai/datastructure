#include "stack.h"
#include "P267E.cpp"


struct BiEdge
{
		BiEdge(){a=b=0;};
		BiEdge(int p1, int p2):a(p1),b(p2){};
		void SetVertex(int p1, int p2){a=p1;b=p2;};
		int operator==(BiEdge e)
		{
		  return ((a==e.a)&&(b==e.b)) || ((a==e.b)&&(b==e.a));
		};
		int a,b;
};
ostream& operator <<(ostream& strm, BiEdge& e)
{
  strm<<"("<<e.a<<","<<e.b<<")";
  return strm;
};

static int * dfn,*low;

//static int dfn[MaxNumVertices];
//static int low[MaxNumVertices];


static int num;


static  Stack< BiEdge >   S(MaxNumEdges);
static int min2(const int a, const int b)
{
	return a>b?b:a;
};



template <class NameType, class DistType> 
void Graph<NameType,DistType>::DfnLow ( const int x ) {				//�Ӷ���x��ʼ�����������
		   num = 1;							// num�Ƿ��ʼ�����, ��һ����������
		   dfn = new int[NumVertices];					// dfn�����������, ��һ����������
		   low = new int[NumVertices];					// low����С���ȷ���˳���, ��һ����������
		   for ( int i=0; i<NumVertices; i++ ) { dfn[i] = low[i] = 0; }
		   DfnLow ( x, -1 );
		   delete [ ] dfn;  delete [ ] low;
		}

template <class NameType, class DistType> 
void Graph<NameType,DistType>::DfnLow ( const int u, const int v ) {
		//�Ӷ���u��ʼ���������������dfn��low���ڲ�������������v��u��˫�ס�
		   dfn[u] = low[u] = num++;					//������ʼ�����num��dfn[u], low[u]��ֵ
		   int w = GetFirstNeighbor (u);
		   while ( w != -1 ) {						//�Զ���u�������ڽӶ���wѭ��
			 if ( dfn[w] == 0 ) {					//δ���ʹ�, w��u�ĺ���
			   DfnLow ( w, u );					//�ݹ������������
			   low[u] = min2 ( low[u], low[w] );			//low[ ]��ֵ���������, �������Ů����������
			 }
			 else if ( w != v )						//��ȥ(u, v)������, (u, w)���ǻر�
				  low[u] = min2 ( low[u], dfn[w] );		//ȡ�����е�С��
			 w = GetNextNeighbor (v, w);				//�Ҷ���v����һ���ڽӶ���
		   }
		}
template <class NameType, class DistType> 
void Graph<NameType,DistType>::Biconnected ( ) {
		   num = 1;								//���ʼ�����num��һ����������
		   dfn = new int[NumVertices];						// dfn�����������, ��һ����������
		   low = new int[NumVertices];						// low����С����˳���, ����������
		   for ( int i=0; i<NumVertices; i++ ) { dfn[i] = low[i] = 0; }
//		   DfnLow ( 0, -1 );							//�Ӷ���0��ʼ
		   Biconnected(0,-1);
		   delete [ ] dfn;  delete [ ] low;
		}

template <class NameType, class DistType> 
void Graph<NameType,DistType>::Biconnected ( const int u, const int v ) {
		//����dfn��low, ������������ͨ�������G�ıߡ��ڲ�������������, v��u�ĸ����, S��һ����ʼΪ�յ�
		//ջ, ��������Ϊͼ�����ݳ�Ա��
		   int w;
		   BiEdge e;
		   dfn[u] = low[u] = num++;		   
		   w = GetFirstNeighbor (u);						//�Ҷ���u�ĵ�һ���ڽӶ���;
		   while ( w != - 1 ) {							//w��v���ڽӶ���
			 if ( v != w && dfn[w] < dfn[u] ) S.Push ( BiEdge(u,w) );
			 if ( dfn[w] == 0 ) {						//δ���ʹ�, w�ǵĺ���
			   Biconnected (w, u);						//�ݹ�������ȷ���
			   low[u] = min2 ( low[u], low[w] );
			   if ( low[w] >= dfn[u] ) {					//�޻ر�, ԭ��������ͨ��������
				 cout << "New Biconnected Component: " << endl;
				 do {
				   e = S.Pop ( );					//���������ͨ�����ĸ��� 
	 			   cout << GetValue(e.a) <<"-"<<GetValue(e.b)<< endl;
				 } while ( !(e==BiEdge(u,w)));
			   }
			 }
			 else if ( w != v ) low[u] = min2 ( low[u], low[w] );		//�лر�, ����
			 w = GetNextNeighbor (u, w);					//�Ҷ���v����һ���ڽӶ���
		   }
		}