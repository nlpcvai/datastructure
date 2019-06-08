//Func7-2.cpp 定义模板<D>的实参SL及相应的I/O操作
struct SL
{
	struct
	{
		int key;
		int order;
	}rc;
	int next;
};
void Visit(SL* c)
{
	cout<<'('<<c->rc.key<<", "<<c->rc.order<<')';
}
void Visitn(SL* c)
{
	cout<<'('<<c->rc.key<<", "<<c->rc.order<<", "<<c->next<<')';
}
void InputFromFile(ifstream &f, SL &c)
{
	f>>c.rc.key>>c.rc.order;
}

