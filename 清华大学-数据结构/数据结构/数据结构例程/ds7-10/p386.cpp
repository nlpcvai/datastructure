#include "P384.cpp"

			void PageRemove ( const TwoChars & key, const paddr p )
			//��p��ָ��ҳ����ɾȥ�ؼ���key������˳����ɾ���㷨, �ɲο���2�¡�
			{
				for (int i=0;i<p->Count;i++)
					if (p->Names[i]==key)
					{
						p->Count--;
						p->Names[i]=p->Names[p->Count];
						return;
					}				
			}
     	   void combine ( unsigned int index ) {		
		   if ( DicDepth == 0 ) return;					   
		   int buddyid= buddy (index);					//���ҳ��Ķ����� ��ַ	
		   paddr p = Directory[index];						//indexҳ��ͻ��ҳ��ָ��
		   paddr s = Directory[buddyid];
		   if ( (buddyid>=0) && ((p->Count + s->Count) <= PageSize )) {
				//����ҳ����������ܹؼ�������Ƿ񳬳�һҳ����, δ����, �ϲ�ҳ��
			 			 
			 for ( int i=0; i<s->Count; i++ ) {				//�����������ȫ���Ƶ�indexҳ��			   
			   p->Names[p->Count] = s->Names[i];
			   p->Count++; 
			 }
			 delete s;   p->PgDepth--;					//�ͷŻ��ҳ��, indexҳ����ȼ�1
			 Directory[buddyid] = p;				

			 unsigned int DirSize = Power2(DicDepth);				//����Ŀ¼����
			 unsigned int NewDirSize = DirSize / 2;					//�������,�µ�Ŀ¼����
			 for ( i=0; i<NewDirSize; i++ )					//�ж��Ƿ�Ҫ����Ŀ¼
			   if ( Directory[i] != Directory[NewDirSize+i] ) return; 
															//�������Ŀ¼, ����������			 
			 paddr *NewDir = Directory;
			 DicDepth--;				//Ŀ¼��ȼ�1
			 Directory = new paddr[NewDirSize];			//������Ŀ¼
			 for ( i=0; i<NewDirSize; i++ ) Directory[i] = NewDir[i];
			 delete [ ] NewDir;
			 if (index<NewDirSize) combine ( index ); else combine(buddyid);							//�ݹ�, ���Ƿ�����ϲ� 
		   }
		}


		void Remove ( const TwoChars & key ) {				//������ɾȥ�ؼ���key
		   unsigned int id = makeAddress ( key, DicDepth );			//Ѱ�ҹؼ���key����ҳ��Ķ����Ƶ�ַ
		   paddr p = Directory [id];						//����key����ҳ��
		   if ( p ) {									//�ҵ�, p��ָ���ҳ���ָ��
			 PageRemove ( key, p );						//��p��ָҳ����ɾȥ�ؼ���key
			 combine ( id );							//�ж��Ƿ�ϲ�ҳ�������Ŀ¼
		   }
		}

		