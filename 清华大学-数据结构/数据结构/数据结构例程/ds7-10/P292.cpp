#include "P267e.cpp"
		template <class NameType, class DistType> 
			class AOVGraph :public Graph<NameType,DistType>
		{
		private:
			int *count;						//�������, ��¼����������		   
		public:
			AOVGraph ( const int sz=DefaultSize ) ;			
			void TopologicalSort ( );
			
		};
		template <class NameType, class DistType> 		
		AOVGraph<NameType,DistType>::AOVGraph ( const int sz=DefaultSize ) 
			{
		      count = new int[sz];					//�����������
			  for (int i=0;i<sz;i++) 
			    count[i]=0;
			  
			  for (i=0;i<NumVertices;i++)
			  {
				 Edge<NameType,DistType> *p=NodeTable[i].adj;
				 while (p)
				 {
					 count[p->dest]++;			  
					 p = p->link;
				 }

			  }

			};