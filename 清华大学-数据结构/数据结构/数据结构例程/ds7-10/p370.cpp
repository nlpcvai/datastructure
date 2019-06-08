#ifndef DefaultSize
#define DefaultSize 100
#endif
		template <class Type>
		class HashTable {									//ɢ�б��ඨ��
		public:
		   enum KindOfEntry { Active, Empty, Deleted };				//������� (� / �� / ɾ)
		   HashTable ( int sz=DefaultSize ) : TableSize ( sz ) { AllocateHt ( );  CurrentSize = 0; }		//���캯��
		   ~HashTable ( ) { delete [ ] ht; }						//��������
		   const HashTable & operator = ( const HashTable & ht2 );		//���غ�������ֵ
		   int Find ( const Type & x );							//��ɢ�б�������x
		   int Insert ( const Type & x );							//��ɢ�б��в���x
		   int Remove ( const Type & x );						//��ɢ�б���ɾ��x
		   int IsIn ( const Type & x ) { return (  Find (x)  >= 0 ) ? 1 : 0; }	//��x��ɢ�б��з�
		   void MakeEmpty ( );								//��ɢ�б�Ϊ��
		   int FindPos ( const Type & x ); 					//ɢ�к���: ���㺬x����ĳ�ʼͰ��
		private:
		   struct HashEntry {								//�����
		      Type Element;								//���������, ������Ĺؼ���
		      KindOfEntry info;								//����״̬: Active, Empty, Deleted
		      int operator== ( HashEntry & );			//���غ����������е�����
		      int operator!= ( HashEntry & );				//���غ����������в�������
		      HashEntry ( ) : info (Empty ) { }						//����캯��, �ÿ�
		      HashEntry (const Type & E, KindOfEntry i = Empty ) : Element (E), info (i) { }
		   };
		   enum { DefualtSize = 11 };
		   HashEntry *ht;									//ɢ�б�洢����
		   int CurrentSize, TableSize;							//��ǰͰ�������Ͱ��
		   void AllocateHt ( ) { ht = new HashEntry[TableSize ]; }			//Ϊɢ�б����洢�ռ�
		};
		template <class Type> int HashTable<Type>::Find ( const Type & x ) {
		//ʹ������̽�鷨��ɢ�б�ht (ÿ��Ͱ����һ������)������x�����x�ڱ��д���, ��������x����
		//λ��j, ��ht[j]=x�����x���ڱ���, �򷵻� -j��
		   int i = FindPos ( x ),  j = i; 						//i�Ǽ��������ɢ�е�ַ, j����һ��Ͱ
		   while ( ht[j].info != Empty && ht[j].Element != x ) {		//ht[j]����, �Ҳ�����x����ͻ
			 j = ( j + 1 ) % TableSize;						//����ѭ������, ����һ����Ͱ 
			 if ( j == i ) return -TableSize-1;					//תһȦ�ص���ʼ��, ������, ʧ��
		   }
		   if ( ht[j].info == Active ) return j;					//�ҵ�����Ҫ��ı���, ����Ͱ��j
		   else return -j-1;									//ʧ��
		}
//	������ɢ�б���и��ִ���֮ǰ���������Ƚ�ɢ�б���ԭ�е������������ʱ���ǿ��Խ��������б����info����ΪEmpty���ɡ���Ϊɢ�б��ŵ��Ǳ���ϣ���Ӧ���ظ��Ĺؼ��룬�����ڲ����±���ʱ��������ֱ����Ѿ��йؼ�����ͬ�ı�����ٲ��롣	�ر�Ҫע����ǣ��ڱ�ɢ�е������²����������ɾ���������еı����Ϊ��ɾ�������Ӱ���������������������ͼ10.26��ʾ�������У����ѹؼ���ΪBroad�ı�������ɾ������������λ�õ�info����ΪEmpty����ô�Ժ��������ؼ���ΪBlum��Alton�ı���ʱ�Ͳ鲻��ȥ���Ӷ��������жϱ���û�йؼ���ΪBlum��Alton�ı����������ɾ��һ������ʱ��ֻ�ܸ�����һ��ɾ�����deleted�������߼�ɾ�������������ĸ������ǣ���ִ�ж��ɾ���󣬱����Ͽ�����ɢ�б������ʵ���������λ��û�����á���ˣ���ɢ�б����䶯ʱ����ò��ñ�ɢ�з�������������ɸ��ÿ�ɢ�з��������������
//	�������ɢ�б�����һЩ������ʵ�֡�
		template <class Type> void HashTable<Type>::MakeEmpty ( ) {		//���ɢ�б�
		   for ( int i=0; i<TableSize; i++) ht[i].info = Empty;
		   CurrentSize = 0;
		}

		template <class Type> const HashTable<Type> & HashTable<Type>::operator= ( const HashTable<Type> &ht2 ) {
		//���غ���������һ��ɢ�б�ht2
		   if ( this != &ht2 ) {
			 delete [ ] ht;  TableSize = ht2.TableSize;  AllocateHt ( );		//���·���Ŀ��ɢ�б�洢�ռ�
			 for ( int i=0; i<TableSize; i++ ) ht[i] = ht2.ht[i];			//��Դɢ�б���Ŀ��ɢ�б���
			 CurrentSize = ht2.CurrentSize;						//���͵�ǰ�������
		   }
		   return *this;									//����Ŀ��ɢ�б�ṹָ��
		}
      
		template <class Type> int HashTable<Type>::Insert (const Type & x ) {
		//��ht��������x�����ҵ����ٲ���, ��δ�ҵ�, ��������, ���ٲ���, �����������, ����0; ���ҵ�
		//λ�õı�־��Empty��Deleted, ���۱��Ƿ�����, x����, ����1��
		   int i = Find (x);
		   if ( i >= 0 ) return 0;					//�������и���, ���ٲ���
		   i++;
		     if ( i != -TableSize && ht[-i].info != Active ) {			//����������Ϊ�ղ���, iΪ����
			 ht[-i].Element = x;  ht[-i].info = Active;  CurrentSize++;		//����
			 return 1;									//���ز���ɹ���־1
		   }
		   else return 0; 									//����������, ���ز��ɹ���־
		}

		template <class Type> int HashTable<Type>::Remove ( const Type & x ) {
		//��ht����ɾ��Ԫ��x���������Ҳ���x, ����Ȼ�ҵ�x, �����Ѿ��߼�ɾ����, �򷵻�0, �����ڱ���ɾ��
		//Ԫ��x, ����1��
			int i = Find (x);
		   if ( i >= 0 ) 
		   {						//�ҵ�ҪɾԪ��, ���ǻԪ��
			 ht[i].info = Deleted;  CurrentSize--;					//���߼�ɾ����־, ������������ɾ��
			 return 1;									//ɾ���������, ���سɹ���־
		   }
		   else return 0;									//�����ޱ�ɾ����, ���ز��ɹ���־
		}
