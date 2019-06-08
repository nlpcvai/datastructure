//Main2-1.cpp 验证顺序栈SqStack<T>类的成员函数
#include "C.h"
#include "SqStack.h"
typedef int T;
#include "Func1-1.cpp"
void main()
{
	int j;
	SqStack<T> S(3);
	T e;
	for(j=1; j<=5; j++)
		S.Push(j);
	cout<<"栈中元素由栈底到栈顶依次为";
	S.StackTraverse(print);
	S.Pop(e);
	cout<<"弹出的栈顶元素e="<<e;
	cout<<"。栈空否？"<<boolalpha<<S.StackEmpty()<<endl;
	S.GetTop(e);
	cout<<"新的栈顶元素e="<<e<<"，栈的长度为"<<S.StackLength()<<endl;
	S.ClearStack();
	cout<<"清空栈后，栈空否？"<<boolalpha<<S.StackEmpty()<<endl;
}

