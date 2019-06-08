#include "p353.cpp"
		template <class Type> int Btree<Type>::Remove ( const Type & x ) {
		//从驻留磁盘上的m阶B-树上删除x。
		   Triple<Type> loc = Search (x);			//在树中搜索x
		   if ( loc.tag ) return 0;					//x不在B-树中, 返主
		   Mnode<Type> *p = loc.r, *q, *s;			//p是关键码x所在结点
		   int j = loc.i;						//j是关键码在结点中的位置
		   if ( p->ptr[j] != NULL ) {				//若p非叶结点
			 s = p->ptr[j];  GetNode (s);  q = p;		//读取磁盘上的s结点
			 while ( s != NULL ) { q = s;  s = s->ptr[0]; }	//找大于x但最接近于x的最小关键码(q是叶结点)
			 p->key[j] = q->key[1];				//用最小关键码填补
			 compress ( q, 1 );					//在q结点中关键码与指针前移填补key[1], q->n减1
			 p = q;						//下一步处理q结点中的删除
   		   }
		   else compress ( p, j );					//p是叶结点, 关键码与指针前移填补key[j], p->n减1
		   int d = (m+1)/2;						//结点容纳关键码的下限
		   if (!(p==root))
		   while (1) {
			 if ( p->n < d-1 ) {					//需要调整
			   j = 0;  q = p->parent;			//在q中找指向p的指针
			   GetNode (q);
			   while ( j <= q->n && q->ptr[j] != p ) j++;
			   if ( !j ) LeftAdjust ( p, q, d, j );		//p是q的最左子女, 与其右兄弟与双亲结点做调整
			   else 
				if (j==q->n) RightAdjust ( p, q, d, j );			//p是q的最右子女, 与其左兄弟与双亲结点做调整
			   else													//p是中间,选择一个较简单的合并方法
				if ( (q->ptr[j+1]->n) > d-1 ) LeftAdjust(p,q,d,j);  
			   else
				RightAdjust ( p, q, d, j );		
			   p = q;						//继续向上做结点调整工作
			   if ( p == root ) break;
			 }
			 else break;						//不需要进行调整, 跳出循环
		   }
		   if ( !root->n ) {					//当根结点为空时删根结点
			 p = root->ptr[0];  delete root;  root = p;  
			 if (root) root->parent = NULL;
		   }
		   return 1;
		}

		template <class Type>
		void Btree<Type>::LeftAdjust ( Mnode<Type> *p, Mnode<Type> *q, const int d, const int j ) {
		   Mnode<Type> *p1 = q->ptr[j+1];			//p的右兄弟
		   if ( p1->n > d-1 ) {					//右兄弟空间还够, 不用合并, 仅做调整
			 ( p->n ) ++;
			 p->key[p->n] = q->key[j+1];			//双亲结点相应关键码下移
			 q->key[j+1] = p1->key[1];				//右兄弟最小关键码上移到双亲结点
			 p->ptr[p->n] = p1->ptr[0];			//右兄弟最左指针左移
			 compress ( p1, 0 );
		   }
		   else merge ( p, q, p1,j );				//p与p1合并, 保留p结点
		}
		template <class Type> void Btree<Type>::compress ( Mnode<Type> *p, const int j ) {
		   for ( int i=j; i<p->n; i++ )				//左移 
			 { p->key[i] = p->key[i+1];  p->ptr[i] = p->ptr[i+1]; }
		   p->n --;							//结点中元素个数减1
		}

		template <class Type>
		 void Btree<Type>::merge ( Mnode<Type> *p, Mnode<Type> *q, Mnode<Type> *p1, const int j) {
		   p->key[(p->n)+1] = q->key[j+1];			//从双亲结点下降一个关键码
		   p->ptr[(p->n)+1] = p1->ptr[0];			//从右兄弟结点左移一个指针
		   for ( int k=1; k<=p1->n; k++ ) {				//从右兄弟结点
		      p->key[(p->n)+k+1] = p1->key[k];		//关键码从p1到p左移
	      	p->ptr[(p->n)+k+1] = p1->ptr[k];		//指针从p1到p左移
		   }
		   compress ( q, j+1 );					//双亲结点q中值与指针左移
		   p->n = p->n + p1->n + 1;
		   delete p1;
		}

		template <class Type>
		void Btree<Type>::RightAdjust ( Mnode<Type> *p, Mnode<Type> *q, const int d, const int j )
		//此程序与LeftAdjust功能基本相同，但与LeftAdjust是对称的：左右指针互换，前端与后端互换。
		{
		   Mnode<Type> *p1 = q->ptr[j-1];			//p的左兄弟
		   if ( p1->n > d-1 ) {					//左兄弟空间还够, 不用合并, 仅做调整
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
		   else merge ( p1, q, p,j-1 );				//p1与p合并, 保留p结点
		}
