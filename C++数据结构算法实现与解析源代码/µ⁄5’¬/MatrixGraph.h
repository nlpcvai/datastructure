//MatrixGraph.h 图的邻接矩阵类（MatrixGraph类）
#ifndef _MATRIXGRAPH_H_
#define _MATRIXGRAPH_H_
#include "AGraph.h"
template<typename VerT, typename ArcT>class MatrixGraph:public AGraph<VerT>
{
protected:
	int VexNum;
	VerT vexs[MAX_VERTEX_NUM];
	ArcT arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int LocateVex(VerT u)const
	{
		int i;
		for(i=0; i<VexNum; ++i)
			if EQ(u, vexs[i])
				return i;
		return -1;
	}
public:
	MatrixGraph()
	{
		VexNum=ArcNum=0;
	}
	void DestroyGraph()
	{
		for(int i=VexNum-1; i>=0; i--)
		
			DeleteVex(vexs[i]);
	}
	void CreateFromFile(char* FileName)
	{
		int i, j, k;
		VRType w=0;
		VerT v1, v2;
		ifstream fin(FileName);
		fin>>boolalpha>>Directed;
		fin>>boolalpha>>Weight;
		if(Weight)
			w=INFINITY;
		fin>>VexNum;
		for(i=0; i<VexNum; ++i)
			InputVertexFromFile(fin, vexs[i]);
		fin>>ArcNum;
		for(i=0; i<VexNum; ++i)
			for(j=0; j<VexNum; ++j)
				arcs[i][j].adj=w;
		if(Weight)
			for(i=0; i<VexNum; ++i)
				arcs[i][i].adj=0;
		if(!Weight)
			w=1;
		for(k=0; k<ArcNum; ++k)
		{
			InputVertexNameFromFile(fin, v1);
			InputVertexNameFromFile(fin, v2);
			if(Weight)
				fin>>w;
			i=LocateVex(v1);
			j=LocateVex(v2);
			arcs[i][j].adj=w;
			InputArcFromFile(fin, arcs[i][j]);
			if(!Directed)
				arcs[j][i]=arcs[i][j];
		}
		fin.close();
	}
	bool PutVex(VerT v, VerT value)
	{
		int k=LocateVex(v);
		if(k<0)
			return false;
		vexs[k]=value;
		return true;
	}
	void InsertVex(VerT v)
	{
		int i;
		VRType j=0;
		if(Weight)
			j=INFINITY;
		vexs[VexNum]=v;
		for(i=0; i<VexNum; i++)
			arcs[VexNum][i].adj=arcs[i][VexNum].adj=j;
		arcs[VexNum][VexNum].adj=0;
		VexNum++;
	}
	bool DeleteVex(VerT v)
	{
		int i, j, k;
		k=LocateVex(v);
		if(k<0)
			return false;
		for(i=0; i<VexNum; i++)
			DeleteArc(v, vexs[i]);
		if(Directed)
			for(i=0; i<VexNum; i++)
				DeleteArc(vexs[i], v);
		for(j=k+1; j<VexNum; j++)
			vexs[j-1]=vexs[j];
		for(i=0; i<VexNum; i++)
			for(j=k+1; j<VexNum; j++)
				arcs[i][j-1]=arcs[i][j];
		for(i=0; i<VexNum; i++)
			for(j=k+1; j<VexNum; j++)
				arcs[j-1][i]=arcs[j][i];
		VexNum--;
		return true;
	}
	bool InsertArc(VerT v, VerT w)
	{
		int i, j;
		i=LocateVex(v);
		j=LocateVex(w);
		if(i<0 || j<0)
			return false;
		ArcNum++;
		if(Weight)
		{
			cout<<"请输入此弧的权值：";
			cin>>arcs[i][j].adj;
		}
		else
			arcs[i][j].adj=1;
		InputArc(arcs[i][j]);
		if(!Directed)
			arcs[j][i]=arcs[i][j];
		return true;
	}
	bool DeleteArc(VerT v, VerT w)
	{
		int i, k;
		VRType j=0;
		if(Weight)
			j=INFINITY;
		i=LocateVex(v);
		k=LocateVex(w);
		if(i<0 || k<0 || i==k)
			return false;
		if(arcs[i][k].adj!=j)
		{
			arcs[i][k].adj=j;
			if(!Directed)
				arcs[k][i]=arcs[i][k];
			ArcNum--;
		}
		return true;
	}
	int FirstAdjVex(int i)const
	{
		VRType j=0;
		if(Weight)
			j=INFINITY;
		for(int k=0; k<VexNum; k++)
			if(i!=k && arcs[i][k].adj!=j)
				return k;
		return -1;
	}
	int NextAdjVex(int i, int j)const
	{
		VRType m=0;
		if(Weight)
			m=INFINITY;
		for(int k=j+1; k<VexNum; k++)
			if(i!=k && arcs[i][k].adj!=m)
				return k;
		return -1;
	}
	VerT GetVex(int i)const
	{
		if(i>=VexNum || i<0)
			exit(1);
		return vexs[i];
	}
	ArcT GetArc(int i, int j)const
	{
		return arcs[i][j];
	}
	void Display()const
	{
		int i, j;
		string s1="无向", s2="无权图";
		if(Directed)
			s1="有向";
		if(Weight)
			s2="带权图";
		cout<<VexNum<<"个顶点"<<ArcNum<<"条弧的"<<s1<<s2<<"。顶点依次是：";
		for(i=0; i<VexNum; ++i)
			Visit(GetVex(i));
		cout<<endl<<"arcs.adj："<<endl;
		for(i=0; i<VexNum; i++)
		{
			for(j=0; j<VexNum; j++)
				if(arcs[i][j].adj==INFINITY)
					cout<<setw(2)<<"∞"<<' ';
				else
					cout<<setw(2)<<arcs[i][j].adj<<' ';
			cout<<endl;
		}
		for(i=0; i<VexNum; i++)
			if(Directed)
			{
				for(j=0; j<VexNum; j++)
					if(i!=j && (!Weight && arcs[i][j].adj || Weight && arcs[i][j].adj!=
					INFINITY))
						OutputArc(Directed, vexs[i], vexs[j], arcs[i][j]);
						
			}
			else
				for(j=i+1; j<VexNum; j++)
					if(!Weight && arcs[i][j].adj || Weight && arcs[i][j].adj!=INFINITY)
						OutputArc(Directed, vexs[i], vexs[j], arcs[i][j]);
	}
	int GetVexNumOrArcNum(int i)const
	{
		if(i==0)
			return VexNum;
		else
			return ArcNum;
	}
};
#endif

