		const int MaxKeySize = 25;
		typedef enum { branch, element } NODETYPE;
		
        class KeyType
		{ 						//�ؼ�������Ͷ���
		public:
		   char ch[MaxKeySize];					//��Źؼ�����ַ�����
		   int currentSize;						//�ؼ���ĳ���
		   int operator == (const KeyType &);
		} ;
		
		template <class RecordNode> class Trie;

		template <class RecordNode>
		class TrieNode {						//Trie�������ඨ��
		friend class Trie<RecordNode>;						//��Ԫ��
		protected:
		   NODETYPE NodeType;			//������
		   union NodeType {					//���ṹ����
			 struct {						//��֧���
			   int num;						//�ڷ�֧����зǿ�ָ�����
			   TrieNode *link[27];				//�±�Ϊ'b', 'a', 'b', ��, 'z'��ָ������
			 } brch;
			 struct {						//Ԫ�ؽ��
			   KeyType key;					//�ؼ���
			   RecordNode *recptr;				//ָ��ʵ�����ݼ�¼��ָ��
			 } elem;
		   }data;
		};

		template <class RecordNode>
		class Trie {							//Trie�����ඨ��
		private:
		   TrieNode<RecordNode> *root, *current;				//Trie�ĸ�ָ��͵�ǰָ��
		public:
		   RecordNode* Search ( const KeyType & );
		   int Insert ( const KeyType & ); 
		   int Delete ( const KeyType & );
		};
		template <class RecordNode>
			RecordNode* Trie<RecordNode>::Search ( const KeyType & x ) {
		//��һ��Trie���������ؼ���x�����i-1��ķ�֧���ɹؼ���ĵ�i���ַ������ġ�
		   KeyType k = x;  
		   concatenate ( k, 'b' );				//������ֵ��������һ��������'b'
		   current = root;  
		   int i = 0;					//�Ӹ���ʼ�����ڽ�����ж�
		   while ( (current) && (current->NodeType != element) && (i <= k.ch[i]) )
			 { current = current->data.brch.link[k.ch[i]];  i = i++; };
			  //�Ӹ��������Ƚ�, ord (k.ch[i])���ַ�k.ch[i]����ĸ���е����, 'b'�ǵ�0��
		   if ( (current) && current->NodeType == element && current->data.elem.key == x )
			 return current->data.elem.recptr;				//�ҵ�, ���ض�Ӧ��¼λ��
	 		 else return 0;						//û���ҵ�, ���ؿյ�ַ
		}
		int KeyType:: operator == (const KeyType & d)
		{
			if (currentSize!=d.currentSize) return 0;
			for (int i=0;i<currentSize;i++)
				if (ch[i]!=d.ch[i]) return 0;
			return 1;
		};