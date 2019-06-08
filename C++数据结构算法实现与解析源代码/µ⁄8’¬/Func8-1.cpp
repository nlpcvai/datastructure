//Func8-1.cpp 定义模板<D>的实参LD及相应的I/O操作
struct LD
{
	KeyType key;
	int order;
};
const int MIN=INT_MIN;
const int MAX=INT_MAX;
const int M=10;
void Visit(LD &c)
{
	cout<<'('<<c.key<<", "<<c.order<<')';
}
void InputFromFile(ifstream &f, LD &c)
{
	f>>c.key>>c.order;
}
void OutputFile(ofstream &f, LD c)
{
	f<<endl<<c.key<<' '<<c.order;
}

