#include "p353.cpp"
		template <class Type> int Btree<Type>::Remove ( const Type & x ) {
		//��פ�������ϵ�m��B-����ɾ��x��
		   Triple<Type> loc = Search (x);			//����������x
		   if ( loc.tag ) return 0;					//x����B-����, ����
		   Mnode<Type> *p = loc.r, *q, *s;			//p�ǹؼ���x���ڽ��
		   int j = loc.i;						//j�ǹؼ����ڽ���е�λ��
		   if ( p->ptr[j] != NULL ) {				//��p��Ҷ���
			 s = p->ptr[j];  GetNode (s);  q = p;		//��ȡ�����ϵ�s���
			 while ( s != NULL ) { q = s;  s = s->ptr[0]; }	//�Ҵ���x����ӽ���x����С�ؼ���(q��Ҷ���)
			 p->key[j] = q->key[1];				//����С�ؼ����
			 compress ( q, 1 );					//��q����йؼ�����ָ��ǰ���key[1], q->n��1
			 p = q;						//��һ������q����е�ɾ��
   		   }
		   else compress ( p, j );					//p��Ҷ���, �ؼ�����ָ��ǰ���key[j], p->n��1
		   int d = (m+1)/2;						//������ɹؼ��������
		   if (!(p==root))
		   while (1) {
			 if ( p->n < d-1 ) {					//��Ҫ����
			   j = 0;  q = p->parent;			//��q����ָ��p��ָ��
			   GetNode (q);
			   while ( j <= q->n && q->ptr[j] != p ) j++;
			   if ( !j ) LeftAdjust ( p, q, d, j );		//p��q��������Ů, �������ֵ���˫�׽��������
			   else 
				if (j==q->n) RightAdjust ( p, q, d, j );			//p��q��������Ů, �������ֵ���˫�׽��������
			   else													//p���м�,ѡ��һ���ϼ򵥵ĺϲ�����
				if ( (q->ptr[j+1]->n) > d-1 ) LeftAdjust(p,q,d,j);  
			   else
				RightAdjust ( p, q, d, j );		
			   p = q;						//��������������������
			   if ( p == root ) break;
			 }
			 else break;						//����Ҫ���е���, ����ѭ��
		   }
		   if ( !root->n ) {					//�������Ϊ��ʱɾ�����
			 p = root->ptr[0];  delete root;  root = p;  
			 if (root) root->parent = NULL;
		   }
		   return 1;
		}

		template <class Type>
		void Btree<Type>::LeftAdjust ( Mnode<Type> *p, Mnode<Type> *q, const int d, const int j ) {
		   Mnode<Type> *p1 = q->ptr[j+1];			//p�����ֵ�
		   if ( p1->n > d-1 ) {					//���ֵܿռ仹��, ���úϲ�, ��������
			 ( p->n ) ++;
			 p->key[p->n] = q->key[j+1];			//˫�׽����Ӧ�ؼ�������
			 q->key[j+1] = p1->key[1];				//���ֵ���С�ؼ������Ƶ�˫�׽��
			 p->ptr[p->n] = p1->ptr[0];			//���ֵ�����ָ������
			 compress ( p1, 0 );
		   }
		   else merge ( p, q, p1,j );				//p��p1�ϲ�, ����p���
		}
		template <class Type> void Btree<Type>::compress ( Mnode<Type> *p, const int j ) {
		   for ( int i=j; i<p->n; i++ )				//���� 
			 { p->key[i] = p->key[i+1];  p->ptr[i] = p->ptr[i+1]; }
		   p->n --;							//�����Ԫ�ظ�����1
		}

		template <class Type>
		 void Btree<Type>::merge ( Mnode<Type> *p, Mnode<Type> *q, Mnode<Type> *p1, const int j) {
		   p->key[(p->n)+1] = q->key[j+1];			//��˫�׽���½�һ���ؼ���
		   p->ptr[(p->n)+1] = p1->ptr[0];			//�����ֵܽ������һ��ָ��
		   for ( int k=1; k<=p1->n; k++ ) {				//�����ֵܽ��
		      p->key[(p->n)+k+1] = p1->key[k];		//�ؼ����p1��p����
	      	p->ptr[(p->n)+k+1] = p1->ptr[k];		//ָ���p1��p����
		   }
		   compress ( q, j+1 );					//˫�׽��q��ֵ��ָ������
		   p->n = p->n + p1->n + 1;
		   delete p1;
		}

		template <class Type>
		void Btree<Type>::RightAdjust ( Mnode<Type> *p, Mnode<Type> *q, const int d, const int j )
		//�˳�����LeftAdjust���ܻ�����ͬ������LeftAdjust�ǶԳƵģ�����ָ�뻥����ǰ�����˻�����
		{
		   Mnode<Type> *p1 = q->ptr[j-1];			//p�����ֵ�
		   if ( p1->n > d-1 ) {					//���ֵܿռ仹��, ���úϲ�, ��������
			 ( p->n ) ++;
			 for (int i=p->n; i>=1;i--)
			 {
				 p->key[i]=p->key[i-1];
				 p->ptr[i]=p->ptr[i-1];
			 }
			 p->key[1]=q->key[j];
			 q->key[j]=p1->key[p1->n];
			 p->ptr[0]=p1->ptr[p1->n];
			 (p1->n)--;
		   }
		   else merge ( p1, q, p,j-1 );				//p1��p�ϲ�, ����p���
		}
