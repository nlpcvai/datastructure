//Func7-3.cpp 定义模板<D>的实参LR及相应的I/O操作
struct Rec
{
	KeyType key;
	string translation;
};
struct LR
{
	Rec rc;
	int next;
};
void Visit(LR* c)
{
	cout<<setiosflags(ios::left)<<setw(3)<<c->rc.key<<"：";
	cout<<setw(37)<<c->rc.translation<<endl;
}
void Visitn(LR* c)
{
	cout<<setiosflags(ios::left)<<setw(3)<<c->rc.key<<"：";
	cout<<setw(37)<<c->rc.translation<<' '<<"next="<<c->next<<endl;
}
void InputFromFile(ifstream &f, LR &c)
{
	f>>c.rc.key;
	getline(f, c.rc.translation);
}

