//Algo6-2.cpp 利用STL对无序数据进行查找的算法
#include "C.h"
#include "Func6-1.cpp"
static long c;
bool cmp(Sc e)
{
	return e.number==c;
}
void main()
{
	int length;
	vector<Sc> a;
	vector<Sc>::iterator ip;
	Sc e;
	ifstream fin("F6-1.txt");
	fin>>length;
	for(int i=0; i<length; i++)
	{
		InputFromFile(fin, e);
		a.push_back(e);
	}
	fin.close();
	cout<<"准考证号  姓名  语文 外语 数学 物理 总分"<<endl;
	for(ip=a.begin(); ip!=a.end(); ip++)
	{
		Total(ip);
		Visit(ip);
	}
	cout<<"请输入待查找人的考号：";
	InputKey(c);
	ip=find_if(a.begin(), a.end(), cmp);
	if(ip!=a.end())
		Visit(ip);
}

