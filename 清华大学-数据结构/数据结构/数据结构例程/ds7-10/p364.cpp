		const int DefaultSize = 26;
		template <class Name, class Attribute> class HashTable {		//词典的抽象数据类型
		//对象: 一组<名字-属性>对, 其中, 名字是唯一的。
		public:
		   Dictionary ( int size = DefaultSize );			//建立一个容量为size的空的词典
		   int IsIn ( Name name );				//若name在词典中, 则返回1, 否则返回0
		   Attribute *Find ( Name name );			//若name在词典中, 则返回指向相应Attr的指针, 否则返回0
		   void Insert ( Name name, Attribute attr );	
					//若name在词典中, 则修改相应<name, Attr>对的attr项; 否则插入<name, Attr>到词典中
		   void Remove ( Name name );				//若name在词典中, 则在词典中删除相应的<name, Attr>对
		};
