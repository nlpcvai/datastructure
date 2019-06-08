//Algo5-10.cpp 调用弗洛伊德类求两城市之间最短距离的程序
const int MAX_VERTEX_NUM=26;
#include "C5-1.h"
#include "Floyd.h"
#include "Func5-1.cpp"
#include "Func5-2.cpp"
void main()
{
	int i, j, q=1;
	MatrixGraph<V, A> g;
	g.CreateFromFile("Map.txt");
	Floyd<V, A> m(g);
	cout<<"城市代码："<<endl;
	for(i=0; i<g.GetVexNumOrArcNum(0); i++)
	{
		cout<<setw(4)<<i<<g.GetVex(i).name<<' ';
		if(i%7==6)
			cout<<endl;
	}
	cout<<endl;
	while(q)
	{
		cout<<"请选择：1 查询两城市间的最短距离  0 结束"<<endl;
		cin>>q;
		if(q)
		{
			cout<<"请输入要查询的起点城市代码 终点城市代码：";
			cin>>i>>j;
			m.Path(i, j);
		}
	}
}

