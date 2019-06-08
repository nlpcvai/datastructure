		#include <stdio.h>

		enum Boolean { False, True };
		template <class Type> class List;					//�������ǰ�Ӷ���
		template <class Type> class ListIterator;				//���������ǰ�Ӷ���

		template <class Type> class ListNode {					//���������������
		friend class List <Type>;							//��Ԫ
		friend class ListIterator <Type>;					//��Ԫ
		public:
		   ListNode ( const Type value ) : data (value), link (NULL) { }
		   //������
		private:
		   Type data;
		   ListNode<Type> *link;
		};

		template <class Type> class List {					//�������������
		public:
		   friend class ListIterator<Type>;
		   List ( const Type value) { last =first = new ListNode<Type> (value) ; }	//���캯��
		   void Add ( const Type value ) ;
		   //������
		private:
		   ListNode<Type> *first, *last;
		};

		template <class Type> class ListIterator {				//�����α����������
		public:
		   ListIterator ( const List<Type> & l ) : list (l), current (l.first) { }
		   Boolean NotNull ( );
		   Boolean NextNotNull ( );
		   Type First ( );
		   Type Next ( );
		private:
		   const List<Type> & list;						//����һ���Ѵ��ڵ�����
		   ListNode<Type> *current;						//ָ�������е�һ�����
		}

		template <class Type> Boolean ListIterator<Type>::NotNull ( ) {
		//��������е�ǰԪ���Ƿ�ǿ�
		   if ( current != NULL ) return True; 					//����ǰ���ָ��ǿ�
		   else return False;
		}

		template <class Type> Boolean ListIterator<Type>::NextNotNull ( ) {
		//�����������һԪ���Ƿ�ǿ�
		   if ( current != NULL && current->link != NULL ) return True;
		   else return False;
		}

		template <class Type> Type ListIterator<Type>::First ( ) {
		//����ָ�������б�ͷ����ָ��
		   Type temp;
		   if ( list.first->link != NULL ) {
		       current = list.first;
		       temp = current->data;
		   }
		   else { current = NULL; temp = 0;}
		   return temp;
		}

		template <class Type> Type ListIterator<Type>::Next ( ) {
		//����ָ����������һ������ָ��
		   Type temp;
		   if ( current != NULL && current->link != NULL ) {
		      current = current->link;
		      temp = current->data;
		   }
		   else { current = NULL; temp = 0;}
		   return temp;
		}


		int sum ( const List<int> &l ) {
		   ListIterator<int> li (l);							//�������liΪ�����������l���α����
		   if ( ! li.NextNotNull ( ) ) return 0;					//������, ����0
		   int retvalue = li.First ( );						//ȡ�õ�һ��Ԫ�ص�ֵ
		   while ( li.NextNotNull ( ) ) retvalue += li.Next ( );		//���Ƿ���һ�������ڣ�����, �ۼ�
		   return retvalue;
		}

		template <class Type> void List<Type>::Add(const Type value) {
		   last->link = new ListNode<Type> (value);
                   last = last->link;
		}

