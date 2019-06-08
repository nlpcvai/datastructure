#include "iostream.h"
#ifndef MAXKEY
#define MAXKEY 32767
#endif
		const MaxM=100;
		template <class Type> class Mtree;
		template <class Type> class Btree;
		template <class Type> class Mnode {					// B_������ඨ��
		public:
			void insertkey(int,Type,Mnode<Type>*);
			Mnode(){n=0;parent=NULL;for (int i=0;i<=MaxM;i++) ptr[i]=NULL;}
		private:
		   int n;									//��ǰ����йؼ������
		   Mnode<Type> *parent;						//˫�׽��ָ��
		   Type key[MaxM+1];								//key[MaxM]Ϊ�����ڼ湤����Ԫ, key[0]δ��
		   Mnode<Type> *ptr[MaxM+1];						//�������ָ������, ptr[m]δ��
		   friend ostream& operator <<(ostream& strm, Mnode<Type>& mn);
		   friend class Mtree<Type>;
		   friend class Btree<Type>;
		};
		
		template <class Type>
		class Triple {								//�������
		public:
		   Mnode<Type> *r;							//B_������ַ
		   int i;  char tag;							//����йؼ�����ż������ɹ���־
		   friend ostream& operator <<(ostream& strm, Triple<Type>& tp);
		};

		template <class Type> class Mtree {                 
		public:
		   Mtree(int d=3){root=NULL;m=d;};		   
		   void insertkey(Mnode<Type>*,int,Type,Mnode<Type>*);
		   Triple<Type>  Search ( const Type & );
		   friend ostream& operator <<(ostream& strm, Mtree<Type>& mt);
		protected:
			void move ( Mnode<Type>*p, Mnode<Type>*q, int s, int m );
			void print(ostream& strm,Mnode<Type> *p);
		   Mnode<Type> *root;
		   int m;
		};

		template <class Type> Triple<Type>  Mtree<Type>::Search ( const Type & x ) {
		//�ùؼ���x����פ���ڴ����ϵ�m·��������������ʽΪn, A[0], (k[1],A[1]),����,  (K[n],A[n]), n < m��
		//��������һ������ΪTriple (r, i, tag)�Ķ���tag=1, ��ʾx �ڽ��r�ҵ�, �Ǹý���K[i];  tag=0, ��
		//ʾû���ҵ�x, ��ʱ���Բ���Ľ����r, ���뵽�ý���K[i]��K[i+1]֮�䡣
		   Triple<int> result;							//��Ž���Ĺ�����Ԫ
		   GetNode ( root );						//�Ӵ����϶�ȡλ�ڸ�root�Ľ��
		   Mnode <Type> *p = root, *q = NULL;			//p��ɨ��ָ��, q��p�ĸ����ָ��
		   int i;
		   while ( p != NULL ) {						//��������
			 i = 0;  p->key[(p->n)+1] = MAXKEY;
			 while ( p->key[i+1] < x ) i++;				//�ڽ����˳������
			 if ( p->key[i+1] == x ) {					//�����ɹ�, �������x
				result.r = p;  result.i = i+1;  result.tag = 0;
				return result;					//���ؽ��, ����������
			 }
			 q = p;  p = p->ptr[i];					//�������x, q���µ�ǰ���, p�½�����Ӧ����			 GetNode (p);							//�Ӵ����϶�ȡp���
		   }
		   result.r = q;  result.i = i;  result.tag = 1;
		   return result;							//x�������������[ Ki, Ki+1 )
		}
		template <class Type> class Btree : public Mtree<Type> {		//B_�����ඨ��
		public:
		   //Search��Mtree�̳�;
		   int Insert ( const Type& x );						//����ؼ���x
		   int Remove ( const Type& x );					//ɾ���ؼ���x
		private:		
		void LeftAdjust ( Mnode<Type> *p, Mnode<Type> *q, const int d, const int j );
		void RightAdjust ( Mnode<Type> *p, Mnode<Type> *q, const int d, const int j );
		void compress ( Mnode<Type> *p, const int j );
		void merge ( Mnode<Type> *p, Mnode<Type> *q, Mnode<Type> *p1, int j) ;

		};
		template <class Type>
			void GetNode(Mnode<Type> *p)
		{
			//������Ӧ�ôӴ��̶�����p,�����������Ϊ��
		};		
		template <class Type>
			void PutNode(Mnode<Type> *p)
		{
			//������Ӧ�ôӴ���д���p,�����������Ϊ��
		};		

		template <class Type>
			void Mtree<Type>::print(ostream& strm,Mnode<Type> *p)
		{
			if (p)
			{		
			strm<<*p;
			if (p->n)
			{	strm<<"(";
				for (int i=0;i<=p->n;i++)				
					print(strm,p->ptr[i]);
			
				strm<<")";
			}
			}
		}
		template <class Type>
		ostream& operator <<(ostream& strm, Mtree<Type>& mt)
		{
			mt.print(strm,mt.root);
			return strm;
		}
		template <class Type>
		ostream& operator <<(ostream& strm, Mnode<Type>& mn)
		{
			strm<<"[";
			for (int i=1;i<=mn.n;i++)
			{
				if (i!=1) strm<<',';
				strm<<mn.key[i];
			}
			strm<<"]";
			return strm;
			
		}
	template <class Type>
	 ostream& operator <<(ostream& strm, Triple<Type>& tp)
	{
		if (tp.tag) strm<<"Key Not Found";
			else
			strm<<"Key Found at :"<<*tp.r<<" No. "<<tp.i<<" key";
		return strm;
	}
	template <class Type>
		void Mnode<Type>::
	insertkey(int i,Type K,Mnode<Type>* q)
	{
		for (int j=n;j>=i;j--)
		{
			key[j+1]=key[j];
			ptr[j+1]=ptr[j];
		}
		key[i]=K;
		ptr[i]=q;
		n++;
	};
	template <class Type>
		void Mtree<Type>::
	insertkey(Mnode<Type>* p,int i,Type K,Mnode<Type>* q)
	{
		p->insertkey(i,K,q);
	}
	template <class Type>
		void Mtree<Type>::move ( Mnode<Type>*p, Mnode<Type>*q, int s, int m )
	//�� p��key[s+1..m]��ptr[s..m]�Ƶ�q��key[1..s-1]��ptr[0..s-1]
	//p->n��Ϊs, q->n��Ϊm-s
	{
		int j=0;
		q->ptr[0]=p->ptr[s];
		if (q->ptr[0])
			q->ptr[0]->parent=q; 
		for (int i=s+1;i<=m;i++)
		{
			j++;
			q->key[j]=p->key[i];
			q->ptr[j]=p->ptr[i];
			if (q->ptr[j])
				q->ptr[j]->parent=q;
		}
		q->n=m-s;
		p->n=s-1;
	}