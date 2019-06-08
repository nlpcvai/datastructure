#include "iostream.h"
#include "assert.h"
   const int NumVertices = 6;				//ͼ����󶥵����
   const int MAXINT=32767;
   class Graph {						//ͼ���ඨ��
   private:
      int n;
      int Edge[NumVertices][NumVertices];		//ͼ���ڽӾ���
      int dist[NumVertices];					//��ŴӶ���0����������������·������
      int path[NumVertices];					//��������·���ϸö����ǰһ����Ķ����
      int S[NumVertices];					    //����õ������·���ϵĶ���Ķ����
   public:
      void ShortestPath ( const int );
      int choose ( const int );
      void BestPath(ostream& os);
      void BellmanFord ( const int v );
      friend istream& operator >>(istream& strm, Graph & g);
   };

   void Graph::ShortestPath ( const int v ) {
   //G��һ������n������Ĵ�Ȩ����ͼ, �����ϵ�Ȩֵ��Edge[i][j]���������㷨������һ������: dist[j], 0 < j < n,
   //�ǵ�ǰ�󵽵ĴӶ���v������j�����·������, ͬʱ������path[j],	0 < j < n, ����󵽵����·����
      assert(((v<n) &&(v>=0)));
      for ( int i=0; i<n; i++) {				// dist��path�����ʼ��
	    dist[i] = Edge[v][i];					//�ڽӾ����v��Ԫ�ظ��Ƶ�dist��
	    S[i] = 0;						//��������·���Ķ��㼯�ϳ�ʼ��
	    if ( i != v && dist[i] < MAXINT ) path[i] = v;
	    else path[i] = -1;					//·����������ʼ��
      }
      S[v] = 1;  dist[v] = 0;					//����v���붥�㼯��
      for ( i=0; i<n-1; i++ ) {				//�Ӷ���vȷ��n-1��·��
	    int min = MAXINT;
	    int u = v;
	    for ( int j=0; j<n; j++ )				//ѡ��ǰ���ڼ���S�о������·���Ķ���u
	      if ( !S[j] && dist[j] < min ) { u = j;  min = dist[j]; }
	    S[u] = 1;						//������u���뼯��S, ��ʾ���������·����
	    for ( int w=0; w<n; w++ )			//�޸�
	      if ( !S[w] && Edge[u][w] < MAXINT && dist[u] + Edge[u][w] < dist[w] ) {
		    dist[w] = dist[u] + Edge[u][w];  path[w] = u;
	      }
      }
   }
   istream& operator >>(istream& strm, Graph & g)
   {
	strm>>g.n;
	    for (int i=0;i<g.n;i++)
	    {
		    for (int j=0;j<g.n;j++)
		    {
			    strm>> (g.Edge[i][j]);
		    }

	    }
	    return strm;

   }
   void Graph::BestPath(ostream& os)
   {
	   os<<"shortest dist:";
	   for (int i=0;i<n;i++)
	   {
	      os<<dist[i]<<" ";
	   }
	   os<<endl;
	   os<<"shortest path:";
	   for ( i=0;i<n;i++)
	   {
	      os<<path[i]<<" ";
	   }
	   os<<endl;
   }