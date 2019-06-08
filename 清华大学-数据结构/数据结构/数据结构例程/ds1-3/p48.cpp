class Polynomial {
		//对象: 是一个有序数对<ei, ai>的集合。其中,
		//ei是指数, ai是系数。在此定义中, 设定指数是大于等于零的整数。
		public:
		   Polynomial ( );						//返回多项式p(x)=0
		   int operator ! ( );						//若*this是零多项式, 则返回1, 否则返回0。
		   int Coef (int e);				//返回多项式*this中指数e的系数。
		   int LeadExp ( );					//返回多项式*this中最大的指数。
		   Polynomial Add (Polynomial poly);			//返回多项式*this与多项式poly的和。
		   Polynomial Mult (Polynomial poly);			//返回多项式*this与多项式poly的乘积。
		   float Eval ( float x);					//计算多项式*this在变量为x时的值。
		};


#include <iostream.h>
class power {							//计算幂值的类
		   double x;							//基数
		   int e;							//指数
		   double mul;						//乘幂的值
		public:
		   power (double val, int exp);				//构造函数
		   double get_power ( ) { return mul; }			//取幂值
		};

		power::power (double val, int exp) {			//构造函数
		   x = val;	  e = exp;   mul = 1.0;			//为对象的基数x及指数e赋值
		   if (exp == 0 ) return ;
		   for ( ; exp>0; exp--) mul = mul * x; 			//计算乘幂mul
}

void main ( ) {
		   power pwr ( 1.5, 3 );					//创建对象pwr，基数为1.5, 指数为2
		   cout << pwr.get_power ( ) << "\n";			//输出乘幂的值
}
