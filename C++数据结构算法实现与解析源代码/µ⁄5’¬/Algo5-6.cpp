//Algo5-6.cpp 输出有向图的一个拓扑序列
#include "C5-1.h"
#include "Topo.h"
#include "Func5-1.cpp"
#include "Func5-5.cpp"
void main()
{
	Topo<V, A> t;
	t.CreateFromFile("F5-10.txt");
	t.Display();
	t.TopologicalSort();
}

