//Algo3-1.cpp 实现改进的KMP算法的程序
#include "C.h"
#include "HString.h"
void get_next(HString S, int next[])
{
	int i=1, j=0;
	HString subs1, subs2;
	next[1]=0;
	while(i<S.StrLength())
	{
		S.SubString(subs1, i, 1);
		S.SubString(subs2, j, 1);
		if(j==0 || subs1.StrCompare(subs2)==0)
		{
			++i;
			++j;
			S.SubString(subs1, i, 1);
			S.SubString(subs2, j, 1);
			if(subs1.StrCompare(subs2)!=0)
				next[i]=j;
			else
				next[i]=next[j];
		}
		else
			j=next[j];
	}
}
int Index_KMP(HString T, HString S, int pos, int next[])
{
 
	int i=pos, j=1;
	HString subs1, subs2;
	while(i<=T.StrLength()&&j<=S.StrLength())
	{
		T.SubString(subs1, i, 1);
		S.SubString(subs2, j, 1);
		if(j==0 || subs1.StrCompare(subs2)==0)
		{
			++i;
			++j;
		}
		else
			j=next[j];
	}
	if(j>S.StrLength())
		return i-S.StrLength();
	else
		return 0;
}
void main()
{
	int i, *p;
	HString s1("aaabaaaab"), s2("aaaab");
	cout<<"主串为";
	s1.StrPrint();
	cout<<"子串为";
	s2.StrPrint();
	p=new int[s2.StrLength()+1];
	get_next(s2, p);
	cout<<"子串的next数组为";
	for(i=1; i<=s2.StrLength(); i++)
		cout<<*(p+i);
	cout<<endl;
	i=Index_KMP(s1, s2, 1, p);
	if(i)
		cout<<"主串和子串在第"<<i<<"个字符处首次匹配"<<endl;
	else
		cout<<"主串和子串匹配不成功"<<endl;
}

