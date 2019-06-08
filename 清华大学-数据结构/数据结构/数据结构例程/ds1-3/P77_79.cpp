		#include <stdio.h>
		#include <iostream.h>

		template <class Type> class List;					//ǰ�ӵ��ඨ��

		template <class Type> class ListNode {					//��������Ķ���
		friend class List<Type>;							//List����Ϊ��Ԫ�ඨ��
		public:
		   ListNode ( );								//�������ݵĹ��캯��
		   ListNode ( const Type& item );					//�����ݵĹ��캯��
		   ListNode ( const Type& item, ListNode<Type>* next );
		   ListNode<Type> *NextNode ( ) { return link; }			//������ǰ������һ������ַ
		   void InsertAfter ( ListNode<Type> *p );				//��ǰ������
		   ListNode<Type> *GetNode ( const Type& item, ListNode<Type> *next );	//����һ���½��
		   ListNode<Type> *RemoveAfter ( );					//ɾ����ǰ������һ���
		private:
		   Type data;								//������
		   ListNode<Type> *link;						//��ָ����
		};

		template <class Type> class List {					//�������ඨ��
		public:
		   List ( ) { last =first = new ListNode<Type> ( ); }	//���캯��, ����һ��������
		   ~List ( );									//��������
		   void MakeEmpty ( );							//��������Ϊ�ձ�
		   int Length ( ) const;							//��������ĳ���
		   ListNode<Type> *GetNode ( const Type& item, ListNode<Type> *next );	//����һ���½��
		   ListNode<Type> *FindValue ( Type value );				//������������������value�Ľ��
		   ListNode<Type> *FindPosition ( int i );					//���������е�i��Ԫ�صĵ�ַ
		   int Insert ( Type value, int i );					//����Ԫ��value�����������е�i��λ��
		   Type *Remove ( int i );						//�������еĵ�i��Ԫ��ɾȥ
		   Type *Get ( int i );							//ȡ�������е�i��Ԫ��
		   void Print();
		private:
		   ListNode<Type> *first, *last;					//����ı�ͷָ��, ��βָ��
		};

		template <class Type> void ListNode<Type>::ListNode ( ) : link (NULL) { }
		//���캯��, ����ʼ��ָ���Ա��

		template <class Type> void ListNode<Type>::ListNode ( const Type& item ) : data (item), link (NULL) { }
		//���캯��, ��ʼ��������ָ���Ա��

		template <class Type> void ListNode<Type>::ListNode ( const Type& item, ListNode<Type>* next ) : data (item), link (next) { }

		template <class Type> void ListNode<Type>::InsertAfter ( ListNode<Type> *p ) {
		//��p��ָʾ�Ľ�����ӳ�Ϊ��ǰ���(*this)�ĺ�̽�㡣
			 p->link = link;  link = p;
		}

		template <class Type> ListNode<Type>* List<Type>::GetNode ( const Type& item,
		ListNode<Type> * next ){
		//�����ݳ�Աitem��ָ��nextΪ����, ����һ���½��, ���������½���ַ��
		   ListNode<Type> *newnode = new ListNode<Type> ( item, next );
		   return newnode;
		}

		template <class Type> ListNode<Type> *ListNode<Type>::RemoveAfter ( ) {
		//������ժ�µ�ǰ������һ���, ��Ϊɾ�������������ַ��
		   ListNode<Type> *tempptr = link;					//����Ҫ��ɾ�����ĵ�ַ
		   if ( link == NULL ) return NULL;					//��ǰ����޺��, ����NULL
		   link = tempptr->link;							//����ɾ��������ժ��
		   return tempptr;
		}

		template <class Type> List<Type>::~List ( ) { MakeEmpty ( );  delete first;  first = last = NULL; }
		//��������

		template <class Type> void List<Type>::MakeEmpty ( ) {
		//��������Ϊ�ձ�
		   ListNode<Type> *q;
		   while ( first->link != NULL ) {					//��������ʱ, ɾȥ�������н��
			 q = first->link;  first->link = q->link;
			 delete q;								//ѭ�����ɾ��������һ����ͷ���
		   }
		   last = first;								//��βָ��ָ���ͷ���
		}

		template <class Type> int List<Type>::Length ( ) const {
		//�������ͷ���ĵ�����ĳ���
		   ListNode<Type> *p = first->link;  int count = 0;
		   while ( p != NULL ) { p = p->link;  count++; }			//ѭ��ɨ��, Ѱ����β
		   return count;
		}

		template <class Type> ListNode<Type> *List <Type>::FindValue ( Type value ) {
		//�ڵ�����������������value�Ľ��, �����ɹ�ʱ, �������ظý���ַ; ���򷵻�NULLֵ��
		   ListNode<Type> *p = first->link;
		   while ( p != NULL && p->data != value )  p = p->link;	//ѭ���Һ�k���
		   return p;
		}

		template <class Type> ListNode<Type> *List<Type>::FindPosition ( int i ) {
		//��λ�������������������е�i��Ԫ�صĵ�ַ����i<-1��i�������н��������򷵻�NULL��
		   if ( i < -1 ) return NULL;						// iֵ������
		   if ( i == -1 ) return first;						// i = -1ʱ�������ر�ͷ����ַ
		   ListNode<Type> *p = first->link;  int j = 0;			//���ָ��pָ����е�һ�����
		   while ( p != NULL && j < i ) { p = p->link;  j = j++; }	//Ѱ�ҵ�i�����ĵ�ַ
		   return p;				 //�������ص�i������ַ, ������NULL, ��ʾiֵ̫��
		}

		template <class Type> int List<Type>::Insert ( Type value, int i ) {
		//����Ԫ��value�����������е�i��λ�á�
		   ListNode<Type> *p = FindPosition ( i-1 );					//��λ��i-1��Ԫ�� (i ( 0)
		   if ( p == NULL ) return 0;						//����i��ֵ��������������0
		   ListNode<Type> *newnode = GetNode ( value, p->link );	//������value�Ľ��
		   if ( p->link == NULL ) last = newnode;
		   p->link = newnode;							//����ɹ�����������1
		   return 1;
		}

		template <class Type> Type *List<Type>::Remove ( int i ) {
		//�������еĵ�i��Ԫ��ɾȥ, ͨ���������ظ�Ԫ�ء���i������, �򷵻�NULL��
		   ListNode<Type> *p = FindPosition (i-1), *q;				// p��λ�ڵ�i-1��Ԫ��
		   if ( p == NULL || p->link == NULL ) return NULL;		// i��ֵ�������ձ�����NULL
		   q = p->link;  p->link = q->link;					// qָ��ɾ��㣬��������
		   Type value = q->data;						//ȡ����ɾ����е�����ֵ
		   if ( q == last ) last = p;						//ɾ��β���ʱ, ��βָ���޸�
		   delete q;  return &value;
		}

		template <class Type> Type *List<Type>::Get ( int i ) {
		//ȡ�������е�i��Ԫ�ء�
		   ListNode<Type> *p = FindPosition ( i );					//��λ�ڵ�i��Ԫ��
		   if ( p == NULL || p == first ) return NULL;			//�ձ�����i��ֵ������
		   else return & p->data;
		}

		template < class Type > void List<Type> :: Print() {
		    int i = 0;
		    Type *p = Get (i);
		    while ( p != NULL ) {
			cout << *p << "  " ;
			p = Get ( ++i );
		    }
		    if ( i == 0 ) cout << " empty!!!! ";
		    cout << endl;
		}
