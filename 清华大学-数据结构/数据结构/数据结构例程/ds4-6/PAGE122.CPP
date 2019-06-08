	#include <iostream.h>
 //		#include "stdlib.h"
		enum EventType { Arrival, Departure };
		class Event {									//事件类定义
		public:
		   Event ( ); 								//构造函数
		   Event ( int t, EventType et, int cn, int tn, int wt, int st );		//构造函数
		   int GetTime ( ) const;							//取出到达或离开时间，视类型不同
		   EventType GetEventType ( ) const;					//取出事件类型
		   int GetCustomerID ( ) const;						//取出客户标识
		   int GetTellerID ( ) const;						//取出出纳窗口标识
		   int GetWaitTime ( ) const;						//取出等待时间
		   int GetServiceTime ( ) const;						//取出服务时间
		private:
		   int time;									//客户到达 | 离开时间
		   EventType eType;							//客户类型：Arrival | Departure
		   int customerID;								//客户标识，编号为1, 2, 3, …
		   int tellerID;								//出纳窗口标识，编号为1, 2, 3, …
		   int waitTime;								//客户等待时间
		   int serviceTime;								//客户服务时间
		};
		


struct TellerStatus {				//有关出纳窗口的信息的记录
		   int finishService;				//什么时候出纳窗口空闲
		   int totalCustomerCount;			//服务过的客户总数
		   int totalCustomerWait;			//客户总的等待时间
		   int totalService;					//总的服务时间
		};

		
#include <pqueue.h>
class Simulation {						//模拟类声明
		public:  
		   Simulation ( );						//构造函数
		   void RunSimulation ( );				//执行模拟
		   void PrintSimulationResults ( );			//打印状态
		private:
		   int simulationLength;					//模拟的时间长度
		   int numTellers;						//出纳窗口个数
		   int nextCustomer;					//下一位客户的编号
		   int arrivalLow, arrivalHigh;				//下一次到达的时间范围	
		   TellerStatus tstat [11];					//最多10个出纳窗口
		   PQueue<Event> pq;						//优先级队列
		   //RandomNumber rnd;					//用于到达和服务的时间
		   int NextArrivalTime ( );				//私有函数: 产生下一次到达的时间
		   int GetServiceTime ( );					//私有函数: 取得服务时间
		   int NextAvailableTeller ( );				//私有函数: 产生下一个可用的出纳窗口
		};
	Simulation::Simulation ( ) {							//构造函数
		   Event  firstEvent ( 0, Arrival, 1, 0, 0, 0 );					//第一个到达事件
		   for ( int i=1; i<=10; i++ ) {							//初始化出纳窗口信息
			 tstat[i].finishService = 0;
			 tstat[i].totalService = 0;
			 tstat[i].totalCustomerWait = 0;
			 tstat[i].totalCustomerCount = 0;
		   }
		   nextCustomer = 1;								//下一位客户编号从1开始
		   cout << "Enter the simulation time in minutes : ";
		   cin >> simulationLength;							//输入模拟时间长度(以分钟计)
		   cout << "Enter the number of bank tellers : ";
		   cin >> numTellers;								//输入出纳窗口个数
		   cout << "Enter the range of arrival time in minutes : ";
		   cin >> arrivalLow >> arrivalHigh;						//输入下一次到达的时间范围
		   cout << "Enter the range of service time in minutes : ";
		   cin >> serviceLow >> serviceHigh;						//输入服务的时间范围
		   pq.PQInsert ( firstEvent );
		}
