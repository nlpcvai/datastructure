//Func7-1.cpp 定义模板<D>的实参ID及相应的I/O操作
struct ID
{
	KeyType key;
	int order;
};
void Visit(ID* c)
{
	cout<<'('<<c->key<<", "<<c->order<<')';
}
void InputFromFile(ifstream &f, ID &c)
{
	f>>c.key>>c.order;
}

