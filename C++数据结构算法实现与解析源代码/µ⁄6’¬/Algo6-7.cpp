//Algo6-7.cpp 验证TrieTree类的成员函数
const int MAX_KEY_LEN=16;
#include "C.h"
const int N=18;
const char Nil='$';
#include "TrieTree.h"
#include "Func6-5.cpp"
const int h=8;
void main()
{
	int i, n;
	bool f;
	K key;
	TrieTree<Ot> t;
	Record<Ot> r, *p;
	ifstream fin("F6-6.txt");
	fin>>n;
	for(i=0; i<n; i++)
	{
		InputFromFile(fin, r);
		f=t.InsertTrie(r);
		if(!f)
			cout<<"record[]中已有关键字为"<<r.key.ch
			<<"的数据，或record[]中没有空位置无法插入。"<<endl;
	}
	t.TraverseTrie(t.Root(), Out);
	t.Print(Out);
	cout<<"请输入待查找的关键字符串：";
	InputKey(key);
	p=t.SearchTrie(key);
	if(p!=NULL)
		Out(*p);
	else
		cout<<"不存在关键字为"<<key.ch<<"的数据";
	for(i=0; i<3; i++)
	{
		cout<<endl<<"请输入待删除的关键字符串：";
		InputKey(key);
		if(t.DeleteTrie(key, r))
		{
			cout<<"删除成功！其值为";
			Out(r);
		}
		else
			cout<<"删除失败！";
	}
	cout<<endl<<"按关键字符串的顺序遍历删除后的树t："<<endl;
	j=0;
	t.TraverseTrie(t.Root(), Out);
	cout<<endl;
	t.Print(Out);
	cout<<endl;
}

