		class List;							//List���ǰ������

		class ListNode {						//����ඨ��
		friend class List;						//����List��Ϊ��Ԫ��
		private:
		   int data;							//����Ԫ����
		   ListNode *link;						//��ָ����
		};

		class List {							//List�ඨ��
		public:
		   //����������
		   //������
		private:
		   ListNode *first, *last;						//ָ�������ͷ��ָ��
		};
