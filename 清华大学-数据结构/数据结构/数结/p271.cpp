#include "iostream.h"
#include "p267E.cpp"
		template <class NameType, class DistType> 
		void Graph< NameType, DistType>::DFS ( ) {						//����ͨͼ�����������������������
		   int *visited = new int [NumVertices];					//������������
		   for ( int i=0; i<NumVertices; i++ ) visited [i] = 0;			//���������ʼ��
		   for (  i=0; i<NumVertices; i++) 
			   if (!visited[i])  DFS (i ,visited);								//�Ӷ���0��ʼ�����������
		   delete [ ] visited;
		   
		};
		template <class NameType, class DistType>
		void Graph< NameType, DistType>::DFS ( const int v, int visited [ ] ) {		//�ӹ���
		//�Ӷ���λ��v����, ��������ȵĴ���������пɶ������δ���ʹ��Ķ��㡣�㷨���õ�һ����������
		// visited, ���ѷ��ʹ��Ķ��������ʱ�ǡ�
		   cout << GetValue (v) << ' ';					//���ʸö��������
		   visited[v] = 1;							//���ʱ�־��Ϊ�ѷ��ʹ�
		   int w = GetFirstNeighbor (v);					//�Ҷ���v�ĵ�һ���ڽӶ���w
		   while ( w != -1 ) {						//���ڽӶ���
			 if ( !visited[w] ) DFS ( w, visited );			//��δ���ʹ�, ��w�ݹ����
			 w = GetNextNeighbor ( v, w );				//�Ҷ���v����һ���ڽӶ���
		   }
		}
