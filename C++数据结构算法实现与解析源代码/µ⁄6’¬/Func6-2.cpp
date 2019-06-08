//Func6-2.cpp 定义静态树表类模板<D>的实参S及对其的I/O操作
struct S
{
	KeyType key;
	int weight;
	int sw;
};
void Visit(S* c)
{
	cout<<'('<<c->key<<", "<<c->weight<<')';
}
void VisitT(BiTNode<S>* c)
{
	cout<<'('<<c->data.key<<", "<<c->data.weight<<')';
}
void InputFromFile(ifstream &f, S &c)
{
	f>>c.key>>c.weight;
}
void InputKey(KeyType &k)
{
	cin>>k;
}

