//Algo6-1.cpp 验证SqTable类的成员函数
#include "C.h"
#include "C4-1.h"
typedef long KeyType;
#include "SqTable.h"
#include "Func6-1.cpp"
void main()
{
	int i, j;
	SqTable<Sc> st[2];
	Sc e;
	KeyType key;
	char s[9]="F6-1.txt";
	for(i=0; i<2; i++)
	{
		s[3]=i+'1';
		st[i].Creat_SeqFromFile(s);
		cout<<"准考证号  姓名  语文 外语 数学 物理 总分"<<endl;
		st[i].Traverse(Total);
		st[i].Traverse(Visit);
		cout<<"请输入待查找人的考号：";
		InputKey(key);
		if(i==0)
			j=st[i].Search_Seq(key);
		else
			j=st[i].Search_Bin(key);
		if(j>0)
		{
			st[i].GetElem(j, e);
			Visit(&e);
		}
	}
}

