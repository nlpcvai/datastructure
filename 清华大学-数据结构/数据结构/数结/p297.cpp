#include "P267E.cpp"
template <class NameType, class DistType> 		
void Graph<NameType,DistType>::CriticalPath ( ) {
		//�ڴ��㷨����Ҫ���ڽӱ��е�����Ľ������޸�, �ڸ����������һ��int��cost, ��¼�ý������ʾ�ı�
		//�ϵ�Ȩֵ��
		   int i;  int k;  int e, l; 		   
		   Edge<NameType,DistType> *p;
		   int* Ve = new int[NumVertices]; int* Vl = new int[NumVertices];					//�¼����硢��ٿ�ʼʱ��
		   for ( i=0; i<NumVertices; i++ ) Ve[i] = 0;					//Ve�����ʼ��
		   for ( i=0; i<NumVertices; i++ ) {							//˳������¼���������ʼʱ��Ve
			 p = NodeTable[i].adj;				//�ö����������ͷָ��p
			 while ( p != NULL ) {						//ɨ�������, �����к���ڽӶ���
			   k = p->dest;							// i�ĺ���ڽӶ���k
			   if ( Ve[i] + p->cost > Ve[k] ) Ve[k] = Ve[i] + p->cost; 
	 		   p = p->link;							//����һ�����
			 }
		   }
		   for ( i=0; i<NumVertices; i++ ) Vl[i] = Ve[NumVertices-1];					//��������¼�����ٿ�ʼʱ��Vl
		   for ( i=NumVertices-2; i; i-- ) {							//������������˳����
			 p = NodeTable[i].adj;						//�ö����������ͷָ��p
			 while ( p != NULL ) {
			   k = p->dest;							// i�ĺ���ڽӶ���k
			   if ( Vl[k] - p->cost < Vl[i]) Vl[i] = Vl[k] - p->cost;
			   p = p->link;							//����һ�����
			 }
		   };
		   for ( i=0; i<NumVertices; i++ ) {							//�������������e[k], l[k]
			 p = NodeTable[i].adj;						//�ö����������ͷָ��p
			 while ( p != NULL ) {
			   k = p->dest;							// k��i�ĺ���ڽӶ���
			   e = Ve[i];  l = Vl[k] - p->cost;
			   if ( l == e )							//�ؼ��
				 cout << "<" << i << "," << k << ">" << "is Critical Activity" << endl;
			   p = p->link;							//����һ�����
			 }
		   }
		}