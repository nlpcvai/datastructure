//RLSMatrix.h 三元组行逻辑链接顺序表的类（RLSMatrix类）
#ifndef _RLSMATRIX_H_
#define _RLSMATRIX_H_
template<typename T>struct Triple
{
	int i, j;
	T e;
};
const int MAX_SIZE=100;
const int MAX_RC=20;
template<typename T>class RLSMatrix
{
private:
	Triple<T> data[MAX_SIZE+1];
	int rpos[MAX_RC+1];
	int row, col, num;
public:
	RLSMatrix()
	{
		row=col=num=0;
	}
	RLSMatrix(char* FileName)
	{
		CreateSMatrixFromFile(FileName);
	}
	bool CreateSMatrixFromFile(char* FileName="F3-1.txt")
	{
		int i, j;
		ifstream fin(FileName);
		fin>>row>>col>>num;
		if(num>MAX_SIZE || row>MAX_RC)
			return false;
		data[0].i=0;
		for(i=1; i<=num; i++)
		{
			fin>>data[i].i>>data[i].j>>data[i].e;
			
			if(data[i].i<1 || data[i].i>row || 
			   data[i].j<1 || data[i].j>col)
				return false;
			if(data[i].i<data[i-1].i || data[i].i==data[i-1].i 
			&& data[i].j<=data[i-1].j)
				return false;
		}
		fin.close();
		for(i=1; i<=row; i++)
			rpos[i]=1;
		for(i=1; i<=num; i++)
			for(j=data[i].i+1; j<=row; j++)
				rpos[j]++;
		return true;
	}
	void CopySMatrix(const RLSMatrix &M)
	{
		int i;
		row=M.row;
		col=M.col;
		num=M.num;
		for(i=0; i<=M.num; i++)
			data[i]=M.data[i];
		for(i=0; i<=M.row; i++)
			rpos[i]=M.rpos[i];
	}
	void TransposeSMatrix(const RLSMatrix &M)
	{
		int i, j, k, colm[MAX_RC+1];
		row=M.col;
		col=M.row;
		num=M.num;
		if(num)
		{
			for(i=1; i<=row; ++i)
				colm[i]=0;
			for(i=1; i<=num; ++i)
				++colm[M.data[i].j];
			rpos[1]=1;
			for(i=2; i<=row; ++i)
				rpos[i]=rpos[i-1]+colm[i-1];
			for(i=1; i<=row; ++i)
				colm[i]=rpos[i];
			for(i=1; i<=num; ++i)
			{
				j=M.data[i].j;
				k=colm[j]++;
				data[k].i=j;
				data[k].j=M.data[i].i;
				data[k].e=M.data[i].e;
			}
		}
	}
	bool AddSMatrix(const RLSMatrix &M, const RLSMatrix &N)
	{
		int p, q, up, uq;
		if(M.row!=N.row || M.col!=N.col)
			return false;
		row=M.row;
		col=M.col;
		num=0;
		for(int k=1; num<=MAX_SIZE && k<=M.row; ++k)
		{
			rpos[k]=num+1;
			p=M.rpos[k];
			q=N.rpos[k];
			if(k<M.row)
			{
				up=M.rpos[k+1];
				uq=N.rpos[k+1];
			}
			else
			{
				up=M.num+1;
				uq=N.num+1;
			}
			while(p<up && q<uq)
				if(M.data[p].j<N.data[q].j)
					data[++num]=M.data[p++];
				else if(M.data[p].j>N.data[q].j)
					data[++num]=N.data[q++];
				else
				{
					if(M.data[p].e+N.data[q].e!=0)
					{
						data[++num]=M.data[p];
						data[num].e+=N.data[q].e;
					}
					p++;
					q++;
				}
			while(p<M.rpos[k+1]&&p<=M.num)
				data[++num]=M.data[p++];
			while(q<N.rpos[k+1]&&q<=N.num)
				data[++num]=N.data[q++];
		}
		if(num>MAX_SIZE)
			return false;
		else
			return true;
	}
	bool SubtSMatrix(const RLSMatrix &M, RLSMatrix &N)
	{
		int i;
		bool f;
		RLSMatrix S, N1;
		N1.CopySMatrix(N);
		for(i=1; i<=N1.num; ++i)
			N1.data[i].e*=-1;
		f=S.AddSMatrix(M, N1);
		if(f)
		{
			row=S.row;
			col=S.col;
			num=S.num;
			for(i=0; i<=S.num; i++)
				data[i]=S.data[i];
			for(i=0; i<=S.row; i++)
				rpos[i]=S.rpos[i];
		}
		return f;
	}
	bool MultSMatrix(const RLSMatrix &M, RLSMatrix &N)
	{
		int i, j, q, p, up, uq;
		T Qs;
		RLSMatrix T;
		if(M.col!=N.row)
			return false;
		row=M.row;
		col=N.col;
		num=0;
		T.TransposeSMatrix(N);
		for(i=1; i<=row; i++)
			for(j=1; j<=col; j++)
			{
				Qs=0;
				p=M.rpos[i];
				q=T.rpos[j];
				if(i<M.row)
					up=M.rpos[i+1];
				else
					up=M.num+1;
				if(j<T.row)
					uq=T.rpos[j+1];
				else
					uq=T.num+1;
				while(p<up && q<uq)
					if(M.data[p].j<T.data[q].j)
						p++;
					else if(M.data[p].j>T.data[q].j)
					
						q++;
					else
						Qs+=M.data[p++].e*T.data[q++].e;
				if(Qs)
				{
					if(++num>MAX_SIZE)
						return false;
					data[num].i=i;
					data[num].j=j;
					data[num].e=Qs;
				}
			}
		return true;
	}
	void PrintSMatrix()const
	{
		int k=1;
		const Triple<T> *p=data+1;
		if(num==0)
			return;
		for(int i=1; i<=row; i++)
		{
			for(int j=1; j<=col; j++)
				if(k<=num && p->i==i && p->j==j)
				{
					cout<<setw(3)<<(p++)->e;
					k++;
				}
				else
					cout<<setw(3)<<0;
			cout<<endl;
		}
	}
};
#endif

