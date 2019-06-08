//Algo3-2.cpp 用类实现BM算法的程序
#include "C.h"
#include "HString.h"
const int N=256;
class BMMatching
{
private:
	HString Main, Sub;
	bitset<N> bit;
	void MakeBitSet()
	{
		int i;
		for(i=0; i<Sub.length; i++)
			bit[(unsigned char)Sub.ch[i]]=1;
	}
	int last(char c)
	{
		if(bit[(unsigned char)c]==0)
			return -1;
		else
			for(int i=Sub.length-1; i>=0; i--)
				if(c==Sub.ch[i])
					return i;
	}
public:
	BMMatching(const char* strM="", const char* strS="")
	{
		Main.StrAssign(strM);
		Sub.StrAssign(strS);
		MakeBitSet();
	}
	int BMMatch()
	{
		int m, n, i, j;
		cout<<"主串为";
		Main.StrPrint();
		cout<<"模式串为";
		Sub.StrPrint();
		m=Sub.length;
		n=Main.length;
		j=m-1;
		i=m-1;
		do
		{
			if(Sub.ch[j]==Main.ch[i])
				if(j==0)
					return i+1;
				else
					i--, j--;
			else
			{
				i=i+m-__min(j, 1+last(Main.ch[i]));
				j=m-1;
			}
		}while(i<n);
		return 0;
	}
};
void main()
{
	BMMatching M1("The atom bomb is in this room.", "room");
	BMMatching M2("算法与数据结构", "数据");
	int i;
	i=M1.BMMatch();
	if(i)
		cout<<"主串和模式串在第"<<i<<"个字符处首次匹配"<<endl;
	else
		cout<<"主串和模式串匹配不成功"<<endl;
	i=M2.BMMatch();
	if(i)
		cout<<"主串和模式串在第"<<i<<"个字符处首次匹配"<<endl;
	else
		cout<<"主串和模式串匹配不成功"<<endl;
}

