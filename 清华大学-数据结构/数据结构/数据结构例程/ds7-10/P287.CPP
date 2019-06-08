#include "p284.cpp"
void Graph::BellmanFord ( const int v ) {
//在带权有向图中有的边具有负的权值。从顶点v找到所有其它顶点的最短路径。
   for ( int i=0; i<n; i++ ) {
	 dist[i] = Edge[v][i];								//对dist初始化
	 if ( i != v && dist[i] < MAXINT ) path[i] = v;			//对dist初始化
	 else path[i] = -1;
   }
   dist[v]=0;
   for ( int k=2; k<n; k++ )
	 for ( int u=0; u<n; u++ )
	   if ( u != v )
		 for ( i=0; i<n; i++ )
		   if ( path[i] >=0 && Edge[i][u] < MAXINT && dist[u] > dist[i]+Edge[i][u] ) {
			   dist[u] = dist[i] + Edge[i][u];  path[u] = i;		//绕i的路径长度小，修改
		   }
}
