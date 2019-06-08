//BankQueue.h 模拟银行队列事件的基类（BankQueue类）
#ifndef _BANKQUEUE_H_
#define _BANKQUEUE_H_
#include "LinkQueue.h"
class BankQueue
{
protected:
	struct QElemType
	{
		int ArrivalTime;
		int Duration;
	};
	struct Event
	{
		int OccurTime;
		int NType;
	};
	class cmp
	{
	public:
		bool operator()(const Event a, const Event b)const
		{
			return (a.OccurTime>b.OccurTime);
		}
	};
	int Qn, CustomerNum, CloseTime;
	int Khjg, Blsj;
	priority_queue<Event, vector<Event>, cmp> ev;
	Event en;
	long int TotalTime;
	string cha;
	void Initialize(int n, int k, int i, int j)
	{
	 
		Qn=n;
		CloseTime=k;
		Khjg=i;
		Blsj=j;
		TotalTime=0;
		CustomerNum=0;
		en.OccurTime=0;
		en.NType=Qn;
		ev.push(en);
	}
	void Random(int &d, int &i)
	{
		d=rand()%Blsj+1;
		i=rand()%(Khjg+1);
	}
	virtual void CustomerArrived()=0;
	virtual void CustomerDeparture()=0;
public:
	void Bank_Simulation()
	{
		while(!ev.empty())
		{
			en=ev.top();
			ev.pop();
			if(en.NType==Qn)
				CustomerArrived();
			else
				CustomerDeparture();
		}
		cout<<"两相邻到达的客户的时间间隔：0～"<<Khjg;
		cout<<"分钟，每个客户办理业务的时间：1～"<<Blsj<<"分钟"<<endl;
		cout<<cha<<"："<<Qn<<"，营业时长："<<CloseTime<<"分钟，客户总数：";
		cout<<CustomerNum<<"，所有客户共耗时："<<TotalTime<<"分钟"<<endl;
		cout<<"平均每人耗时："<<TotalTime/CustomerNum;
		cout<<"分钟，最后一个客户离开的时间："<<en.OccurTime<<"分"<<endl;
	}
};
#endif

