#include "p350.cpp"
		template <class Type> int Btree<Type>::Insert ( const Type & x ) {
		//将关键码x插入到一个驻留在磁盘上的m阶B-树中。
			if (!root)
			{
				root=new Mnode<Type>;
				insertkey ( root, 1, x, NULL );				//K, ap插入到j位置, 且p->n加1
			    PutNode (root);  return 1;				    //输出结点到磁盘, 返回调用程序				
			}
		   Triple<Type> loc = Search (x);				//在树中搜索x的插入位置
		   if ( !loc.tag ) return 0;						//x已经存在于树中, 不再插入
		   Mnode<Type> *p = loc.r,  *q;				//r是关键码x要插入的结点地址
		   Mnode<Type> *ap = NULL,  *t;				//ap是插入关键码x的右邻指针
		   Type K = x;  int j = loc.i;					//(K,ap)形成插入二元组
		   while (1) {
			 if ( p->n < m-1) {						//结点中关键码个数未超出，还可容下新关键码
			   insertkey ( p, j+1, K, ap );				//K, ap插入到j位置, 且p->n加1
			   PutNode (p);  return 1;				//输出结点到磁盘, 返回调用程序
			 }
			 int s = (m+1)/2;						//准备分裂结点, s是(m/2(位置
			 insertkey ( p, j+1, K, ap );					//先插入, 结点中p->n达到m
			 q = new Mnode<Type>;					//建立新结点q
			 move ( p, q, s, m );						//将 p的key[s+1..m]和ptr[s..m]移到q的key[1..s-1]
											//和ptr[0..s-1],  p->n改为s-1, q->n改为s-1
			 K = p->key[s];  ap = q;		//(K,ap)形成向上插入二元组
			 if ( p->parent != NULL ) {				//从下向上进行调整: 原来的p不为根
			   t = p->parent;  GetNode (t);				//从磁盘上读取p的双亲结点
			   j = 0;  t->key[(t->n)+1] = MAXKEY;			//在双亲结点内顺序搜索插入位置, 设监视哨
			   while ( t->key[j+1] < K ) j++;			//搜索, 找到 >K的关键码停
			   ap->parent = p->parent;				//新结点的双亲指针赋值
	 		   PutNode (p);  PutNode (ap);				//输出结点到磁盘
			   p = t;							//p上升到父结点, 向上调整
			 }
			 else {								//原来的p是根, 则要产生新的根
			   root = new Mnode<Type>;
			   root->n = 1;  root->parent = NULL;		//创建新根
			   root->key[1] = K;  root->ptr[0] = p;  root->ptr[1] = ap;
			   ap->parent = p->parent = root;
			   PutNode (p);  PutNode (ap);  PutNode (root);	//输出结点到磁盘
			   return 1;
			 }
		   }
		}
		
