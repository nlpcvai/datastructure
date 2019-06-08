		const int MaxKeySize = 25;
		typedef enum { branch, element } NODETYPE;
		
        class KeyType
		{ 						//关键码的类型定义
		public:
		   char ch[MaxKeySize];					//存放关键码的字符数组
		   int currentSize;						//关键码的长度
		   int operator == (const KeyType &);
		} ;
		
		template <class RecordNode> class Trie;

		template <class RecordNode>
		class TrieNode {						//Trie树结点的类定义
		friend class Trie<RecordNode>;						//友元类
		protected:
		   NODETYPE NodeType;			//结点分类
		   union NodeType {					//结点结构定义
			 struct {						//分支结点
			   int num;						//在分支结点中非空指针个数
			   TrieNode *link[27];				//下标为'b', 'a', 'b', …, 'z'的指针数组
			 } brch;
			 struct {						//元素结点
			   KeyType key;					//关键码
			   RecordNode *recptr;				//指向实际数据记录的指针
			 } elem;
		   }data;
		};

		template <class RecordNode>
		class Trie {							//Trie树的类定义
		private:
		   TrieNode<RecordNode> *root, *current;				//Trie的根指针和当前指针
		public:
		   RecordNode* Search ( const KeyType & );
		   int Insert ( const KeyType & ); 
		   int Delete ( const KeyType & );
		};
		template <class RecordNode>
			RecordNode* Trie<RecordNode>::Search ( const KeyType & x ) {
		//在一棵Trie树上搜索关键码x。设第i-1层的分支是由关键码的第i个字符决定的。
		   KeyType k = x;  
		   concatenate ( k, 'b' );				//在搜索值后面连接一个结束符'b'
		   current = root;  
		   int i = 0;					//从根开始，先在结点中判断
		   while ( (current) && (current->NodeType != element) && (i <= k.ch[i]) )
			 { current = current->data.brch.link[k.ch[i]];  i = i++; };
			  //从根向下逐层比较, ord (k.ch[i])是字符k.ch[i]在字母表中的序号, 'b'是第0个
		   if ( (current) && current->NodeType == element && current->data.elem.key == x )
			 return current->data.elem.recptr;				//找到, 返回对应记录位置
	 		 else return 0;						//没有找到, 返回空地址
		}
		int KeyType:: operator == (const KeyType & d)
		{
			if (currentSize!=d.currentSize) return 0;
			for (int i=0;i<currentSize;i++)
				if (ch[i]!=d.ch[i]) return 0;
			return 1;
		};