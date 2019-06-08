//Algo2-8.cpp 用递归函数和非递归函数求解背包问题
#include "C.h"
#include "SqStack.h"
class KNAP
{
private:
	int N;
	int *w;
	struct knapNode
	{
		int w;
		int state;
	};
	bool knap(int s, int n)
	{
		if(s==0)
			return true;
		if(s<0 || s>0 && n<1)
			return false;
		if(knap(s-w[n-1], n-1))
		{
			cout<<w[n-1]<<' ';
			return true;
		} 
		else return knap(s, n-1);
	}
public:
	KNAP(char* FileName)
	{
		ifstream fin(FileName);
		fin>>N;
		cout<<"物品件数="<<N<<"，每件重量：";
		w=new int[N];
		for(int i=0; i<N; i++)
		{
			fin>>w[i];
			cout<<w[i]<<' ';
		}
		fin.close();
	}
	~KNAP()
	{
		delete[]w;
	}
	bool knapByRecursion(int weigh)
	{
	 
		return knap(weigh, N);
	}
	bool KnapByStack(int weigh)
	{
		knapNode s;
		SqStack<knapNode> stack;
		bool k=false;
		s.w=weigh;
		s.state=0;
		stack.Push(s);
		while(!stack.StackEmpty())
		{
			stack.GetTop(s);
			while(s.w>=0 && (s.w<=0 || N>=stack.StackLength()))
			{
				if(s.w==0)
				{
					k=true;
					break;
				}
				else
				{
					s.w=s.w-w[N-stack.StackLength()];
					
					s.state=1;
					stack.Push(s);
				}
				stack.GetTop(s);
			}
			while(!stack.StackEmpty())
			{
				stack.Pop(s);
				if(s.state==0)
					return k;
				if(s.state==1)
					if(k==true)
						cout<<w[N-stack.StackLength()]<<' ';
					else
					{
						stack.GetTop(s);
						s.state=2;
						stack.Push(s);
						break;
					}
			}
		}
		return k;
	}
};
void main()
{
	KNAP k("F2-2.txt");
	int W;
	bool f;
	cout<<endl<<"请输入背包的承重量W：";
	cin>>W;
	f=k.knapByRecursion(W);
	if(!f)
		cout<<"递归无解。";
	cout<<endl;
	f=k.KnapByStack(W);
	if(!f)
		cout<<"非递归无解。";
	cout<<endl;
}

