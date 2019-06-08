#include "iostream.h"
#include "p267E.cpp"
		template <class NameType, class DistType> 
		void Graph< NameType, DistType>::DFS ( ) {						//对连通图进行深度优先搜索的主过程
		   int *visited = new int [NumVertices];					//创建辅助数组
		   for ( int i=0; i<NumVertices; i++ ) visited [i] = 0;			//辅助数组初始化
		   for (  i=0; i<NumVertices; i++) 
			   if (!visited[i])  DFS (i ,visited);								//从顶点0开始深度优先搜索
		   delete [ ] visited;
		   
		};
		template <class NameType, class DistType>
		void Graph< NameType, DistType>::DFS ( const int v, int visited [ ] ) {		//子过程
		//从顶点位置v出发, 以深度优先的次序访问所有可读入的尚未访问过的顶点。算法中用到一个辅助数组
		// visited, 对已访问过的顶点作访问标记。
		   cout << GetValue (v) << ' ';					//访问该顶点的数据
		   visited[v] = 1;							//访问标志改为已访问过
		   int w = GetFirstNeighbor (v);					//找顶点v的第一个邻接顶点w
		   while ( w != -1 ) {						//有邻接顶点
			 if ( !visited[w] ) DFS ( w, visited );			//若未访问过, 从w递归访问
			 w = GetNextNeighbor ( v, w );				//找顶点v的下一个邻接顶点
		   }
		}
