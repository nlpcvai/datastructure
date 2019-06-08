//Func4-1.cpp 数据元素类型为基本类型的I/O操作
void Visit(BiTNode<T> *c)
{
	cout<<c->data<<' ';
}
void InputFromFile(ifstream &f, T &c)
{
	f>>c;
}
void Input(T &c)
{
	cin>>c;
}

