//Algo8-2.cpp 将无序的大文件F8-1.txt（数据个数=k*N）分成k个长度为N的有序子文件的程序
#include "C.h"
#include "C4-1.h"
typedef int KeyType;
#include "InsSort.h"
#include "Func8-1.cpp"
const int k=5;
const int N=3;
void main()
{
	int i, j;
	LD c;
	char s[7]="F0.txt";
	ifstream fin("F8-1.txt");
	
	for(i=0; i<k; i++)
	{
		s[1]=i+'0';
		ofstream fout(s);
		fout<<N;
		for(j=1; j<=N; j++)
		{
			InputFromFile(fin, c);
			OutputFile(fout, c);
		}
		fout.close();
	}
	fin.close();
	InsSort<LD> is[k];
	for(i=0; i<k; i++)
	{
		s[1]=i+'0';
		is[i].Creat_SeqFromFile(s);
		is[i].InsertSort();
		is[i].OutputToFile(s);
	}
}

