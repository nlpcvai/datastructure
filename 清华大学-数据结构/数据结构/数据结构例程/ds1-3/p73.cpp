		class List {
		public:
		   //链表操作
		   //………
		private:
		   class ListNode {						//嵌套的类
		   public:
		      int data;						//结点的数据域
		      ListNode *link;					//结点的指针域
		   };
		   ListNode *first;						//单链表的表头指针
		};
