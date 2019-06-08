		#include <stdio.h>
		#include <iostream.h>

		template <class Type> class DblList;

		template <class Type> class DblNode {
		friend class DblList<Type>;
		private:
		  Type data;								//����������
		  DblNode<Type> *lLink, *rLink;					//����ǰ��(����)�����(����)ָ��
		  DblNode ( Type value, DblNode<Type> *left, DblNode *right ) :
		      data (value), lLink (left), rLink (right) { }				//���캯��
		  DblNode ( Type value ) : data (value), lLink (NULL), rLink (NULL) { }	//���캯��
		};

		template <class Type> class DblList {
		public:
		   DblList ( Type uniqueVal );						//���캯��: ����˫��ѭ������ı�ͷ��㡣
		   ~DblList ( );								//��������: �ͷ�˫��ѭ���������ô洢��
		   int Length ( ) const;							//����˫��ѭ������ĳ��ȡ�
		   int IsEmpty ( ) { return first->rLink == first; }			//��˫��ѭ������շ�
		   int Find ( const Type & target );					//��������Ѱ�ҵ��ڸ���ֵ�Ľ�㡣
		   Type getData ( ) const ;						//���ص�ǰ����д洢��ֵ��
		   void Firster ( ) { current = first; }					//��ʼ��: ����ǰָ��ָ����ͷ��㡣
		   int First ( );								//��ǰָ��ָ�������ͷ��㡣
		   int Next ( );								//��ǰָ��ָ����ǰ���ĺ�̽�㡣
		   int Prior ( );								//��ǰָ��ָ����ǰ����ǰ����㡣
		   int operator ! ( ) { return current != NULL; }			//���ز�����: �е�ǰָ��current�շ�
		   void Insert ( const Type & value );					//����һ��������ֵvalue���½�㡣
		   void Remove ( );						//ɾ����ǰ��㡣
		   void Print ();
		private:
		   DblNode<Type> *first, *current;
		};


		template <class Type> DblList<Type>::DblList ( Type uniqueVal ) {
		//���캯��: ����˫��ѭ������ı�ͷ���, ��������һ������ĳЩ�ض������ֵ��
		   first = new DblNode<Type> ( uniqueVal );
		   first->rLink = first->lLink = first;   current = NULL;
		}

		template <class Type> DblList<Type>::~DblList() {
		    current = first->rLink;
		    while ( current != first ) { current = current->lLink; delete current->lLink; }
		    delete first;
		}

		template <class Type> int DblList<Type>::Length ( ) const {
		//�������ͷ����˫��ѭ������ĳ���, ͨ���������ء�
		   DblNode<Type> * p = first->rLink;
		   int count = 0;
		   while ( p != first ) { p = p->rLink;  count++; }
		   return count;
		}

		template <class Type> int DblList<Type>::Find ( const Type & target ) {
		//�ڴ���ͷ����˫��ѭ��������Ѱ����ֵ����target�Ľ��, ���ҵ�, ��������1, ͬʱcurrentָ��
		//ָ��ý��, ����������0��
		   DblNode<Type> *p = first->rLink;
		   while ( p != first && p->data != target )  p = p->rLink;		//Ѱ�Һ�target�Ľ��
		   if ( p != first ) { current = p;  return 1; }					//�����ɹ�, ����1
		   return 0;										//û���ҵ�, ����0
		}

		template <class Type> Type DblList<Type>::getData () const {
		    if ( current == NULL ) return first->data;
		    else return current->data;
		}

		template <class Type> int DblList<Type>::First ( ) {
		//������ǿ�, �򽫵�ǰָ��ָ������ĵ�һ������Һ�������1; �������, ���ǰָ��ΪNULL��
		//��������0��
		   if ( !IsEmpty ( ) ) { current = first->rLink;  return 1; }
		   current = NULL;  return 0;
		}

		template <class Type> int DblList<Type>::Next ( ) {
		//����ǰ����к�̽��, ��ǰָ��ָ����ǰ���ĺ�̽���Һ�������1, �����ǰָ��ΪNULL
		//�Һ�������0��
		   if ( current->rLink == first ) { current = NULL;  return 0; }
		   current = current->rLink;  return 1;
		}

		template <class Type> int DblList<Type>::Prior ( ) {
		//����ǰ�����ǰ�����, ��ǰָ��ָ����ǰ����ǰ������Һ�������1; �����ǰָ��ΪNULL
		//�Һ�������0��
		   if ( current->lLink == first ) { current = NULL;  return 0; }
		   current = current->lLink;  return 1;
		}

		template <class Type> void DblList<Type>::Insert ( const Type & value ) {
		//����һ��������ֵvalue���½��, ��������뵽��ǰ���֮��
		   if ( current == NULL )							//ԭΪ�ձ�
		      current = first->rLink = new DblNode<Type> ( value, first, first );
		   else {										//ԭΪ�ǿձ�
			 current->rLink = new DblNode<Type> ( value, current, current->rLink );
			 current = current->rLink;						//�½���Ϊ��ǰ���
		       }
		   current->rLink->lLink = current;						//�����������
		}

		template <class Type> void DblList<Type>::Remove ( ) {
		//�ڴ���ͷ����˫��ѭ��������ɾ����ǰ���, ͬʱ�õ�ǰָ��ָ�������е���һ�����, ����ɾ���
		//���������һ�����, ���õ�ǰָ��ָ��������ǰ�˵�һ����㡣���ɾ���������ɿ�����, ���
		//ǰָ��ΪNULL��
		   if ( current != NULL ) {
		      DblNode<Type> *temp = current;
		      current = current->rLink;						//��ǰָ��ָ����һ���
		      current->lLink = temp->lLink;						//����ɾ��������ժ��
		      temp->lLink->rLink = current;  delete temp; 			//ɾ��
		      if ( current == first )
			 if ( IsEmpty ( ) ) current = NULL;					//ɾ��������
			 else  current = current->rLink;
		   }
		}

		template <class Type> void DblList<Type>::Print ( ) {
		    if ( first->rLink == first ) cout << "It is empty" << endl;
		    else {
			DblNode<Type> * temp = first;
			while ( temp->rLink != first ) {
			    temp = temp->rLink;
			    cout << temp->data << "  " ;
			}
			cout << endl;
		    }
		}
