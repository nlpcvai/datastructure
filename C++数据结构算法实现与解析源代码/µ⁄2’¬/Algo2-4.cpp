//Algo2-4.cpp 用递归函数和非递归函数求解汉诺塔问题
#include "C.h"
#include "SqStack.h"
class HANOI
{
private:
	struct HanioData
	{
		int	x;
		int y;
		int n;
	};
	HanioData hd;
	static int c;
	SqStack<HanioData> stack;
	inline void move(int x, int z, int n)const
	{
		cout<<"第"<<++c<<"步：将"<<n<<"号盘从"<<x<<"座移到"<<z<<"座"<<endl;
	}
public:
	void hanoi(int n, int x, int y, int z)const
	{
		if(n==1)
			move(x, z, 1);
		else
		{
			hanoi(n-1, x, z, y);
			
			move(x, z, n);
			hanoi(n-1, y, x, z);
			
		}
	}
	void hanoi(int n, int x, int y)
	{
		assert(n>0 && x>0 && x<4 && y>0 && y<4 && x!=y);
		hd.n=n;
		hd.x=x;
		hd.y=y;
		c=0;
		while(hd.n || !stack.StackEmpty())
		{
			while(hd.n)
			{
				hd.n--;
				stack.Push(hd);
				hd.y^=hd.x;
			}
			if(!stack.StackEmpty())
			{
				stack.Pop(hd);
				move(hd.x, hd.y, hd.n+1);
				hd.x^=hd.y;
			}
		}
	}
};
int HANOI::c=0;
void main()
{
	HANOI H;
	int n;
	int p[3]={1, 2, 3};
	cout<<"3个塔座为"<<p[0]<<"、"<<p[1]<<"、"<<p[2]<<"，圆盘最初在"<<p[0];
	cout<<"座，借助"<<p[1]<<"座移到"<<p[2]<<"座。请输入圆盘数：";
	cin>>n;
	cout<<"递归求解汉诺塔问题："<<endl;
	H.hanoi(n, p[0], p[1], p[2]);
	cout<<"非递归求解汉诺塔问题："<<endl;
	H.hanoi(n, p[0], p[2]);
}

