#include "iostream.h"
const int DefaultSize = 100;
class UFSets {								//�����еĸ����Ӽ��ϻ����ཻ��
public:
   UFSets ( int s = DefaultSize );					//���캯��
   ~UFSets ( ) { delete [ ] parent; }					//��������
   const UFSets & operator = ( UFSets const & Value );		//���غ��������ϸ�ֵ;ʡ��
   //��������
   void Union ( int Root1, int Root2 );					//�����Ӽ��Ϻϲ�
   int Find ( int x );							//��Ѱ����x�ĸ�
   //�Ľ�����
   void UnionByHeight ( int Root1, int Root2 );			//ѹ���߶ȵĺϲ��㷨,ʡ��
   void WeightedUnion ( int Root1, int Root2 );
   int CollapsingFind ( int i );
   friend ostream& operator <<(ostream& strm, UFSets& a);
private:
   int *parent;								//����Ԫ������ (��Ÿ�Ԫ�ص�˫�׽��ָ��)
   int size;									//����Ԫ�ص���Ŀ
};

UFSets::UFSets ( int s ) {
//���캯����s�Ǽ���Ԫ�ظ�����˫��ָ������ķ�ΧΪparent[0]��parent[size]��
   size = s;									//����Ԫ�ظ���
   parent = new int [size+1];						//����˫��ָ������
   for ( int i=0; i<=size; i++ ) parent[i] = -1;				//ÿһ���Գ�һ����Ԫ�ؼ���
}

int UFSets::Find ( int x ) {
//�������������ذ���Ԫ��x�����ĸ���
   if ( parent[x] < 0 ) return x;						//x�Ǹ�ʱֱ�ӷ���x
   else return Find ( parent[x] );						//����, �ݹ���x��˫�׵ĸ�
}

void UFSets::Union ( int Root1, int Root2 ) {
//�������������ཻ���ϵĲ���Ҫ��Root1��Root2�ǲ�ͬ��, �ұ�ʾ���Ӽ��ϵ����֡���Ϊunion��C++
//�Ĺؼ���, Ϊ���»���, ��ʹ��Set_Union������������
   parent[Root2] = Root1;				//����Root2���ӵ���һ��Root1����
}
void UFSets::WeightedUnion ( int Root1, int Root2 ) {
//ʹ�ý�����̽�鷽��������UF sets�ͼ��ϵĲ���Ҫ��Root1��Root2�ǲ�ͬ��, �ұ�ʾ���Ӽ��ϵ����֡�	
   Root1=CollapsingFind ( Root1 );
   Root2=CollapsingFind ( Root2 );
   int temp = parent[Root1] + parent[Root2];
   if ( parent[Root2] < parent[Root1] )					//��Root2Ϊ����������һЩ
     { parent[Root1] = Root2;  parent[Root2] = temp; }		//��Root1ֱ�ӽ���Root2����
   else { parent[Root2] = Root1;  parent[Root1] = temp; }		//��Root1��Ϊ�µĸ�
}

int UFSets::CollapsingFind ( int i ) {
//�ڰ���Ԫ��i������������, ������i������·
//���ϵ����н�㶼��ɸ�����Ů��				  ͼ7.11 ʹ���۵�����ѹ��·����ʾ��
   for ( int j=i; parent[j]>=0; j=parent[j]);		//������j
   while ( i != j ) {						//�������ѹ��
	 int temp = parent[i];
	 parent[i] = j;  i = temp;
  }
   return j;							//���ظ�
}
ostream& operator <<(ostream& strm, UFSets& a)
{
  for (int i=0;i<=a.size;i++)
  { 
    strm<<"Father of "<<i<<" is "<<a.parent[i]<<endl;
  }
  strm<<endl;
  return strm;
}