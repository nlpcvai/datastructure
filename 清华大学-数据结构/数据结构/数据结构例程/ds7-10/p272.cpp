#include "iostream.h"
#include "queue.h"
#include "p267E.cpp"
		template <class NameType, class DistType> 
		void Graph<NameType, DistType>::BFS (  int v ) {
		//从顶点v出发, 以广度优先的次序横向搜索图, 算法中使用了一个队列。
		   int *visited = new int[NumVertices];                  		//visited记录顶点是否访问过
		   for ( int i=0; i<NumVertices; i++ ) visited[i] = 0;			//初始化
		   cout << GetValue (v) << ' ';	
		   visited[v] = 1;			//首先访问顶点v, 做已访问标记
		   Queue<int> q;								//q是实现分层访问的队列
		   q.EnQueue (v);								//顶点v进队列
		   while ( !q.IsEmpty ( ) ) {
			 v = q.DeQueue ( );							//从队列中退出顶点v
			 int w = GetFirstNeighbor (v);					//找顶点v的第一个邻接顶点
			 while ( w != -1 ) {							//w是v的邻接顶点
			   if ( !visited[w] ) {						//若未访问过
				 cout << GetValue (w) << ' ';  visited[w] = 1;		//访问顶点w
				 q.EnQueue (w);						//顶点w进队列
			   }
			   w = GetNextNeighbor (v, w);					//找顶点v的下一个邻接顶点
			 }
		   }
		   delete [ ] visited;
		}
