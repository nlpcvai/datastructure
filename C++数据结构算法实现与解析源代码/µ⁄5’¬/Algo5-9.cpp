//Algo5-9.cpp 调用弗洛伊德类求每两点之间的最短路径
const int MAX_VERTEX_NUM=20;
#include "C5-1.h"
#include "Floyd.h"
#include "Func5-1.cpp"
#include "Func5-2.cpp"
void main()
{
	MatrixGraph<V, A> g;
	g.CreateFromFile("F5-13.txt");
	g.Display();
	Floyd<V, A> m(g);
	m.DisplayD();
	for(int i=0; i<g.GetVexNumOrArcNum(0); ++i)
		for(int j=0; j<g.GetVexNumOrArcNum(0); ++j)
			m.Path(i, j);
}

