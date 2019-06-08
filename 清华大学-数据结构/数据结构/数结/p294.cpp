#include "p292.cpp"
#include "iostream.h"
template <class NameType, class DistType> 
void  AOVGraph<NameType,DistType>::TopologicalSort ( ) 
{
		//��n�������AOV��������������top�����Ϊ�㶥��ջ��ջ��ָ�롣
		   int top = -1;
		   for ( int i=0; i<NumVertices; i++ )						//�������Ϊ�㶥�����ջ
		   {
			 if ( count[i] == 0 ) 
				{ count[i] = top;  top = i;	};		//��ջ����
		   }
		   for ( i=0; i<NumVertices; i++ )
			 if ( top == -1 )
				{ cout << "Network has a cycle" << endl;	
				return; }
			 else
			 {
			    int j = top;  top = count[top];				//һ�����Ϊ��Ķ����ջ
			    cout << j << endl;						//�������j
			    Edge<NameType,DistType> * l = NodeTable[j].adj;				//����j�ı��������ͷָ��
			    while ( l )
				{							// l ( 0, �г���
				  int k = l->dest;						//ȡ�ñߵ��յ�k, �ö������ȼ�1
					  if ( --count[k] == 0 ) {
					  count[k] = top;  top = k; }	//��ȼ���0�Ķ�������Ϊ��Ķ���ջ
				  l = l->link;						// ȡj����һ������
			    }
			 }
}

