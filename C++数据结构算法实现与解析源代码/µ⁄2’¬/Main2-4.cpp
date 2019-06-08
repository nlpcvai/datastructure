//Main2-4.cpp 验证顺序循环队列SqQueueCy<T>类的成员函数
#include "C.h"
#include "SqQueueCy.h"
typedef int T;
#include "Func1-1.cpp"
void main()
{
	bool i;
	T d;
	SqQueueCy<T> Q(3);
	for(int k=0; k<5; k++)
		assert(Q.EnQueue(k));
	cout<<"入队5个元素后，队列的元素依次为";
	Q.QueueTraverse(print);
	cout<<"是否空队列？"<<boolalpha<<Q.QueueEmpty();
	cout<<"。队列的长度为"<<Q.QueueLength()<<endl;
	Q.DeQueue(d);
	cout<<"出队了队头元素，其值为"<<d;
	i=Q.GetHead(d);
	if(i==true)
		cout<<"。新的队头元素是"<<d<<endl;
	Q.ClearQueue();
	cout<<"清空队列后，是否空队列？"<<boolalpha<<Q.QueueEmpty();
	cout<<"。队列的长度为"<<Q.QueueLength()<<endl;
}

