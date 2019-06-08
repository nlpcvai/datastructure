const int MaxTerms = 100;

class Polynomial;						//多项式类的前视声明

class term { 							//多项式中项的类定义
	friend Polynomial;						//定义Polynomial类为term类的友元类
	private:
	float coef;							//系数
	int exp;							//指数
};

class Polynomial {

public:
	//在定义2.3中列出的多项式的公共操作
	//   ……
       Polynomial ( );						//返回多项式p(x)=0
		   int operator ! ( );						//若*this是零多项式, 则返回1, 否则返回0。
		   int Coef (int e);				//返回多项式*this中指数e的系数。
		   int LeadExp ( );					//返回多项式*this中最大的指数。
		   Polynomial Add (Polynomial poly);			//返回多项式*this与多项式poly的和。
		   Polynomial Mult (Polynomial poly);   	    //返回多项式*this与多项式poly的乘积。
		   void NewTerm (float c, int e);
		   float Eval ( float x);					//计算多项式*this在变量为x时的值。
private:

    static term termArray[MaxTerms];			//存放多项式的数组
    static int free;						//多项式有效项数的下一位置
    //要求在类定义之外定义：
    // term Polynomial::termArray[MaxTerms];
    // int Polynomial::free = 0;				//在termArray中下一个空闲位置

    int start, finish ;						//多项式开始与结束位置
};

#include <iostream.h>
void Polynomial::NewTerm ( float c, int e ) {
		//把一个新的项加到多项式C (x)中
    if ( free >= MaxTerms ) {
	cout << "Too many terms in polynomials" << endl;  return;
    }
    termArray[free].coef = c;	 termArray[free].exp = e;  free++;
}


Polynomial Polynomial::Add ( Polynomial B ) {
	//返回两个多项式A(x) {在*this中}与B(x)的和
    Polynomial C;   int a = start;   int b = B.start;   C.start = free;		//a, b分别为两多项式检测指针
    float c;									//c为结果多项式的存放指针
    while ( a <= finish && b <= B.finish )
	if ( termArray[a].exp == termArray[b].exp)  {	//比较对应项的指数
	     c = termArray[a].coef + termArray[b].coef;		//相等，系数相加
	     if ( c ) NewTerm ( c, termArray[a].exp );		//和不为0，建立新项
	     a++;  b++;
	}
	else if ( termArray[a].exp < termArray[b].exp ) {
	    NewTerm ( termArray[b].coef, termArray[b].exp );	//不等，建立新项
	    b++;
	}
	else if ( termArray[a].exp < termArray[b].exp ) {
	    NewTerm ( termArray[a].coef, termArray[a].exp ); 	//不等，建立新项
	    a++;
	}

    for ( ; a<=finish; a++ )							//加A(x)中剩余的项
	NewTerm ( termArray[a].coef, termArray[a].exp );
    for ( ; b<=B.finish; b++ )						//加B(x)中剩余的项
	NewTerm ( termArray[b].coef, termArray[b].exp );
    C.finish = free-1;
    return C;
}


