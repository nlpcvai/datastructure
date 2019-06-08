//�ļ���:exap3-6.cpp
#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
int cont=0;			//��¼�����
typedef struct
{	
	int col[MaxSize];	//col[i]��ŵ�i���ʺ���к�
	int top;			//ջ��ָ��
} StType;				//����˳��ջ����
int count=0;
bool place(StType st,int i,int j)  //����(i,j)�Ƿ���1��i-1�ʺ��г�ͻ
{
	int k=1;
	if (i==1) return true;	//�ŵ�һ���ʺ�ʱû�г�ͻ
	while (k<=i-1)			//j=1��k-1���ѷ����˻ʺ����
	{
		if ((st.col[k]==j)  
			|| (abs(j-st.col[k])==abs(k-i)))
			return false;
		k++;
	}
	return true;
}
void queen(int n)					//���n�ʺ�����
{
	int i,j,k;
	bool find;
	StType st;						//����ջst
	st.top=0;						//��ʼ��ջ��ָ��
	st.top++;						//��(1,1)��ջ
	st.col[st.top]=1;
	while (st.top>0)				//ջ����ʱѭ��
	{
		i=st.top;					//��ǰ�ʺ�Ϊ��i���ʺ�
		if (st.top==n)				//���лʺ���ź�,���һ����
		{
			printf("  ��%d���⣺",++count);
			for (k=1;k<=st.top;k++)
				printf("(%d,%d) ",k,st.col[k]);
			printf("\n");
		}
		find=false;
		for (j=1;j<=n;j++)
			if (place(st,i+1,j))	//��i+1���ҵ�һ���Żʺ��λ��(i+1,j)
			{
				st.top++;
				st.col[st.top]=j;
				find=true;
				break;
			}
		if (find==false)			//��i+1���Ҳ����Żʺ��λ��,����
		{
			while (st.top>0)
			{
				if (st.col[st.top]==n)	//����û�пɷ�λ��,��ջ
					st.top--;
				for (j=st.col[st.top]+1;j<=n;j++)	//�ڱ�������һ��λ��
					if (place(st,st.top,j))
					{
						st.col[st.top]=j;
						break;
					}
				if (j>n)				//��ǰ�ʺ��ڱ���û�пɷŵ�λ��
					st.top--;			//��ջ
				else					//�����ҵ�һ��λ�ú��˳�����
					break;
			}
		}
	}
}

void main()
{
	int n;						//n���ʵ�ʻʺ����
	printf(" �ʺ�����(n<20) n=");
	scanf("%d",&n);
	if (n>20)
		printf("nֵ̫��,�������\n");
	else
	{	printf(" %d�ʺ�����������£�\n",n);
		queen(n);
		printf("\n");
	}
}

