//Func6-5.cpp 定义模板<D>的实参Ot及相应的I/O操作
struct Ot
{
	int order;
};
void Out(Record<Ot> c)
{
	cout<<'('<<c.key.ch<<", "<<c.others.order<<')';
}
void InputFromFile(ifstream &f, Record<Ot> &c)
{
	f>>c.key.ch>>c.others.order;
	c.key.num=strlen(c.key.ch);
}
int j=0;

