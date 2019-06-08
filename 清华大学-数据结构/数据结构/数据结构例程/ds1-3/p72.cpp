		class List;							//List类的前视声明

		class ListNode {						//结点类定义
		friend class List;						//声明List类为友元类
		private:
		   int data;							//数据元素域
		   ListNode *link;						//链指针域
		};

		class List {							//List类定义
		public:
		   //链表公共操作
		   //………
		private:
		   ListNode *first, *last;						//指向链表表头的指针
		};
