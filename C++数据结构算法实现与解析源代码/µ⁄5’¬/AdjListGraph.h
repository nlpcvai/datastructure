//AdjListGraph.h 图的邻接表类（AdjListGraph类）
#ifndef _ADJLISTGRAPH_H_
#define _ADJLISTGRAPH_H_
#include "AGraph.h"
template<typename VerT, typename ArcT>class Articul;
template<typename VerT, typename ArcT>class AdjListGraph:public AGraph<VerT>
{
	friend Articul<struct V, struct A>;
protected:
	struct ArcTNode
	{
		int adjvex;
		ArcT arc;
	};
	struct VerTNode
	{
		VerT vex;
		list<ArcTNode> arcs;
	};
	vector<VerTNode> vexs;
	int LocateVex(VerT u)const
	{
		for(int i=0; i<vexs.size(); i++)
			if EQ(u, vexs[i].vex)
				return i;
		return -1;
	}
public:
	AdjListGraph()
	{
		ArcNum=0;
	}
	VerT GetVex(int i)const
	{
		if(i>=vexs.size() || i<0)
			exit(1);
		return vexs[i].vex;
	}
	void CreateFromFile(char* FileName)
	{
		int i, j, k;
		VerT v1, v2;
		ArcTNode e;
		VerTNode v;
		ifstream fin(FileName);
		fin>>boolalpha>>Directed;
		fin>>boolalpha>>Weight;
		fin>>j;
		for(i=0; i<j; ++i)
		{
			InputVertexFromFile(fin, v.vex);
			
			vexs.push_back(v);
		}
		fin>>ArcNum;
		for(k=0; k<ArcNum; ++k)
		{
			InputVertexNameFromFile(fin, v1);
			InputVertexNameFromFile(fin, v2);
			i=LocateVex(v1);
			j=LocateVex(v2);
			e.adjvex=j;
			if(Weight)
				fin>>e.arc.weight;
			InputArcFromFile(fin, e.arc);
			vexs[i].arcs.push_front(e);
			if(!Directed)
			{
				e.adjvex=i;
				vexs[j].arcs.push_front(e);
			}
		}
		fin.close();
	}
	bool PutVex(VerT v, VerT value)
	{
		int k=LocateVex(v);
		if(k<0)
			return false;
		vexs[k].vex=value;
		return true;
	}
	void InsertVex(VerT v)
	{
		VerTNode vv;
		vv.vex=v;
		vexs.push_back(vv);
	}
	bool DeleteVex(VerT v)
	{
		int i, k;
		list<ArcTNode>::iterator p;
		k=LocateVex(v);
		if(k<0)
			return false;
		ArcNum-=vexs[k].arcs.size();
		vexs.erase(vexs.begin()+k);
		for(i=0; i<vexs.size(); i++)
		{
			for(p=vexs[i].arcs.begin(); p!=vexs[i].arcs.end(); p++)
				if(p->adjvex==k)
				{
					vexs[i].arcs.erase(p);
					if(Directed)
						ArcNum--;
					break;
				}
			for(p=vexs[i].arcs.begin(); p!=vexs[i].arcs.end(); p++)
				if(p->adjvex>k)
					p->adjvex--;
		}
		return true;
	}
	bool InsertArc(VerT v, VerT w)
	{
		ArcTNode e;
		int i, j;
		string s1="边", s2="—";
		i=LocateVex(v);
		j=LocateVex(w);
		if(i<0 || j<0)
			return false;
		ArcNum++;
		e.adjvex=j;
		InputArc(Directed, Weight, v, w, e.arc);
		vexs[i].arcs.push_front(e);
		if(!Directed)
		{
			e.adjvex=i;
			vexs[j].arcs.push_front(e);
		}
		return true;
	}
	bool DeleteArc(VerT v, VerT w)
	{
		list<ArcTNode>::iterator p;
		int i, j;
		i=LocateVex(v);
		j=LocateVex(w);
		if(i<0 || j<0 || i==j)
			return false;
		for(p=vexs[i].arcs.begin(); p!=vexs[i].arcs.end(); p++)
			if(p->adjvex==j)
			{
				vexs[i].arcs.erase(p);
				ArcNum--;
				break;
			}
		if(!Directed)
			for(p=vexs[j].arcs.begin(); p!=vexs[j].arcs.end(); p++)
				if(p->adjvex==i)
				{
					vexs[j].arcs.erase(p);
					break;
				}
		return true;
	}
	int FirstAdjVex(int i)const
	{
		list<ArcTNode>::const_iterator p=vexs[i].arcs.begin();
		if(p!=vexs[i].arcs.end())
			return p->adjvex;
		else
			return -1;
	}
	int NextAdjVex(int i, int j)const
	{
		list<ArcTNode>::const_iterator p;
		for(p=vexs[i].arcs.begin(); p!=vexs[i].arcs.end(); p++)
			if(p->adjvex==j)
			{
				p++;
				break;
			}
		if(p==vexs[i].arcs.end())
			return -1;
		else
			return p->adjvex;
	}
	void Display()const
	{
		int i;
		list<ArcTNode>::const_iterator p;
		string s1="无向", s2="无权图";
		if(Directed)
			s1="有向";
		if(Weight)
			s2="带权图";
		cout<<vexs.size()<<"个顶点"<<ArcNum<<"条弧的"<<s1<<s2<<"。顶点依次是：";
		for(i=0; i<vexs.size(); ++i)
			Visit(vexs.at(i).vex);
		cout<<endl<<ArcNum<<"条弧："<<endl;
		for(i=0; i<vexs.size(); i++)
		{
			for(p=vexs[i].arcs.begin(); p!=vexs[i].arcs.end(); p++)
				if(Directed||i<p->adjvex)
					OutputArc(Directed, Weight, vexs[i].vex, vexs[p->adjvex].vex, p->arc);
			cout<<endl;
		}
	}
	int GetVexNumOrArcNum(int i)const
	{
		if(i==0)
			return vexs.size();
		else
			return ArcNum;
	}
};
#endif

