		const int DefaultSize = 26;
		template <class Name, class Attribute> class HashTable {		//�ʵ�ĳ�����������
		//����: һ��<����-����>��, ����, ������Ψһ�ġ�
		public:
		   Dictionary ( int size = DefaultSize );			//����һ������Ϊsize�ĿյĴʵ�
		   int IsIn ( Name name );				//��name�ڴʵ���, �򷵻�1, ���򷵻�0
		   Attribute *Find ( Name name );			//��name�ڴʵ���, �򷵻�ָ����ӦAttr��ָ��, ���򷵻�0
		   void Insert ( Name name, Attribute attr );	
					//��name�ڴʵ���, ���޸���Ӧ<name, Attr>�Ե�attr��; �������<name, Attr>���ʵ���
		   void Remove ( Name name );				//��name�ڴʵ���, ���ڴʵ���ɾ����Ӧ��<name, Attr>��
		};
