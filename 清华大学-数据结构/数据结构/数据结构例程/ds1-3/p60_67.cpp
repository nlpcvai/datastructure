//Test is T60_67.cpp

#include <string.h>
#include <iostream.h>

const int maxLen = 128;			//字符串的最大长度

class String {
	//对象: 零个或多个字符的一个有限序列。
public:
    String ( const String & ob);		//复制构造函数, 由一个已有的字符串对象ob构造一个新字符串。
    String ( const char *init );		//构造函数, 构造一个最大长度为maxLen, 由init初始化的新字符串。
    String ( );					//构造函数, 构造一个最大长度为maxLen, 实际长度为0的字符串。
    ~String ( ) { delete [ ] ch, f; }		//析构函数，释放动态分配的串空间。
    int Length ( ) const { return curLen; }		//函数返回串*this的长度。
    int String::fastFind ( String & pat ) const;
    void String::fail ( );
    String &operator ( ) ( int pos, int len );
	 //当 0<=pos<=maxLen且0(len且pos+len<maxLen 时, 则在串*this中从pos所指出
	 //位置开始连续取len个字符组成子串返回。
    int operator == ( const String &ob ) const { return strcmp (ch, ob.ch) == 0; }
	 //判是否串相等。若串*this与ob相等, 则函数返回1, 否则函数返回0。
    int operator != ( const String &ob ) const { return strcmp (ch, ob.ch) != 0; }
	 //判是否串不相等。若串*this与ob不相等, 则函数返回1, 否则函数返回0。
    int operator ! ( ) const { return curLen == 0; }
	 //判是否串空。若串*this为空, 则函数返回1, 否则函数返回0。
    String &operator = ( const String & ob );
	 //串ob赋值给当前串*this
    String &operator += ( const String & ob );
	 //若 length(*this)+length(ob)<=maxLen, 则把串ob接在串*this后面。
    char &operator [ ] ( int i );
	 //取*this的第i个字符。
    int Find ( String &pat ) const;
	 //若串pat与串*this中的某个子串匹配, 则函数返回第1次匹配时子串在串*this中的
	 //位置。若串pat为空或在串*this中没有匹配子串, 则函数返回-1。
    friend ostream & operator << (ostream& out , String s);
private:
    int curLen, *f ;								//串的长度
    char *ch;									//串存放数组
};

#include <iostream.h>
#include <process.h>

String::String ( const String &ob ) {					//串复制构造函数
    ch = new char[maxLen+1];						//创建字符串数组
    if ( !ch ) { cout << "Allocation Error\n";  exit(1); }
    curLen = ob.curLen;							//串长度
    strcpy ( ch, ob.ch );							//串复制
}

String::String ( const char *init ) {						//串构造函数
    ch = new char[maxLen+1];						//创建字符串数组
    if ( !ch ) { cout << "Allocation Error\n";  exit(1); }
    curLen = strlen (init);							//串长度
    strcpy ( ch, init );								//串复制
}

String::String ( ) {								//串构造函数
    ch = new char[maxLen+1];						//创建字符串数组
    if ( !ch ) { cout << "Allocation Error\n";  exit(1); }
    curLen = 0;								//串长度
    ch[0] = '\0';								//空串
}

String &String::operator ( ) ( int pos, int len ) { 				//求子串
    String *temp = new String;						//创建一个空串
    if ( pos < 0 || pos+len-1 >= maxLen || len < 0 ) {			//参数不合理，不取子串
       temp->curLen = 0;  temp->ch[0] = '\0';
    }
    else {
	 if ( pos+len-1>=curLen ) len = curLen - pos;			//子串字符数不够，取一部分
	 temp->curLen = len;
	 for ( int i=0, j=pos; i<len; i++, j++ ) temp->ch[i] = ch[j];
	 temp->ch[len] = '\0';
    }
    return *temp;
}

String &String::operator = ( const String &ob )	{			//串重载操作: 串赋值
    if ( &ob != this ) {							//若两个串相等为自我赋值
	delete [ ] ch;								//删去当前串
	ch = new char [maxLen+1];						//重新分配，加一个字符放"\0"
	if ( ! ch ) {	cerr << "Out Of Memory!\n ";  exit (1);	}	//ch为空，分配失败
	curLen = ob.curLen;
	strcpy ( ch, ob.ch );							//复制
    }
    else  cout << "Attempted assignment of a String to itself!\n";
    return *this;
}

String &String::operator += ( const String &ob ) { 			//串重载操作: 串连接
    char * temp =ch;								//保存将要覆盖字符串的地址
    curLen += ob.curLen;							//结果串的长度
    ch = new char [maxLen+1];						//为结果串分配存储
    if ( ! ch ) { cerr << "Out Of Memory!\n ";  exit (1) ; }
    strcpy ( ch, temp );							//结果串的前一部分
    strcat ( ch, ob.ch );							//结果串的后一部分
    delete [ ] temp;  return *this;						//释放旧存储，返回结果串
}

char &String::operator [ ] ( int i ) {					//取*this的第i个字符
    if ( i < 0 && i >= curLen ) { cout << "Out Of Boundary!\n ";  exit (1) ; }
    return ch[i];
}

int String::Find ( String &pat ) const {

//若在串s(*this)中找不到与串pat匹配的子串, 则函数返回
//-1, 否则返回pat在*this中第一次匹配的位置。
     char *p = pat.ch, *s = ch;  int i = 0;		//i是开始位置
     if ( *p && *s )					//两个串均不空
	while ( i <= curLen - pat.curLen )
	     if ( *p++ == *s++ ) {
		  if ( !*p ) return i;	  		//串pat扫描完, *p = 0
	     }						//匹配成功
	     else { i++;  s = ch+i;  p = pat.ch; }		//不匹配
	     //s指针进1, p指针回到开始位置做下一趟比较
     return -1;			//pat为空或在s中找不到它   		  图2.14  程序2.13的匹配过程
}

int String::fastFind ( String & pat ) const {
     int posP = 0,  posT = 0;					//两个串的扫描指针
     int lengthP = pat.curLen,  lengthT = curLen;			//模式与目标串的长度
     while ( posP < lengthP && posT < lengthT )			//对两串扫描
	 if ( pat.ch[posP] == ch[posT] ) {				//对应字符匹配
	    posP++;  posT++;
	 }
	 else if ( posP == 0 ) posT++;
	      else posP = pat.f [posP-1]+1;
     if ( posP < lengthP ) return -1;					//匹配失败
     else return posT - lengthP;					//匹配成功
}

void String::fail ( ) {								//对模式p(*this), 计算失效函数
    int lengthP = curLen;
    f [0] = -1;
    for ( int j=1; j<lengthP; j++ ) {					//计算f [j]
	int i = f [j-1];
	while ( *(ch+j) != *(ch+i+1) && i >= 0 ) i = f [i];		//递推计算f [j]
	if ( *(ch+j) == *(ch+i+1) ) f [j] = i+1;
	else f [j] = -1;
    }
}

ostream & operator << ( ostream & out, String s ) {
    if ( s.curLen == 0 ) out << "It is empty!";
    else {
	 for (int i=0 ; i < s.curLen ; i++ ) out << s.ch[i];
    }
    return out;
}
