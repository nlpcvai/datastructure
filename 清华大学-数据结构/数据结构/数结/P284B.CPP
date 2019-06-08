#include "iostream.h"
#include "assert.h"
   const int NumVertices = 6;				//图中最大顶点个数
   const int MAXINT=32767;
   class Graph {						//图的类定义
   private:
      int n;
      int Edge[NumVertices][NumVertices];		//图的邻接矩阵
      int dist[NumVertices][NumVertices];		//图的邻接矩阵
      int path[NumVertices][NumVertices];		//图的邻接矩阵
   public:
      void AllLengths ( );
      int choose ( const int );
      void BestPath(ostream& os);
      friend istream& operator >>(istream& strm, Graph & g);
   };

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
	   os<<"shortest dist:"<<endl;
	   for (int i=0;i<n;i++)
	   {
	     for (int j=0;j<n;j++)
	       os<<dist[i][j]<<" ";
	     os<<endl;
	   }
	   os<<endl;
	   os<<"shortest path:"<<endl;
	   for ( i=0;i<n;i++)
	   {
	     for ( int j=0;j<n;j++)
	       os<<path[i][j]<<" ";
	     os<<endl;
	   }
	   os<<endl;
   }