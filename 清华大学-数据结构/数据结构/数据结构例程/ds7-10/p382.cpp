		const int PageSize = 2;						//һ��ҳ����������
		const int CharNum = 2;						//�ؼ����е��ַ�������������������
		struct TwoChars 
		{ 
			char str[CharNum]; 			
		};			//ÿ���ؼ��������ַ�
		struct page {								//ҳ�鹹��
		   int PgDepth;							//���ֹؼ���Ķ���λλ��, ���ֲ����
		   TwoChars Names[PageSize];					//�ؼ�������, ÿҳ�������ɵĹؼ������
		   int Count;							//�ڱ�ҳ���е�ʵ�ʹؼ�����Ŀ
		};
		typedef page *paddr;						//ҳ��ָ��
		int DicDepth;							//Ŀ¼���, �����ֲ����, ������WordSize
		paddr *Directory;


		int hash (  TwoChars  key ) {
		//ʹ��һ�����ȷֲ���ɢ�к����Թؼ���key���м���, ��������һ��������ĵ�ַ
		   int Sum = 0,  j = 0,  len = 0;
		   for ( int i=0; i<=CharNum; i++ ) 
			 if ( key.str[i] == '\0' || key.str[i] == '\n') break;
			 else len++; 					//����ؼ�����ַ���
		   if ( len % 2 == 1)				//���len������, �ڹؼ���β��һ�հ�, ʹlen��Ϊż��
			 { key.str[len+1] = key.str[len];  key.str[len] = ' ';  len++; }	
		   while ( j < len ) { 
			 Sum = ( Sum + 100 * key.str[j] + key.str[j+1] ) % 19937;  j += 2;
		   }   
		   return Sum;
		}

		unsigned int makeAddress ( const TwoChars & key , const int depth ) {			
		//���ɹؼ���keyת���ɵ�ɢ��ֵ��ָ���ĵͽ׶���λ��depth��ת���ɶ���λ���У� ��Ϊҳ���ַ���ء�
		   int hashval = hash ( key );			//���ؼ���ת����Ϊһ�����͵�ɢ��ֵ
		   unsigned int retval = 0,  mask = 1;		//�ۼӽ��λ���ó�ֵ����ȡ���λ�����ε�Ԫ
		   for ( int j=1; j<=depth; j++ ) {		//����ָ������λ��ѭ���� ��λת��
			 retval = retval << 1;				//�������һλ			 
			 retval = retval | mask;			//�����λƴ����			 
		   }
		   retval=retval&hashval;
		   return retval;
		}

		int operator ==(const TwoChars& left,const TwoChars& right)
		{
			return ((left.str[0]==right.str[0])&&(left.str[1]==right.str[1]));
		}

        inline unsigned int Power2(unsigned int n)
		{	
			return 1<<n;
		}

		void InitHash(void)
		{
			DicDepth=0;
			Directory=new paddr[1];
			Directory[0]=new page;
			Directory[0]->Count=0;
			Directory[0]->PgDepth=0;
		}
