//Main3-1.cpp 验证串HString类的成员函数
#include "C.h"
#include "HString.h"
void main()
{
	int i;
	char c, *p="God bye!", *q="God luck!";
	HString t, s(p),r("Good luck!");
	cout<<"串s为";
	s.StrPrint();
	cout<<"串r为";
	r.StrPrint();
	HString u(r);
	cout<<"串u为";
	u.StrPrint();
	t.StrAssign(p);
	cout<<"串t为";
	t.StrPrint();
	cout<<"t的串长为"<<t.StrLength()<<"，串空否？";
	cout<<boolalpha<<t.StrEmpty()<<endl;
	s.StrAssign(q);
	cout<<"串s为";
	s.StrPrint();
	i=s.StrCompare(t);
	if(i<0)
		c='<';
	else if(i==0)
		c='=';
	else
		c='>';
	cout<<"串s"<<c<<"串t"<<endl;
	r.Concat(t, s);
	cout<<"串t联接串s产生的串r为";
	r.StrPrint();
	s.StrAssign("oo");
	cout<<"串s为";
	s.StrPrint();
	t.StrAssign("o");
	cout<<"串t为";
	t.StrPrint();
	r.Replace(t, s);
	cout<<"把串r中和串t相同的子串用串s代替后，串r为";
	r.StrPrint();
	s.ClearString();
	cout<<"串s清空后，串长为"<<s.StrLength()<<"，串空否？";
	cout<<boolalpha<<s.StrEmpty()<<endl;
	r.SubString(s, 6, 4);
	cout<<"串s为从串r的第6个字符起的4个字符，长度为"<<s.StrLength()<<"，串s为";
	s.StrPrint();
	t.StrCopy(r);
	cout<<"由串r复制得串t，串t为";
	t.StrPrint();
	t.StrInsert(6, s);
	cout<<"在串t的第6个字符前插入串s后，串t为";
	t.StrPrint();
	t.StrDelete(1, 5);
	cout<<"从串t的第1个字符起删除5个字符后，串t为";
	t.StrPrint();
	cout<<t.Index(s, 1)<<"是从串t的第1个字符起，和串s相同的第一个子串的位置"<<endl;
	cout<<t.Index(s, 2)<<"是从串t的第2个字符起，和串s相同的第一个子串的位置"<<endl;
}

