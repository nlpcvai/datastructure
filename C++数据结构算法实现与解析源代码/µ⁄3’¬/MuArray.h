//MuArray.h 多维数组的类（MuArray类）
#ifndef _MUARRAY_H_
#define _MUARRAY_H_
template<typename T>class MuArray
{
private:
	T *base;
	int dim;
	int *bounds;
	int *constants;
	bool Locate(va_list ap, int &off)const
	{
		int i, ind;
		off=0;
		for(i=0; i<dim; i++)
		{
			ind=va_arg(ap, int);
			if(ind<0 || ind>=bounds[i])
				return false;
			off+=constants[i]*ind;
		}
		return true;
	}
public:
	MuArray(int Dim, ...)
	{
		int elemtotal=1, i;
		va_list ap;
		assert(Dim>0);
		dim=Dim;
		bounds=new int[dim];
		assert(bounds!=NULL);
		va_start(ap, Dim);
		for(i=0; i<Dim; i++)
		{
			bounds[i]=va_arg(ap, int);
			
			assert(bounds[i]>0);
			elemtotal*=bounds[i];
		}	
		va_end(ap);
		base=new T[elemtotal];
		assert(base!=NULL);
		constants=new int[dim];
		assert(constants!=NULL);
		constants[dim-1]=1;
		for(i=Dim-2; i>=0; i--)
			constants[i]=bounds[i+1]*constants[i+1];
	}
	~MuArray()
	{
		delete[]base;
		delete[]bounds;
		delete[]constants;
	}
	bool Value(T &e, int n, ...)const
	{
		va_list ap;
		int off;
		va_start(ap, n);
		if(Locate(ap, off)==false)
			return false;
		e=*(base+off);
		return true;
	}
	bool Assign(T e, ...)const
	{
		va_list ap;
		int off;
		va_start(ap, e);
		if(Locate(ap, off)==false)
			return false;
		*(base+off)=e;
		return true;
	}
};
#endif

