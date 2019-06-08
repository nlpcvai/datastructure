//HuffmanTree.h 赫夫曼树类（HuffmanTree类）
#ifndef _HUFFMANTREE_H_
#define _HUFFMANTREE_H_
#include "HuffmanNode.h"
template<typename T>class HuffmanTree
{
private:
	HTNode<T> *HT;
	T Sum;
	int N;
	int min(int i)const
	{
		int j, m;
		T k=Sum;
		for(j=0; j<i; j++)
			if(HT[j].weight<k && HT[j].parent<0)
			{
				k=HT[j].weight;
				m=j;
			}
		HT[m].parent=i;
		return m;
	}
	void CreateHT(char *FileName)
	{
		int m, i, s1, s2;
		ifstream fin(FileName);
		fin>>N;
		cout<<N<<"个权值依次是：";
		if(N<=1)
			return;
		m=2*N-1;
		HT=new HTNode<T>[m];
		assert(HT!=NULL);
		Sum=0;
		for(i=0; i<N; ++i)
		{
			fin>>HT[i].weight;
			cout<<HT[i].weight<<' ';
			Sum+=HT[i].weight;
			HT[i].parent=-1;
			HT[i].lchild=-1;
			HT[i].rchild=-1;
		}
		cout<<endl;
		fin.close();
		for(i=N; i<m; ++i)
			HT[i].parent=-1;
		for(i=N; i<m; ++i)
		{
			s1=min(i);
			s2=min(i);
			HT[i].lchild=s1;
			HT[i].rchild=s2;
			HT[i].weight=HT[s1].weight+HT[s2].weight;
		}
	}
	void HuffmanCodingLeaf()const
	{
		int i, p, c;
		string *HC=new string[N];
		assert(HC!=NULL);
		cout<<"从叶子到根逆向求得的赫夫曼编码为："<<endl;
		for(i=0; i<N; i++)
		{
			for(c=i, p=HT[i].parent; p>=0; c=p, p=HT[p].parent)
			
				if(c==HT[p].lchild)
					HC[i]='0'+HC[i];
				else
					HC[i]='1'+HC[i];
			cout<<HC[i]<<endl;
		}
		delete[]HC;
	}
	void HuffmanCodingRoot()const
	{
		string str="", *HC=new string[N];
		assert(HC!=NULL);
		int c=2*N-2;
		for(int i=0; i<=c; ++i)
			HT[i].weight=0;
		while(c>=0)
		{
			if(HT[c].weight==0)
			{
				HT[c].weight=1;
				if(HT[c].lchild!=-1)
				{
					c=HT[c].lchild;
					str=str+'0';
				}
				else
				{
					HC[c]=str;
					c=HT[c].parent;
					str=str.substr(0, str.length()-1);
				}
			}
			else if(HT[c].weight==1)
			{
				HT[c].weight=2;
				c=HT[c].rchild;
				str=str+'1';
			}
			else
			{
				c=HT[c].parent;
				str=str.substr(0, str.length()-1);
			}
		}
		cout<<"无栈非递归从根到叶子求得的赫夫曼编码为："<<endl;
		for(i=0; i<N; i++)
			cout<<HC[i]<<endl;
		delete[]HC;
	}
public:
	HuffmanTree()
	{
		HT=NULL;
	}
	void HuffmanCoding(char *FileName)
	{
		CreateHT(FileName);
		HuffmanCodingLeaf();
		HuffmanCodingRoot();
		delete[]HT;
		HT=NULL;
	}
};
#endif

