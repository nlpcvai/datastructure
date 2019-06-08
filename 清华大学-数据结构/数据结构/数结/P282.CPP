#include "p263.cpp"

template <class NameType,class DistType>
void Graph<NameType, DistType>::Prim ( MinSpanTree &T ) {
   int NumVertices = VerticesList.Length();				//图中顶点数
   if (NumVertices<=0) return;
   int *lowcost,*nearvex;
   lowcost = new int[NumVertices];				//创建辅助数组
   nearvex = new int[NumVertices];				//创建辅助数组TV
   for ( int i=1; i<NumVertices; i++ ) {
	 if (Edge[0][i]==0) lowcost[i]=MAXINT; else lowcost[i] = Edge[0][i];  
	 nearvex[i] = 0;		//顶点0到各边的代价及最短带权路径
   }
   nearvex[0] = -1;							//顶点0加到生成树顶点集合, 用-1表示
   
   for ( i=1; i<NumVertices; i++ ) {				//循环-1次, 加入n-1条边
	 int min = MAXINT;  int v = 0;				//求生成树外顶点到生成树内顶点具有最小权值的边
	 for ( int j=0; j<NumVertices; j++ )			//确定当前具最小权值的边及顶点位置
	   if ( nearvex[j] != -1 && lowcost[j] < min ) { v = j;  min = lowcost[j]; }
	 if ( v ) 
	 {									// v==0表示再也找不到要求的顶点了
	   T.addEdge(nearvex[v],v,lowcost[v]);	   
	   nearvex[v] = -1;						//加入生成树顶点集合
	   for ( j=1; j<NumVertices; j++ )
		 if ( (nearvex[j] != -1) && (Edge[v][j]!=0) && (Edge[v][j] < lowcost[j]) )
		   { lowcost[j] = Edge[v][j];  nearvex[j] = v; }		//修改
	 }
   }   
}
