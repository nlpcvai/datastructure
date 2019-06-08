//Algo6-5.cpp 验证BTree类的成员函数
#include "C.h"
#include "C4-1.h"
const int EMPTY=0;
const int m=3;
const int N=12;
typedef int KeyType;
#include "BTree.h"
#include "Func6-4.cpp"
void main()
{
	Record<Ot> r;
	BTree<Ot> t;
	Result<Ot> u[4];
	int n, i;
	KeyType k;
	bool f;
	ifstream fin("F6-5.txt");
	fin>>n;
	for(i=0; i<n; i++)
	{
		InputFromFile(fin, r);
		f=t.InsertRecord(r);
		if(!f)
			cout<<"record[]中已有关键字为"<<r.key
			<<"的数据，或record[]中没有空位置无法插入。"<<endl;
	}
	fin.close();
	t.Print();
	cout<<endl<<"按关键字的顺序遍历B树t："<<endl;
	t.TraverseBTree(t.Root(), Visit);
	for(i=0; i<4; i++)
	{
		cout<<endl<<"请输入待查找数据的关键字：";
		InputKey(k);
		u[i]=t.SearchBTree(k);
		cout<<"u["<<i<<"].i="<<u[i].i<<" u["<<i<<"].tag="<<u[i].tag<<' ';
		if(u[i].tag)
			Visit(*(u[i].pt->recptr[u[i].i]));
		else
			cout<<"未找到关键字为"<<k<<"的数据。";
	}
	cout<<endl<<"请输入待删除数据的关键字：";
	InputKey(k);
	f=t.DeleteBTree(r, k);
	if(f)
		Visit(r);
	cout<<endl<<"按关键字的顺序遍历删除后的B树t："<<endl;
	t.TraverseBTree(t.Root(), Visit);
	cout<<endl;
	t.Print();
	cout<<endl;
}

