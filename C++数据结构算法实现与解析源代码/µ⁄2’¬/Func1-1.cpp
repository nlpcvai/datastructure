//Func1-1.cpp 3个常用的函数
bool equal(int c1, int c2)
{
	return c1==c2;
}
bool equal(double c1, double c2)
{
	return abs(c1-c2)<1.0e-6;
}
inline void print(T* c)
{
	cout<<*c<<" ";
}

