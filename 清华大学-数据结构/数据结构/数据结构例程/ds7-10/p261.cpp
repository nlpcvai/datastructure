		class Graph {
		//对象: 由一个顶点的非空集合和一个边集合构成, 每条边由一个顶点对来表示。
		public:
		   Graph ( );
			//建立一个空的图。
		   void InsertVertex ( const Type & vertex );
			//在图中插入一个顶点vertex, 该顶点没有入边。
		   void InsertEdge ( const int v1, const int v2, int weight );
			//若构成边的两个顶点v1和v2是图中的顶点, 则在图中插入一条边(v1,v2)。
		   void RemoveVertex ( const int v );
			//若被删顶点是图中的顶点, 则删去顶点v和所有关联到它的边。
  		   void RemoveEdge ( const int v1, const int v2 );
			//若构成边的两个顶点v1和v2是图中的顶点, 则在图中删去边(v1,v2)。
		   int IsEmpty ( );
			//若图中没有顶点, 则函数返回1, 否则返回0。
		   Type GetWeight ( const int v1, const int v2 );
			//函数返回边 (v1,v2) 的权值。
		   int GetFirstNeighbor ( const int v );
			//给出顶点位置为v的第一个邻接顶点的位置, 如果找不到, 则函数返回-1。
		   int GetNextNeighbor ( const int v1, const int v2 );
			//给出顶点位置为v1的某邻接顶点v2的下一个邻接顶点的位置, 如果找不到, 则返回-1。
		}

