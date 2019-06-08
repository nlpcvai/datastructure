#include "p292.cpp"
#include "iostream.h"
template <class NameType, class DistType> 
void  AOVGraph<NameType,DistType>::TopologicalSort ( ) 
{
		//对n个顶点的AOV网进行拓扑排序。top是入度为零顶点栈的栈顶指针。
		   int top = -1;
		   for ( int i=0; i<NumVertices; i++ )						//建立入度为零顶点的链栈
		   {
			 if ( count[i] == 0 ) 
				{ count[i] = top;  top = i;	};		//进栈运算
		   }
		   for ( i=0; i<NumVertices; i++ )
			 if ( top == -1 )
				{ cout << "Network has a cycle" << endl;	
				return; }
			 else
			 {
			    int j = top;  top = count[top];				//一个入度为零的顶点出栈
			    cout << j << endl;						//输出顶点j
			    Edge<NameType,DistType> * l = NodeTable[j].adj;				//顶点j的边链表的链头指针
			    while ( l )
				{							// l ( 0, 有出边
				  int k = l->dest;						//取该边的终点k, 该顶点的入度减1
					  if ( --count[k] == 0 ) {
					  count[k] = top;  top = k; }	//入度减至0的顶点进入度为零的顶点栈
				  l = l->link;						// 取j的下一条出边
			    }
			 }
}

