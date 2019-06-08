#include "iostream.h"
const int DefaultSize = 100;
class UFSets {								//集合中的各个子集合互不相交。
public:
   UFSets ( int s = DefaultSize );					//构造函数
   ~UFSets ( ) { delete [ ] parent; }					//析构函数
   const UFSets & operator = ( UFSets const & Value );		//重载函数：集合赋值;省略
   //基本例程
   void Union ( int Root1, int Root2 );					//两个子集合合并
   int Find ( int x );							//搜寻集合x的根
   //改进例程
   void UnionByHeight ( int Root1, int Root2 );			//压缩高度的合并算法,省略
   void WeightedUnion ( int Root1, int Root2 );
   int CollapsingFind ( int i );
   friend ostream& operator <<(ostream& strm, UFSets& a);
private:
   int *parent;								//集合元质数组 (存放各元素的双亲结点指针)
   int size;									//集合元素的数目
};

UFSets::UFSets ( int s ) {
//构造函数：s是集合元素个数。双亲指针数组的范围为parent[0]～parent[size]。
   size = s;									//集合元素个数
   parent = new int [size+1];						//创建双亲指针数组
   for ( int i=0; i<=size; i++ ) parent[i] = -1;				//每一个自成一个单元素集合
}

int UFSets::Find ( int x ) {
//函数搜索并返回包含元素x的树的根。
   if ( parent[x] < 0 ) return x;						//x是根时直接返回x
   else return Find ( parent[x] );						//否则, 递归找x的双亲的根
}

void UFSets::Union ( int Root1, int Root2 ) {
//函数求两个不相交集合的并。要求Root1与Root2是不同的, 且表示了子集合的名字。因为union是C++
//的关键码, 为不致混乱, 可使用Set_Union来命名函数。
   parent[Root2] = Root1;				//将根Root2连接到另一根Root1下面
}
void UFSets::WeightedUnion ( int Root1, int Root2 ) {
//使用结点个数探查方法求两个UF sets型集合的并。要求Root1与Root2是不同的, 且表示了子集合的名字。	
   Root1=CollapsingFind ( Root1 );
   Root2=CollapsingFind ( Root2 );
   int temp = parent[Root1] + parent[Root2];
   if ( parent[Root2] < parent[Root1] )					//以Root2为根的树结点多一些
     { parent[Root1] = Root2;  parent[Root2] = temp; }		//让Root1直接接在Root2下面
   else { parent[Root2] = Root1;  parent[Root1] = temp; }		//让Root1成为新的根
}

int UFSets::CollapsingFind ( int i ) {
//在包含元素i的树中搜索根, 并将从i到根的路
//径上的所有结点都变成根的子女。				  图7.11 使用折叠规则压缩路径的示例
   for ( int j=i; parent[j]>=0; j=parent[j]);		//搜索根j
   while ( i != j ) {						//向上逐次压缩
	 int temp = parent[i];
	 parent[i] = j;  i = temp;
  }
   return j;							//返回根
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