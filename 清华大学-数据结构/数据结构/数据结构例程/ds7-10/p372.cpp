		int IsPrime ( int N ) {					//����N�Ƿ�����
		   for ( int i=3; i*i<=N; i+=2 )				//��N�ֽܷ�Ϊ���������ĳ˻�, ����һ��һ�� 
			 if ( N % i == 0 ) return 0;			//N������i, N��������
		   return 1;							//N������
		}

		int NextPrime ( int N ) {					//����һ��>N����������N >= 5
		   if ( N % 2 == 0 ) N++;				//ż����������
		   for ( ; !IsPrime (N); N+=2 );				//Ѱ������
		   return N;
		}

		template <class Type> class HashTable {				//ɢ�б���Ķ���
		public:
		   enum KindOfEntry { Active, Empty, Deleted };			//������� (� / �� / ɾ)
		   int Find ( const Type & x );				//��ɢ�б�������x
		   int IsEmpty ( ) { return !CurrentSize ? 1 : 0; }			//��ɢ�б�շ񣬿��򷵻�1 
		   int IsFull ( ) { return CurrentSize == TableSize ? 1 : 0; }	//��ɢ�б��������򷵻�1
		   int Insert ( const Type & x );
		   int Remove ( const Type & x );
		   int IsIn ( const Type & x );
		   int WasFound ( ) const { return LastFindOK;	}		//�����һ�������Ƿ�ɹ�
		   //�������к����붨��10.6��������̽��ɢ�б�����ͬ
		   HashTable ( int sz=DefaultSize ) : TableSize ( sz ) { AllocateHt ( );  CurrentSize = 0; }		//���캯��
		   ~HashTable ( ) { delete [ ] ht; }						//��������
		   const HashTable & operator = ( const HashTable & ht2 );		//���غ�������ֵ
		   int FindPos ( const Type & x ); 					//ɢ�к���: ���㺬x����ĳ�ʼͰ��
		   void MakeEmpty ( );								//��ɢ�б�Ϊ��

		private:
		   struct HashEntry {							//ɢ�б�ı����
		      Type Element;							//���������, ������Ĺؼ���
		      KindOfEntry info;							//����״̬: Active, Empty, Deleted
		      HashEntry ( ) : info (Empty ) { }					//����캯��
		      HashEntry ( const Type &E, KindOfEntry i = Empty ) : Element (E), info (i) { };
		   };
		   //enum { DefualtSize = 11; };
		   HashEntry *ht; 								//ɢ�б�洢����
		   int TableSize;								//���鳤�ȣ�Ҫ��������4k+3��������k������
		   int CurrentSize;								//��ռ��ɢ�е�ַ��Ŀ
		   int LastFindOK;							//�����һ�������ɹ��ɹ�, �򷵻�1
		   void AllocateHt ( ) { ht = new HashEntry[TableSize ]; }	//����ɢ�б�洢�ռ�ĺ���
		};
		template <class Type> int HashTable<Type>::Find ( const Type & x ) {
		//���к����� ����һɢ��λ�õĺ���
		   int i = 0,  odd = 0 ;								// iΪ̽�������odd�ǿ��ƼӼ���־
		   int CurrentPos = FindPos ( x );						//����ɢ�к�������x��ɢ�е�ַ
		   while ( ht[CurrentPos].info != Empty && ht[CurrentPos].Element != x ) {	//�����Ƿ�Ҫ�����
			 if ( !odd ) {									// odd == 0Ϊ(H0 + i2)%TableSize����
			   CurrentPos += 2*++i - 1;   odd = 1;				//����һ����Ͱ
		 	   while ( CurrentPos >= TableSize ) CurrentPos -= TableSize;	//ʵ��ȡģ
			 }
			 else {										// odd == 1Ϊ(H0 - i2)%TableSize����
			   CurrentPos -= 2*i-1;  odd = 0;					//����һ����Ͱ
			   while ( CurrentPos < 0 ) CurrentPos += TableSize; 		//ʵ��ȡģ
			 }
		   }
		   LastFindOK = ht[CurrentPos].info == Active;				//��������Ƿ������ɹ���Ϣ
		   return CurrentPos;								//����Ͱ��
		};

		template <class Type> int HashTable<Type>::Insert ( const Type & x ) {
		//��x���뵽ɢ�б���, ��x�ڱ����Ѵ���, �򷵻�0, ���򷵻�1��
		   int CurrentPos = Find (x);
		   if (LastFindOK ) return 0;						//�����ڱ����Ѿ�����, ���ټ���
		   ht[CurrentPos] = HashEntry ( x, Active );				//����x
		   if ( ++CurrentSize < TableSize/2) return 1;				//��ǰ����������1, ����������һ�뷵��
		   HashEntry *Oldht = ht;						//���ѿռ䴦��: ����ԭ����ɢ�б�
		   int OldTableSize = TableSize;
		   CurrentSize = 0;
		   TableSize = NextPrime ( 2 * OldTableSize );			//ԭ���С��2����ȡ����
		   AllocateHt ( );								//�����µĶ�����С�Ŀձ�
		   for (int i=0; i<OldTableSize; i++)					//ԭ����Ԫ������ɢ�е��±���
		      if ( Oldht[i].info == Active ) Insert ( Oldht[i].Element );	//�ݹ����
		   delete [ ] Oldht;
		   return 1;
		}

		template <class Type> int HashTable<Type>::IsIn ( const Type & x ) {
		//�ж�x�Ƿ���ɢ�б��С����ڱ���, �򷵻�1, ���򷵻�0��
		   int CurrentPos = Find ( x );
		   return LastFindOK;
		}

		template <class Type> int HashTable<Type>::Remove ( const Type & x ) {
		//��x��ɢ�б���ɾ������ɾ���ɹ�, �򷵻�1, ���򷵻�0��
		   int CurrentPos = Find (x);
		   if (!LastFindOK ) return 0;						//������ɢ�б���û��
		   ht[CurrentPos].info = Deleted;  return 1;				//��ɾ�����, ɾ���ɹ�
		}



		//������������̽�鷨
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
      
