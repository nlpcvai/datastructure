#include "p350.cpp"
		template <class Type> int Btree<Type>::Insert ( const Type & x ) {
		//���ؼ���x���뵽һ��פ���ڴ����ϵ�m��B-���С�
			if (!root)
			{
				root=new Mnode<Type>;
				insertkey ( root, 1, x, NULL );				//K, ap���뵽jλ��, ��p->n��1
			    PutNode (root);  return 1;				    //�����㵽����, ���ص��ó���				
			}
		   Triple<Type> loc = Search (x);				//����������x�Ĳ���λ��
		   if ( !loc.tag ) return 0;						//x�Ѿ�����������, ���ٲ���
		   Mnode<Type> *p = loc.r,  *q;				//r�ǹؼ���xҪ����Ľ���ַ
		   Mnode<Type> *ap = NULL,  *t;				//ap�ǲ���ؼ���x������ָ��
		   Type K = x;  int j = loc.i;					//(K,ap)�γɲ����Ԫ��
		   while (1) {
			 if ( p->n < m-1) {						//����йؼ������δ���������������¹ؼ���
			   insertkey ( p, j+1, K, ap );				//K, ap���뵽jλ��, ��p->n��1
			   PutNode (p);  return 1;				//�����㵽����, ���ص��ó���
			 }
			 int s = (m+1)/2;						//׼�����ѽ��, s��(m/2(λ��
			 insertkey ( p, j+1, K, ap );					//�Ȳ���, �����p->n�ﵽm
			 q = new Mnode<Type>;					//�����½��q
			 move ( p, q, s, m );						//�� p��key[s+1..m]��ptr[s..m]�Ƶ�q��key[1..s-1]
											//��ptr[0..s-1],  p->n��Ϊs-1, q->n��Ϊs-1
			 K = p->key[s];  ap = q;		//(K,ap)�γ����ϲ����Ԫ��
			 if ( p->parent != NULL ) {				//�������Ͻ��е���: ԭ����p��Ϊ��
			   t = p->parent;  GetNode (t);				//�Ӵ����϶�ȡp��˫�׽��
			   j = 0;  t->key[(t->n)+1] = MAXKEY;			//��˫�׽����˳����������λ��, �������
			   while ( t->key[j+1] < K ) j++;			//����, �ҵ� >K�Ĺؼ���ͣ
			   ap->parent = p->parent;				//�½���˫��ָ�븳ֵ
	 		   PutNode (p);  PutNode (ap);				//�����㵽����
			   p = t;							//p�����������, ���ϵ���
			 }
			 else {								//ԭ����p�Ǹ�, ��Ҫ�����µĸ�
			   root = new Mnode<Type>;
			   root->n = 1;  root->parent = NULL;		//�����¸�
			   root->key[1] = K;  root->ptr[0] = p;  root->ptr[1] = ap;
			   ap->parent = p->parent = root;
			   PutNode (p);  PutNode (ap);  PutNode (root);	//�����㵽����
			   return 1;
			 }
		   }
		}
		
