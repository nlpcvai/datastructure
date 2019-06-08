//Func6-4.cpp 定义模板<D>的实参Ot及相应的I/O操作
struct Ot
{
	int order;
};
void Visit(Record<Ot> c)
{
	cout<<'('<<c.key<<", "<<c.others.order<<')';
}
void InputFromFile(ifstream &f, Record<Ot> &c)
{
	f>>c.key>>c.others.order;
}
void InputKey(KeyType &k)
{
	cin>>k;
}

