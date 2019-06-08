#include "p382.cpp"
		int PageFind ( const TwoChars & key, const paddr PageNumber )
		//����ָ��PageNumber��ָ��ҳ���������ؼ���key, ����ҵ��򷵻�1, ���򷵻�0��
		//��Ϊ��ҳ���ڵ���������һ��Ϊ˳������, �㷨�����ر����, �ɲο�����9.1��
		{
			for (int i=0;i<PageNumber->Count;i++)
			{
				if (key==PageNumber->Names[i]) return 1;
			}
			return 0;
		};
		paddr Find ( const TwoChars & key ) {
		//���ļ����������йؼ���key�ļ�¼�����ҵ�, �򷵻ظü�¼����ҳ��ĵ�ַ; ��û���ҵ�, �򷵻� 0��
		   unsigned int id = makeAddress ( key, DicDepth );			//��key��DicDepth����Ŀ¼��ַ
		   paddr FoundPage;
		   FoundPage= Directory[id];					//��Ŀ¼���ҵ���Ӧҳ���ַ
		   if ( PageFind ( key, FoundPage ) ) return FoundPage;		//�ڸ�ҳ��������, �ҵ�����ҳ���ַ
		   else return 0;
		}



		void DirDouble ( ) {							//Ŀ¼�ɱ�������㷨
		   unsigned int CurrentSize = Power2(DicDepth);
		   
		   paddr *TmpDir = Directory;				//������ʱĿ¼		   
		   Directory = new paddr[2*CurrentSize];			//������Ŀ¼
		   for ( int i=0; i<CurrentSize; i++ )					//����ʱĿ¼����Ŀ¼����ҳ��ָ��
			 { Directory[i] = TmpDir[i];  Directory[CurrentSize+i] = TmpDir[i]; } 
		   DicDepth++;
		   delete [] TmpDir;
		}

		int buddy ( const unsigned int index ) {
		//����һ��ҳ��Ķ����Ƶ�ַindex�����ҳ��Ļ��Ķ����Ƶ�ַ, ǰ�˵Ķ���λ�ǻ����ġ�
		   if (DicDepth == 0 ) return 0;						//Ŀ¼���Ϊ0, û�л��
		   if ( Directory[index]->PgDepth < DicDepth ) 			//��ҳ��ľֲ����С��Ŀ¼���
			 return -1;								//û�л��
		   unsigned int mask = 1;						//��������
		   mask <<= DicDepth - 1;						//����DicDepth - 1λ, ��1�Ƶ����λ 
		   unsigned int buddyAddress = index ^ mask;			//��������, ����
		   return buddyAddress;
		}

		void ReDisTribute ( paddr PageNumber, paddr NewPage )
			//����ҳ�������йؼ������·ֲ�
		{
			int i=0;
			int CurrentSize=PageNumber->PgDepth;
			NewPage->Count=0;
			while (i<PageNumber->Count)
			{
				TwoChars key=PageNumber->Names[i];
				int NowPage=makeAddress ( key, CurrentSize );
				if (Directory[NowPage]==NewPage) 
				{
					NewPage->Names[NewPage->Count]=key;
					NewPage->Count++;

					PageNumber->Count--;
					PageNumber->Names[i]=PageNumber->Names[PageNumber->Count];
				}
				else
					i++;
			}
		}


		void Split ( const TwoChars key, paddr PageNumber ) {		//����ҳ��
		   int CurrentSize = DicDepth;						//�����ϵ�Ŀ¼��С
		   if ( PageNumber->PgDepth == DicDepth )			//ҳ����ȵ���Ŀ¼���ʱ
			 DirDouble( );							//ҳ����ѽ�����Ŀ¼�ɱ�����
		   paddr NewPage = new page;						//Ϊ���ҳ�����洢�ռ�
		   PageNumber->PgDepth ++;						//��ҳ��ľֲ���ȼ�1
		   unsigned int id = makeAddress ( key, CurrentSize );		//��key����DicDepth��������Ƶ�ַ
		   unsigned int bd = buddy ( id );					//�һ��ҳ��Ķ����Ƶ�ַ	
		   Directory [ bd ] = NewPage;						//�������ҳ���Ŀ¼��		   
		   NewPage->PgDepth = PageNumber->PgDepth;			//���ľֲ���ȵ�����ҳ��ľֲ����
		   ReDisTribute ( PageNumber, NewPage );				//����ҳ�������йؼ������·ֲ�
		} 

		int Add (const TwoChars & key ) ;

	   
		void Insert ( paddr PageNumber, const TwoChars & key ) {
		//���¹ؼ���key���뵽��PageNumberָ����ҳ���С�
		   if ( PageNumber->Count != PageSize ) {				//����ҳ���йؼ������δ��
			 PageNumber->Names [ PageNumber->Count ] = key;
			 PageNumber->Count++;						//ֱ�Ӳ���
		   }
		   else {									//����
			 Split ( key, PageNumber );						//��ҳ��һ��Ϊ��
			 Add ( key);								//����
		   }
		}


		int Add (const TwoChars & key ) {
		//��һ���¹ؼ���key���뵽Ŀ¼��ָ�����ļ��С�
		   paddr foundPage = Find ( key );					//��key���ļ�������
		   if ( foundPage ) return 0;						//���ҵ�, �򲻲���, ����������
		   Insert ( Directory[makeAddress ( key, DicDepth )], key );						//���ؼ���key����foundPageҳ��
		   return 1;
		}
