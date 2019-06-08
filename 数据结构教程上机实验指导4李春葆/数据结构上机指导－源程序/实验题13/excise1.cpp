//�ļ���:excise1.cpp
#include <stdio.h>
#include <malloc.h>
typedef struct
{
	int no;						//ְ����
	char name[10];				//����
	int depno;					//���ź�
	float salary;				//������
} EmpType;						//ְ������
typedef struct node
{
	EmpType data;				//���ְ����Ϣ
	struct node *next;			//ָ����һ���ڵ��ָ��
}  EmpList;						//ְ��������ڵ�����
void DelAll(EmpList *&L)		//���ְ���ļ���ȫ����¼
{
	FILE *fp;
	EmpList *p,*q;
	if ((fp=fopen("emp.dat","wb"))==NULL)	//��д���emp.dat�ļ�
	{	
		printf("  ��ʾ:���ܴ�ְ���ļ�\n");
		return;
	}
	fclose(fp);
	p=L->next;
	if (p!=NULL)
	{
		q=p->next;
		while (q!=NULL)
		{
			free(p);
			p=q;
			q=q->next;
		}
		free(p);
		L->next=NULL; 
	}
	else
		printf("  ��ʾ:�������κ�ְ����¼\n");
	printf("  ��ʾ:ְ������������\n");
}
void ReadFile(EmpList *&L)		//��emp.dat�ļ�����ְ��������L
{
	FILE *fp;
	EmpType emp;
	EmpList *p,*r;
	int n=0;
	L=(EmpList *)malloc(sizeof(EmpList));	//����ͷ�ڵ�
	r=L;
	if ((fp=fopen("emp.dat","rb"))==NULL) 
	{	
		 if ((fp=fopen("emp.dat","wb"))==NULL) 
			 printf("  ��ʾ:���ܴ���emp.dat�ļ�\n");
	}
	else		//����emp.dat�ļ�
	{
		while (fread(&emp,sizeof(EmpType),1,fp)==1)
		{	//����β�巨����������L
			p=(EmpList *)malloc(sizeof(EmpList));
			p->data=emp;
			r->next=p;
			r=p;
			n++;
		}
	}
	r->next=NULL;
	printf("  ��ʾ:ְ��������L�������,��%d����¼\n",n);
	fclose(fp);
}
void SaveFile(EmpList *L)	//��ְ�����������ݴ��������ļ�
{
	EmpList *p=L->next,*q;
	FILE *fp;
	if ((fp=fopen("emp.dat","wb"))==NULL) 
	{	
		printf("  ��ʾ:���ܴ����ļ�emp.dat\n");
		return;
	}
	while (p!=NULL)
	{
		fwrite(&p->data,sizeof(EmpType),1,fp);
		p=p->next;
	}
	fclose(fp);
	p=L;					//�ͷ�ְ��������
	q=p->next;
	while (q!=NULL)
	{
		free(p);
		p=q;
		q=q->next;
	}
	free(p);
	printf("  ��ʾ:����ְ����¼�ɹ�д�뵽emp.dat�ļ���\n");
}
void InputEmp(EmpList *&L)	//���һ��ְ����¼
{
	EmpList *p;
	printf("  >>����ְ����,����,���ź�,����:");
	p=(EmpList *)malloc(sizeof(EmpList));
	scanf("%d%s%d%f",&p->data.no,p->data.name,&p->data.depno,&p->data.salary);
	p->next=L->next;		//����ͷ�巨����ڵ�*p
	L->next=p;
}
void Sortno(EmpList *&L)	//����ֱ�Ӳ��뷨������L��no������������
{
	EmpList *p,*pre,*q;
	p=L->next->next;
	if (p!=NULL)
	{
		L->next->next=NULL;
		while (p!=NULL)
		{
			q=p->next;
			pre=L;
			while (pre->next!=NULL && pre->next->data.no<p->data.no)
				pre=pre->next;
			p->next=pre->next;
			pre->next=p;
			p=q;
		}
	}
	printf("  ��ʾ:��no�����������\n");
}
void Sortdepno(EmpList *&L) //����ֱ�Ӳ��뷨������L��depno������������
{
	EmpList *p,*pre,*q;
	p=L->next->next;
	if (p!=NULL)
	{
		L->next->next=NULL;
		while (p!=NULL)
		{
			q=p->next;
			pre=L;
			while (pre->next!=NULL && pre->next->data.depno<p->data.depno)
				pre=pre->next;
			p->next=pre->next;
			pre->next=p;
			p=q;
		}
	}
	printf("  ��ʾ:��depno�����������\n");
}
void Sortsalary(EmpList *&L) //����ֱ�Ӳ��뷨������L��salary������������
{
	EmpList *p,*pre,*q;
	p=L->next->next;
	if (p!=NULL)
	{
		L->next->next=NULL;
		while (p!=NULL)
		{
			q=p->next;
			pre=L;
			while (pre->next!=NULL && pre->next->data.salary<p->data.salary)
				pre=pre->next;
			p->next=pre->next;
			pre->next=p;
			p=q;
		}
	}
	printf("  ��ʾ:��salary�����������\n");
}
void Display(EmpList *L)	//�������ְ����¼
{
	EmpList *p=L->next;
	if (p==NULL)
		printf("  ��ʾ:û���κ�ְ����¼\n");
	else
	{
		printf("      ���  ����  ���ź�       ����\n");
		printf("   ----------------------------------\n");
		while (p!=NULL)
		{
			printf("  >>%3d%10s    %-8d%7.2f\n",p->data.no,p->data.name,p->data.depno,p->data.salary);
			p=p->next; 
		}
		printf("   ----------------------------------\n");
	}
}
void main()
{
	EmpList *L;
	int sel;
	printf("��emp.dat�ļ�����ְ��������L\n");
	ReadFile(L);
	do
	{	
		printf("1:���� 2:��ʾ 3:��no���� 4:��depno���� 5:��salary���� 9:ȫ�� 0:�˳� ��ѡ��:");
		scanf("%d",&sel);
		switch(sel)
		{
		case 9:
			DelAll(L);
			break;
		case 1:
			InputEmp(L);
			break;
		case 2:
			Display(L);
			break;
		case 3:
			Sortno(L);
			break;
		case 4:
			Sortdepno(L);
			break;
		case 5:
			Sortsalary(L);
			break;
		}
	} while (sel!=0);
	SaveFile(L);
}
