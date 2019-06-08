		//Test is T74_75.cpp

		#include <stdio.h>
		#include <iostream.h>

		class List;							//List���ǰ������

		class ListNode {						//����ඨ��
		friend class List;
		friend ostream & operator << ( ostream&, List & );						//����List��Ϊ��Ԫ��
		public:
		   //ListNode() { data = 0; link = NULL; );
		   ListNode( int x, ListNode * p ) { data = x; link = p; }
		private:
		   int data;							//����Ԫ����
		   ListNode *link;						//��ָ����
		};

		class List {							//List�ඨ��
		friend ostream & operator << ( ostream&, List & );						//����List��Ϊ��Ԫ��
		public:
		   List(): first( NULL ) {};
		   //����������
		   //������
		   int Insert ( const int x, const int i );
		   int Remove ( int i );
		private:
		   ListNode *first, *last;					//ָ�������ͷ��ָ��
		};

		#include <iostream.h>

		int List::Insert ( const int x, const int i ) {
		//����Ԫ��x���뵽��i���֮ǰ��i�ǽ��ţ���0��ʼ��
		   ListNode *p = first;  int k = 0;
		   while ( p != NULL && k< i-1 ) { p = p->link;  k++; }		//ѭ���ҵ�i-1�����
		   if ( p == NULL && first != NULL ) {				//�ǿձ�������̣��Ҳ�����i-1�����
			 cout << "Invalid position for Insertation!\n";  return 0;	//��ֹ����, ��������0
		   }
		   ListNode *newnode= new ListNode( x, NULL );				//����һ��newnodeָʾ���½��, ����Ϊx
		   if ( first == NULL || i == 0 ) {					//����ձ��ǿձ��һ�����֮ǰ
			  newnode->link = first;						//�½���Ϊ��һ�����
			  if ( first == NULL ) last = newnode;				//ԭΪ�ձ�ʱ����βָ��ָ������½��
			  first = newnode;
		   }
		   else {									//������������м��β��
			  newnode->link = p->link;
			  if ( p->link == NULL ) last = newnode;
			  p->link = newnode;
		}
		   return 1;									//�������룬��������1
		}

		int List::Remove ( int i ) {
		//�������еĵ�i��Ԫ��ɾȥ, ͨ���������ظ�Ԫ�ء���i������, �򷵻�NULL��
		   if ( i < 0 ) { cout << "Invalid position for Deletion!\n";  return 0;}	//����ɾ��, ��������0
		   ListNode *p = first, *q;  int k = 0;
		   while ( p != NULL && k< i-1 ) { p = p->link; k++; }		//ѭ���ҵ�i-1�����
		   if ( p == NULL || p->link == NULL ) {							//�ձ�������̣��Ҳ�����i-1�����
			  cout << "Invalid position for Deletion!\n";  return 0;	//����ɾ��, ��������0
		   }
		   if ( i == 0 ) {	q = first;  p = first = first->link; } 		//ɾ��һ�����ʱ����������
		   else { q = p->link;  p->link = q->link; }			//ɾ�м�һ������β���ʱ
		   if ( q == last ) last = p;						//ɾ��β���ʱ, ��βָ���޸�
		   k = q->data;  delete q;  return k;					//ȡ����ɾ����е�����ֵ
		}

		ostream & operator << ( ostream& os , List & onelist) {
		    ListNode * p = onelist.first;
		    if ( p == NULL ) os << "It is empty";
		    else while ( p != NULL ) {
			     os << p->data << " " ;
			     p = p->link;
			 }
		    return os;
		}