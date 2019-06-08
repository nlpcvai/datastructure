		#include <stdio.h>
                #include <iostream.h>

		enum Boolean { False, True };
		template <class Type> class CircList;

		template <class Type> class CircListNode {
		friend class CircList<Type>;
		public:
		   CircListNode ( Type d=0, CircListNode<Type> *next=NULL ) : data (d), link (next) { }
		private:
		   Type data;
		   CircListNode<Type> *link;
		};

		template <class Type> class CircList {
		public:
		   CircList ();
		   CircList ( Type value );						//���캯��
		   ~CircList ( );								//��������
		   int Length ( ) const;							//����ѭ��������
		   Boolean IsEmpty ( ) { return first->link == first; }		//�б�շ�
		   Boolean Find ( const Type & value );				//��ѭ��������Ѱ����ֵ����value�Ľ��
		   Type getData ( ) { return current->data; }						//���ص�ǰ����д�ŵ�ֵ
		   Type getNextData () ;
		   void Firster ( ) { current = first; }					//����ǰָ������ͷ���
		   void First ( );							//����ǰָ��ָ������ĵ�һ�����
		   void Next ( );							//����ǰָ��ָ����ǰ���ĺ�̽��
		   void Prior ( );							//����ǰָ��ָ����ǰ����ǰ�����
		   void Insert ( const Type & value );					//�����½��
		   void RemoveNext ( );
		   void Josephus ( int n, int m );								//ɾ����ǰ���
		private:
		   CircListNode<Type> *first, *current, *last;			//ͷָ��, ��ǰָ��, βָ��
		};

		template <class Type> void CircList <Type> :: CircList () {
		    current = last = first = new CircListNode<Type> ();
		    first->link = first;
		}

		template <class Type> void CircList <Type> :: ~CircList () {
		    CircListNode<Type> *q;
		    while ( first->link != first ) {
			q = first->link;   first->link = q->link;
			delete q;
		    }
		    delete first;  current = first = last = NULL;
		}

		template <class Type> void CircList <Type> :: Next () {
		    if ( current->link == first ) current = first;
		    current = current->link;
		}

		template <class Type> Type CircList <Type> :: getNextData() {
		    if ( current->link == first ) return first->link->data;
		       else return current->link->data;
		}

		template <class Type> void CircList <Type> :: RemoveNext () {
		    CircListNode<Type> *p = current->link;
		    if ( p == last ) last = current;
		    if ( p != first ) current->link = p->link;
			else { p = first->link; first->link = p->link; }
		    delete p;
		}

		template <class Type> void CircList <Type> :: Insert (const Type & value) {
		    CircListNode<Type> *p = new CircListNode<Type> ( value, first );
		    last = last->link = p;
		}

		template <class Type> void CircList <Type> :: Josephus ( int n, int m ) {
		   for ( int i=0; i<n-1; i++ ) {		     				//ѭ��n-1�ˣ���n-1���˳���
			 for ( int j=0; j<m-1; j++ ) Next ( );	  			//��current����ƶ�m-1��
			 cout << "Delete person " << getNextData ( ) << endl;
			 RemoveNext ( ); 								//ɾȥ�ý�㣬��currentָʾ��һ���
		   }
		   cout << "the winner is : " << getData () << endl;
		}
