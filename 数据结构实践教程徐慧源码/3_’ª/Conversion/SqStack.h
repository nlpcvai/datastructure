//˳��ջ�ඨ��
template <class T> 
class SqStack
{
	private:
		T *base;//ջ��ָ��
		int top;//ջ��
		int stacksize;//ջ����
	public:
		SqStack(int m);//��������
		~SqStack(){delete [] base;top=0;stacksize=0;}//��������
		void Push(T x);//��ջ
		T Pop();//��ջ
		T GetTop();//��ȡջ��Ԫ��
		int StackEmpty();//��ջ��
		void ClearStack();//���ջ
		void StackTop();//����ջ��ָ��
		void StackTranverse();//��ʾջ��Ԫ��
};
//˳��ջ��ʵ��
template <class T>
SqStack<T>::SqStack(int m)
{
	
	base=new T[m];
	if(base==NULL) 
	{
		cout<<"ջ����ʧ�ܣ��˳�!"<<endl;
		exit(1);
	}
	stacksize=m;
	top=-1;
}

template <class T>
void SqStack<T>::Push(T x)
{//��ջ
	if(top==stacksize-1) throw "ջ�����޷���ջ";
	top++;
	base[top]=x;
}


template <class T>
T SqStack<T>::Pop()
{//��ջ
	T x;
	if(top==-1) throw "ջ�գ����ܳ�ջ";
	x=base[top--];
	return x;
}

template <class T>
T SqStack<T>::GetTop()
{//��ȡջ��Ԫ��
	if(top==-1) throw "ջ�գ�ջ����Ԫ��";
	return base[top];
}

template <class T>
int SqStack<T>::StackEmpty()
{//��ջ��
	if(top==-1) 
		return 1;
	else
		return 0;
}

template <class T>
void SqStack<T>::ClearStack()
{//���ջ
	top=-1;
}

template <class T>
void SqStack<T>::StackTop()
{//����ջ��ָ��
	cout<<"ջ��top= "<<top;
}

template <class T>
void SqStack<T>::StackTranverse()
{//��ջ�������ջ
	int i=top;
   while(i>=0)
     cout<<base[i--]<<'\t';
   cout<<endl;
 }