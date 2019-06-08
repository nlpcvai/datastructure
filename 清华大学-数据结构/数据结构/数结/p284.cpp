#include "iostream.h"
#include "assert.h"
   const int NumVertices = 6;				//图中最大顶点个数
   const int MAXINT=32767;
   class Graph {						//图的类定义
   private:
      int n;
      int Edge[NumVertices][NumVertices];		//图的邻接矩阵
      int dist[NumVertices];					//存放从顶点0到其它各顶点的最短路径长度
      int path[NumVertices];					//存放在最短路径上该顶点的前一顶点的顶点号
      int S[NumVertices];					    //已求得的在最短路径上的顶点的顶点号
   public:
      void ShortestPath ( const int );
      int choose ( const int );
      void BestPath(ostream& os);
      void BellmanFord ( const int v );
      friend istream& operator >>(istream& strm, Graph & g);
   };

   void Graph::ShortestPath ( const int v ) {
   //G是一个具有n个顶点的带权有向图, 各边上的权值由Edge[i][j]给出。本算法建立起一个数组: dist[j], 0 < j < n,
   //是当前求到的从顶点v到顶点j的最短路径长度, 同时用数组path[j],	0 < j < n, 存放求到的最短路径。
      assert(((v<n) &&(v>=0)));
      for ( int i=0; i<n; i++) {				// dist和path数组初始化
	    dist[i] = Edge[v][i];					//邻接矩阵第v行元素复制到dist中
	    S[i] = 0;						//已求出最短路径的顶点集合初始化
	    if ( i != v && dist[i] < MAXINT ) path[i] = v;
	    else path[i] = -1;					//路径存放数组初始化
      }
      S[v] = 1;  dist[v] = 0;					//顶点v加入顶点集合
      for ( i=0; i<n-1; i++ ) {				//从顶点v确定n-1条路径
	    int min = MAXINT;
	    int u = v;
	    for ( int j=0; j<n; j++ )				//选择当前不在集合S中具有最短路径的顶点u
	      if ( !S[j] && dist[j] < min ) { u = j;  min = dist[j]; }
	    S[u] = 1;						//将顶点u加入集合S, 表示它已在最短路径上
	    for ( int w=0; w<n; w++ )			//修改
	      if ( !S[w] && Edge[u][w] < MAXINT && dist[u] + Edge[u][w] < dist[w] ) {
		    dist[w] = dist[u] + Edge[u][w];  path[w] = u;
	      }
      }
   }
   istream& operator >>(istream& strm, Graph & g)
   {
	strm>>g.n;
	    for (int i=0;i<g.n;i++)
	    {
		    for (int j=0;j<g.n;j++)
		    {
			    strm>> (g.Edge[i][j]);
		    }

	    }
	    return strm;

   }
   void Graph::BestPath(ostream& os)
   {
	   os<<"shortest dist:";
	   for (int i=0;i<n;i++)
	   {
	      os<<dist[i]<<" ";
	   }
	   os<<endl;
	   os<<"shortest path:";
	   for ( i=0;i<n;i++)
	   {
	      os<<path[i]<<" ";
	   }
	   os<<endl;
   }