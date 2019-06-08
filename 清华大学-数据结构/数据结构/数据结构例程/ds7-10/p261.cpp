		class Graph {
		//����: ��һ������ķǿռ��Ϻ�һ���߼��Ϲ���, ÿ������һ�����������ʾ��
		public:
		   Graph ( );
			//����һ���յ�ͼ��
		   void InsertVertex ( const Type & vertex );
			//��ͼ�в���һ������vertex, �ö���û����ߡ�
		   void InsertEdge ( const int v1, const int v2, int weight );
			//�����ɱߵ���������v1��v2��ͼ�еĶ���, ����ͼ�в���һ����(v1,v2)��
		   void RemoveVertex ( const int v );
			//����ɾ������ͼ�еĶ���, ��ɾȥ����v�����й��������ıߡ�
  		   void RemoveEdge ( const int v1, const int v2 );
			//�����ɱߵ���������v1��v2��ͼ�еĶ���, ����ͼ��ɾȥ��(v1,v2)��
		   int IsEmpty ( );
			//��ͼ��û�ж���, ��������1, ���򷵻�0��
		   Type GetWeight ( const int v1, const int v2 );
			//�������ر� (v1,v2) ��Ȩֵ��
		   int GetFirstNeighbor ( const int v );
			//��������λ��Ϊv�ĵ�һ���ڽӶ����λ��, ����Ҳ���, ��������-1��
		   int GetNextNeighbor ( const int v1, const int v2 );
			//��������λ��Ϊv1��ĳ�ڽӶ���v2����һ���ڽӶ����λ��, ����Ҳ���, �򷵻�-1��
		}

