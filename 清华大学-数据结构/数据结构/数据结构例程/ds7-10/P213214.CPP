#include <assert.h>
#include <iostream.h>
const int DefaultSize = 100;
class Set {
//用位向量来存储集合元素。这些集合元素只具有整数类型, 集合元素的取值范围在0到MaxSetSize-1之间。
public:
   Set ( int MaxSetSize = DefaultSize );						//构造函数
   ~Set ( ) { delete [ ] bitVector; }						//析构函数
   void MakeEmpty ( ); 					 			//置空集合
   int AddMember ( const int x );						//加入新成员x
   int DelMember ( const int x );							//删除老成员x
   void operator = ( Set & right );						//集合right赋值给集合this
   void operator + ( Set & right );						//求集合this与集合right的并
   void operator * ( Set & right );						//求集合this与集合right的交
   void operator - ( Set & right );						//求集合this与集合right的差
   int Contains ( const int x );							//判元素x是否集合this的成员
   int SubSet ( Set & right );							//判集合this是否集合right的子集
   int operator == ( Set & right );						//判集合this与集合right是否相等
   friend ostream& operator <<(ostream& strm, Set& a);
private:
   int * bitVector;									//存储集合元素的位向量
   int MaxSize;									//向量大小
};

Set::Set (int MaxSetSize) : MaxSize (MaxSetSize) {				//构造函数
   assert ( MaxSize > 0 );								//检查参数的合理性
   bitVector = new int [MaxSize];						//分配一个整型数组给位向量
   assert ( bitVector != 0 );							//检查存储分配是否成功
   for ( int i=0; i<MaxSize; i++ ) bitVector[i] = 0;				//初始化为空集合
}

void Set::MakeEmpty ( ) { for ( int i=0; i<MaxSize; i++ ) bitVector[i] = 0; } 	//置空集合

int Set::AddMember ( const int x ) {						//把x加入到集合this中
   assert ( x >= 0 && x < MaxSize );						//检查x的合理性
   if ( ! bitVector[x] ) { bitVector[x] = 1;  return 1; }
   return 0;					//x所在的位原来为0, 表示x不在集合中加入, 在相应位置置1
}

int Set::DelMember ( const int x ) {						//把x从集合中删去
   assert ( x >= 0 && x < MaxSize );						//判断元素x的合理性
   if ( bitVector[x] ) { bitVector[x] = 0;  return 1; }
   return 0;					//若位向量在x处的值为1, 表示x在集合中该位置置0, 表示x删去
}

void Set::operator = ( Set & right ) {						//把集合right的值复制到集合this中
   assert ( MaxSize == right.MaxSize );     					//判断两集合的大小是否相等
   for ( int i=0; i<MaxSize; i++ ) bitVector[i] = right.bitVector[i];		//相等则位向量按位传送数据
}

void Set::operator + (Set & right ) {						//求两集合right与this的并
   assert ( MaxSize == right.MaxSize );						//判断两集合的大小是否相等
   for ( int i=0; i<MaxSize; i++ ) bitVector[i] = bitVector[i]|| right.bitVector[i];	//按位求"或"
}

void Set::operator * (Set & right ) {						//求两集合right与this的交
   assert ( MaxSize == right.MaxSize );						//判断两集合的大小是否相等
   for ( int i=0; i<MaxSize; i++) bitVector[i] = bitVector[i] && right.bitVector[i];	//按位求"与"
}

void Set::operator - ( Set & right ) {						//求集合this与集合right的差
   assert ( MaxSize == right.MaxSize );						//判断两集合的大小是否相等
   for ( int i=0; i<MaxSize; i++ ) bitVector[i] = bitVector[i] && ! right.bitVector[i];	//按位求"异或"
}

int Set::Contains ( const int x ) {		//测试元素x是否集合的成员。是则返回1, 否则返回0。
   assert ( x >= 0 && x < MaxSize );						//判断元素x是否合理
   return bitVector[x];								//合理则返回相关信息
}

int Set::operator == ( Set & right ) {	//测试集合this与集合right是否相等。若相等, 则函数返回1, 否则返回0。
   assert ( MaxSize == right.MaxSize );						//判断两集合的元素个数是否相等
   for ( int i=0; i<MaxSize; i++)							//相等则按位判断对应位是否相等
	 if ( bitVector[i] != right.bitVector[i] ) return 0;
   return 1;
}

int Set::SubSet (Set & right ) {		//若集合this是集合right的子集, 则函数返回1, 否则函数返回0。
   assert ( MaxSize == right.MaxSize );						//判断两集合的元素个数是否相等
   for ( int i=0; i<MaxSize; i++)							//相等再按位判断
	 if ( bitVector[i] && ! right.bitVector[i] ) return 0;
   return 1;					//this集合该位为1而right集合该位为0, 则返回0, 两集合不等
}
ostream& operator <<(ostream& strm, Set& a)
{

  for (int i=0;i<a.MaxSize;i++)
  if (a.bitVector[i])
  {
    strm<<i<<' ';
  }
  strm<<endl;
   return strm;
}