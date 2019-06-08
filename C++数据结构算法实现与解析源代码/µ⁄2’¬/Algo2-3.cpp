//Algo2-3.cpp 算术表达式求值，输入负数要用(0-正数)表示
#include "C.h"
#include "SqStack.h"
template<typename T>class Evaluate
{
private:
	char Precede(char t1, char t2)
	{
		char f;
		switch(t2)
		{
		case'+':
		case'-':if(t1=='(' || t1=='#')
					f='<';
				else
					f='>';
				break;
		case'*':
		case'/':if(t1=='*' || t1=='/' || t1==')')
					f='>';
				else
					f='<';
				break;
		case'(':if(t1==')')
				{
					cout<<"括号不匹配"<<endl;
					exit(1);
				}
				else
					f='<';
				break;
		case')':switch(t1)
				{
				case'(':f='=';
						break;
				case'#':cout<<"缺乏左括号"<<endl;
						exit(1);
				default:f='>';
				}
				break;
		case'#':switch(t1)
				{
				case'#':f='=';
						break;
				case'(':cout<<"缺乏右括号"<<endl;
						exit(1);
				default:f='>';
				}
		}
		return f;
	}
	bool In(char c)
	{
		switch(c)
		{
		case'+':
		case'-':
		case'*':
		case'/':
		case'(':
		case')':
		case'#':return true;
		default:return false;
		}
	}
	T Operate(T a, char theta, T b)
	{
		switch(theta)
		{
		case'+':return a+b;
		case'-':return a-b;
		case'*':return a*b;
		default:return a/b;
		}
	}
public:
	T Expression(string s)
	{
		SqStack<char> OPTR(10);
		SqStack<T> OPND(10);
		s=s+'#';
		int a, b, d;
		int i=0;
		char c, x;
		OPTR.Push('#');
		c=s[i++];
		OPTR.GetTop(x);
		while(c!='#' || x!='#')
		{
			if(In(c))
			{
				switch(Precede(x, c))
				{
				case'<':OPTR.Push(c);
						if(i<s.length())
							c=s[i++];
						break;
				case'=':OPTR.Pop(x);
						if(i<s.length())
							c=s[i++];
						break;
				case'>':OPTR.Pop(x);
						OPND.Pop(b);
						OPND.Pop(a);
						OPND.Push(Operate(a, x, b));
				}
			}
			else
			{
				if(c>='0' && c<='9')
				{
					d=0;
					while(c>='0' && c<='9')
					{
						d=d*10+c-'0';
						if(i<s.length())
							c=s[i++];
					}
					OPND.Push(d);
				}
				else
				{
					cout<<"出现非法字符"<<endl;
					exit(1);
				}
			}
			OPTR.GetTop(x);
		}
		OPND.Pop(a);
		if(!OPND.StackEmpty())
		{
			cout<<"表达式不正确"<<endl;
			exit(1);
		}
		return a;
	}
};
void main()
{
	string s;
	Evaluate<int> e;
	cout<<"请输入算术表达式，负数要用(0-正数)表示"<<endl;
	cin>>s;
	cout<<'='<<e.Expression(s)<<endl;
}

