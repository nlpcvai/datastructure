#include "iostream.h"
#include "queue.h"
#include "p267E.cpp"
		template <class NameType, class DistType> 
		void Graph<NameType, DistType>::BFS (  int v ) {
		//�Ӷ���v����, �Թ�����ȵĴ����������ͼ, �㷨��ʹ����һ�����С�
		   int *visited = new int[NumVertices];                  		//visited��¼�����Ƿ���ʹ�
		   for ( int i=0; i<NumVertices; i++ ) visited[i] = 0;			//��ʼ��
		   cout << GetValue (v) << ' ';	
		   visited[v] = 1;			//���ȷ��ʶ���v, ���ѷ��ʱ��
		   Queue<int> q;								//q��ʵ�ֲַ���ʵĶ���
		   q.EnQueue (v);								//����v������
		   while ( !q.IsEmpty ( ) ) {
			 v = q.DeQueue ( );							//�Ӷ������˳�����v
			 int w = GetFirstNeighbor (v);					//�Ҷ���v�ĵ�һ���ڽӶ���
			 while ( w != -1 ) {							//w��v���ڽӶ���
			   if ( !visited[w] ) {						//��δ���ʹ�
				 cout << GetValue (w) << ' ';  visited[w] = 1;		//���ʶ���w
				 q.EnQueue (w);						//����w������
			   }
			   w = GetNextNeighbor (v, w);					//�Ҷ���v����һ���ڽӶ���
			 }
		   }
		   delete [ ] visited;
		}
