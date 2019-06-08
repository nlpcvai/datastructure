//Func5-4.cpp 定义一种MatrixGraph类中弧结构模板<ArcT>的实参A及对其的I/O操作
const int INFINITY=INT_MAX;
struct A
{
	VRType adj;
	
	string message;
};
void InputArc(A &arc)
{
	cout<<"请输入此弧的文字信息：";
	getline(cin, arc.message);
	getline(cin, arc.message);
}
void OutputArc(bool direct, V ver1, V ver2, A arc)
{
	string s="—";
	if(direct)
		s="→";
	cout<<ver1.name<<s<<ver2.name<<"：("<<arc.adj<<", "<<arc.message<<')'<<endl;
}
void InputArcFromFile(ifstream &f, A &arc)
{
	getline(f, arc.message, ' ');
	getline(f, arc.message);
}

