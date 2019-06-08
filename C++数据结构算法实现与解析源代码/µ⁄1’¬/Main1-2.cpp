//Main1-2.cpp T为用户自定义类型
#include "C.h"
#include "SqList.h"
struct Student
{
	string name;
	int score;
};
inline void printSt(Student* c)
{
	cout<<endl<<setw(6)<<c->name<<"："<<c->score;
}
inline void printName(Student* c)
{
	cout<<c->name;
}
bool equal(Student c1, Student c2)
{
	return c1.name==c2.name;
}
void main()
{
	bool i;
	int j=1;
	SqList<Student>L(5);
	ifstream fin("F1-1.txt");
	Student e, e0;
	while(!fin.eof())
	{
		fin>>e.name>>e.score;
		L.ListInsert(j++, e);
	}
	fin.close();
	cout<<"在L的表尾依次插入文件F1-1.txt中的数据后，表L=";
	L.ListTraverse(printSt);
	cout<<"L是否空？"<<boolalpha<<L.ListEmpty()<<"，表长=";
	cout<<L.ListLength()<<endl;
	L.GetElem(4, e);
	cout<<"第4个元素的值为";
	printSt(&e);
	cout<<endl;
	L.GetElem(j, e);
	i=L.PriorElem(e, equal, e0);
	if(i)
	{
		printName(&e);
		cout<<"的前驱为";
		printName(&e0);
		cout<<endl;
	}
	i=L.NextElem(e, equal, e0);
	if(i)
	{
		printName(&e);
		cout<<"的后继为";
		printName(&e0);
		cout<<endl;
	}
	i=L.ListDelete(3, e);
	if(i)
	{
		cout<<"删除第3个元素成功，其值为";
		printSt(&e);
	}
	cout<<"\n目前，表L=";
	L.ListTraverse(printSt);
	L.ClearList();
	cout<<"清空L后，L是否空？"<<boolalpha<<L.ListEmpty();
	cout<<"，表长="	<<L.ListLength()<<endl;
}

