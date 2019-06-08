//Algo5-7.cpp Çó¹Ø¼üÂ·¾¶
#include "C5-1.h"
#include "Topo.h"
#include "Func5-7.cpp"
#include "Func5-5.cpp"
void main()
{
	Topo<V, A> t;
	t.CreateFromFile("F5-11.txt");
	t.Display();
	t.CriticalPath();
}

