#include "P267E.cpp"
template <class NameType, class DistType> 		
void Graph<NameType,DistType>::CriticalPath ( ) {
		//在此算法中需要对邻接表中单链表的结点加以修改, 在各结点中增加一个int域cost, 记录该结点所表示的边
		//上的权值。
		   int i;  int k;  int e, l; 		   
		   Edge<NameType,DistType> *p;
		   int* Ve = new int[NumVertices]; int* Vl = new int[NumVertices];					//事件最早、最迟开始时间
		   for ( i=0; i<NumVertices; i++ ) Ve[i] = 0;					//Ve数组初始化
		   for ( i=0; i<NumVertices; i++ ) {							//顺向计算事件最早允许开始时间Ve
			 p = NodeTable[i].adj;				//该顶点边链表链头指针p
			 while ( p != NULL ) {						//扫描边链表, 找所有后继邻接顶点
			   k = p->dest;							// i的后继邻接顶点k
			   if ( Ve[i] + p->cost > Ve[k] ) Ve[k] = Ve[i] + p->cost; 
	 		   p = p->link;							//找下一个后继
			 }
		   }
		   for ( i=0; i<NumVertices; i++ ) Vl[i] = Ve[NumVertices-1];					//逆向计算事件的最迟开始时间Vl
		   for ( i=NumVertices-2; i; i-- ) {							//按逆拓扑有序顺序处理
			 p = NodeTable[i].adj;						//该顶点边链表链头指针p
			 while ( p != NULL ) {
			   k = p->dest;							// i的后继邻接顶点k
			   if ( Vl[k] - p->cost < Vl[i]) Vl[i] = Vl[k] - p->cost;
			   p = p->link;							//找下一个后继
			 }
		   };
		   for ( i=0; i<NumVertices; i++ ) {							//逐个顶点求各活动的e[k], l[k]
			 p = NodeTable[i].adj;						//该顶点边链表链头指针p
			 while ( p != NULL ) {
			   k = p->dest;							// k是i的后继邻接顶点
			   e = Ve[i];  l = Vl[k] - p->cost;
			   if ( l == e )							//关键活动
				 cout << "<" << i << "," << k << ">" << "is Critical Activity" << endl;
			   p = p->link;							//找下一个后继
			 }
		   }
		}