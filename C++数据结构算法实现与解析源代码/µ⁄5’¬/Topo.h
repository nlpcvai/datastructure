//Topo.h 拓扑类（Topo类）
#ifndef _TOPO_H_
#define _TOPO_H_
#include "AdjListGraph.h"
template<typename VerT, typename ArcT>class Topo:public AdjListGraph<VerT, ArcT>
{
private:
	int *indegree;
	void FindInDegree()const
	{
		int i;
		list<AdjListGraph<VerT, ArcT>::ArcTNode>::const_iterator p;
		for(i=0; i<vexs.size(); i++)
			indegree[i]=0;
		for(i=0; i<vexs.size(); i++)
			for(p=vexs[i].arcs.begin(); p!=vexs[i].arcs.end(); p++)
			
				indegree[p->adjvex]++;
	}
	bool TopologicalOrder(stack<int> &T)
	{
	 
	 
		int i, k, count=0;
		stack<int> S;
		list<AdjListGraph<VerT, ArcT>::ArcTNode>::const_iterator p;
		indegree=new int[vexs.size()];
		FindInDegree();
		cout<<"一个拓扑序列：";
		for(i=0; i<vexs.size(); ++i)
			if(indegree[i]==0)
				S.push(i);
		for(i=0; i<vexs.size(); ++i)
			vexs[i].vex.ve=0;
		while(!S.empty())
		{
			i=S.top();
			S.pop();
			Visit(vexs[i].vex);
			T.push(i);
			++count;
			for(p=vexs[i].arcs.begin(); p!=vexs[i].arcs.end(); p++)
			{
				k=p->adjvex;
				if(--indegree[k]==0)
					S.push(k);
				if(vexs[i].vex.ve+p->arc.weight>vexs[k].vex.ve)
					
					vexs[k].vex.ve=vexs[i].vex.ve+p->arc.weight;
					
			}		
		}
		if(count<vexs.size())
		{
			cout<<"此有向带权图有回路"<<endl;
			return false;
		}
		else
			return true;
	}
public:
	Topo()
	{
		indegree=NULL;
	}
	~Topo()
	{
		if(indegree!=NULL)
			delete[]indegree;
	}
	bool TopologicalSort()
	{
		int i, k, count=0;
		stack<int> S;
		list<AdjListGraph<VerT, ArcT>::ArcTNode>::const_iterator p;
		indegree=new int[vexs.size()];
		FindInDegree();
		for(i=0; i<vexs.size(); ++i)
			if(!indegree[i])
				S.push(i);
		while(!S.empty())
		{
			i=S.top();
			S.pop();
			cout<<vexs[i].vex.name<<" ";
			++count;
			for(p=vexs[i].arcs.begin(); p!=vexs[i].arcs.end(); p++)
			{
				k=p->adjvex;
				if(!(--indegree[k]))
					S.push(k);
			}
		}
		if(count<vexs.size())
		{
			cout<<"此有向图有回路"<<endl;
			return false;
		}
		else
		{
			cout<<"为一个拓扑序列。"<<endl;
			return true;
		}
	}
	bool CriticalPath()
	{
		stack<int> S;
		int i, j;
		list<AdjListGraph<VerT, ArcT>::ArcTNode>::iterator p;
		bool f=TopologicalOrder(S);
		if(!f)
			return false;
		j=S.top();
		for(i=0; i<vexs.size(); i++)
			vexs[i].vex.vl=vexs[j].vex.ve;
		while(!S.empty())
		{
			j=S.top();
			S.pop();
			for(p=vexs[j].arcs.begin(); p!=vexs[j].arcs.end(); p++)
			{
				i=p->adjvex;
				if(vexs[i].vex.vl-p->arc.weight<vexs[j].vex.vl)
				
					vexs[j].vex.vl=vexs[i].vex.vl-p->arc.weight;
					
			}		
		}
		cout<<endl<<"i  name  ve  vl"<<endl;
		for(i=0; i<vexs.size(); i++)
		{
			cout<<i<<setw(3);
			Visitel(vexs[i].vex);
			if(vexs[i].vex.ve==vexs[i].vex.vl)
				cout<<" 关键路径经过的顶点";
			cout<<endl;
		}
		cout<<"j   i  权值  j最早发生时间  i最迟发生时间"<<endl;
		for(j=0; j<vexs.size(); ++j)
			for(p=vexs[j].arcs.begin(); p!=vexs[j].arcs.end(); p++)
			{
				i=p->adjvex;
				OutputArc(Directed, Weight, vexs[j].vex, vexs[i].vex, p->arc);
				cout<<setw(10)<<vexs[j].vex.ve<<setw(12)<<vexs[i].vex.vl;
				if(vexs[j].vex.ve+p->arc.weight==vexs[p->adjvex].vex.vl)
				
					cout<<" 关键活动";
				cout<<endl;
			}
		return true;
	}
};
#endif

