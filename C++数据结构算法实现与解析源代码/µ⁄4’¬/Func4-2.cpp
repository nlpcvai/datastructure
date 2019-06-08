//Func4-2.cpp 定义数据元素类型和关键字类型及对它们的I/O操作
typedef int KeyType;
struct T
{
	KeyType key;
	int others;
};
void Visit(BiTNode<T> *c)
{
	cout<<'('<<c->data.key<<", "<<c->data.others<<')';
}
void InputFromFile(ifstream &f, T &c)
{
	f>>c.key>>c.others;
}
void InputKey(KeyType &k)
{
	cin>>k;
}

