		#include <stdio.h>

		enum Boolean { False, True };
		template <class Type> class List;					//�������ǰ�Ӷ���
		template <class Type> class ListIterator;				//���������ǰ�Ӷ���

		template <class Type> class ListNode {					//���������������
		friend class List <Type>;							//��Ԫ
		friend class ListIterator <Type>;					//��Ԫ
		friend class Polynomial;
		friend Polynomial operator + ( const Polynomial & ah, const Polynomial & bh );
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
		   int sum ();
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
		   ListNode<Type>* First ( );
		   ListNode<Type>* Next ( );
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

		template <class Type> ListNode<Type>* ListIterator<Type>::First ( ) {
		//����ָ�������б�ͷ����ָ��
		   if ( list.first->link != NULL ) { current = list.first; }
		   else { current = NULL; }
		   return current ;
		}

		template <class Type> ListNode<Type>* ListIterator<Type>::Next ( ) {
		//����ָ����������һ������ָ��
		   if ( current != NULL && current->link != NULL ) { current = current->link; }
		   else { current = NULL; }
		   return current;
		}

		char compare ( int a, int b ) {
		    if ( a > b ) return '>';
		    else if ( a == b ) return '=';
		    else return '<';
		}

		struct Term {						//�������ʾ�Ķ���ʽ��, ������Ķ���
		   int coef;							//ϵ��
		   int exp;							//ָ��
		   void Init ( int c, int e ) { coef = c;  exp = e; }
		};

		class Polynomial	{					//����ʽ��Ķ���
		friend Polynomial operator + ( const Polynomial &, const Polynomial & );
		private:
		   List<Term> poly;					//������ṹ, ���ݲ�����Term
		};


		Polynomial operator + ( const Polynomial & ah, const Polynomial & bh ) {
		//������ͷ���İ��������еĶ���ʽ�����ͷָ��ֱ���ah��bh, �����ǽ������ʽ����ı�ͷָ��,
		//ָ��ah�ı�ͷ���, �ҽ��������ռ�ô洢, ����ah��bh����
		   ListNode<Term> *pa, *pb, *pc, *p;
		   ListIterator<Term> Aiter ( ah.poly );
		   ListIterator<Term> Biter ( bh.poly );
		   pa = pc = Aiter.First ( );  pb = Biter.First ( );			//ȡ��ah��bh�ı�ͷ���
		   pa = Aiter.Next ( );  pb = Biter.Next ( );				//pa��pb������ah��bh�ļ��ָ��
		   delete pb;								//����ah�ı�ͷ���, ɾȥbh�ı�ͷ���
		   while ( Aiter.NotNull ( ) && Biter.NotNull ( ) )			//�����Ƚ�
			  switch ( compare ( pa->data.exp, pb->data.exp ) ) {
				case '=' :							//pa��exp==pb��exp
				   pa->data.coef = pa->data.coef+pb->data.coef;			//ϵ�����
				   p = pb;  pb = Biter.Next ( );  delete p;		//ɾȥԭpb��ָ���
				   if ( !pa->data.coef ) { p = pa;  pa = Aiter.Next ( );  delete p; }	//���Ϊ��, ��Ҫ
				   else { pc->link = pa;  pc = pa;  pa = Aiter.Next ( ); }		//��Ӳ�Ϊ��, ����ch��
				   break;
				case '<' :							//pa��exp < pb��exp
				   pc->link = pb;  pc = pb;  pb = Biter.Next ( );
				   break;
				case '>' :							//pa��exp > pb��exp
				   pc->link = pa;  pc = pa;  pa = Aiter.Next ( );
			  }
		   if ( Aiter.NotNull ( ) )  pc->link = pa;				//ʣ�ಿ������ch��
		   else  pc->link = pb;
		   return ah;
		}

		Polynomial operator * ( const Polynomial & ah, const Polynomial & bh )


		void Calc ( ) {
		   Polynomial a, b, c, d, t;
		   cin >> a;  cin >> b;  cin >> c;				//����3������ʽ
		   t = a * b;  d = t + c;
		   cout << d;
		}
