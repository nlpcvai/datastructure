//BankN.h 模拟银行多队列排队事件的类（BankN类）
#ifndef _BANKN_H_
#define _BANKN_H_
#include "BankQueue.h"
class BankN:public BankQueue
{
private:
	LinkQueue<QElemType> *q;
	int Minimum()
	{
		int minlen, k=0;
		minlen=q[0].QueueLength();
		for(int i=1; i<Qn; i++)
			if(q[i].QueueLength()<minlen)
			{
				minlen=q[i].QueueLength();
				k=i;
			}
		return k;
	}
	void CustomerArrived()
	{
		Event e;
		QElemType f;
		int DurationTime, IntervalTime, i;
		
		++CustomerNum;
		Random(DurationTime, IntervalTime);
		
		e.OccurTime=en.OccurTime+IntervalTime;
		
		e.NType=Qn;
		i=Minimum();
		if(e.OccurTime<CloseTime)
			ev.push(e);
		f.ArrivalTime=en.OccurTime;
		f.Duration=DurationTime;
		q[i].EnQueue(f);
		if(q[i].QueueLength()==1)
		{
			e.OccurTime=f.ArrivalTime+f.Duration;
			
			e.NType=i;
			ev.push(e);
		}
	}
	void CustomerDeparture()
	{
		Event e;
		QElemType f;
		int i;
		i=en.NType;
		q[i].DeQueue(f);
		TotalTime+=en.OccurTime-f.ArrivalTime;
		
		if(!q[i].QueueEmpty())
		{
			q[i].GetHead(f);
			e.OccurTime=en.OccurTime+f.Duration;
			
			e.NType=i;
			ev.push(e);
		}
	}
public:
	BankN(int n=2, int k=480, int i=8, int j=20)
	{
	 
		Initialize(n, k, i, j);
		cha="队列数";
		q=new LinkQueue<QElemType>[Qn];
	}
	~BankN()
	{
		delete[]q;
	}
};
#endif

