//Bank1.h 模拟银行排队机事件的类（Bank1类）
#ifndef _BANK1_H_
#define _BANK1_H_
#include "BankQueue.h"
class Bank1:public BankQueue
{
private:
	LinkQueue<QElemType> q;
	bool *chk;
	QElemType *customer;
	int ChuangKou()
	{
	 
		for(int i=0; i<Qn; i++)
			if(chk[i])
				return i;
		return i;
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
		if(e.OccurTime<CloseTime)
			ev.push(e);
		f.ArrivalTime=en.OccurTime;
		f.Duration=DurationTime;
		q.EnQueue(f);
		i=ChuangKou();
		if(i<Qn)
		{
			q.DeQueue(customer[i]);
			
			e.OccurTime=en.OccurTime+customer[i].Duration;
			e.NType=i;
			ev.push(e);
			chk[i]=0;
		}
	}
	void CustomerDeparture()
	{
		Event e;
		int i;
		i=en.NType;
		chk[i]=true;
		TotalTime+=en.OccurTime-customer[i].ArrivalTime;
		
		if(!q.QueueEmpty())
		{
			q.DeQueue(customer[i]);
			
			chk[i]=false;
			e.OccurTime=en.OccurTime+customer[i].Duration;
			
			e.NType=i;
			ev.push(e);
		}
	}
public:
	Bank1(int n=2, int k=480, int i=8, int j=20)
	{
	 
		Initialize(n, k, i, j);
		cha="窗口数";
		chk=new bool[Qn];
		customer=new QElemType[Qn];
		
		for(int m=0; m<Qn; m++)
			chk[m]=true;
	}
	~Bank1()
	{
		delete[]chk;
		delete[]customer;
	}
};
#endif

