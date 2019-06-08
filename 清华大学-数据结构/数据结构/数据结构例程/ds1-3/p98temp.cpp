		#include <iostream.h>
		#define Pi 3.1415926

		class Point {
		friend ostream &operator << (ostream &, const Point &);
		public:
		   Point ( float x = 0, float y = 0 ) : x(x) , y(y) { } ;					//默认的构造函数
		   void setPoint ( float, float );					//设置坐标值
		   float getX ( ) const { return x; }				//取得x坐标值
		   float getY ( ) const { return y; }				//取得y坐标值
		protected:								//允许派生类访问
		   float x, y;							//点(类Point的对象)的坐标值
		};

		class Circle : public Point {					//类Circle继承了类Point
		friend ostream &operator << ( ostream &, const Circle & );
		public:
		   Circle ( float r = 0.0, float x = 0, float y = 0 ):
			radius(r) { center.x = x; center.y = y; }; 		//默认的构造函数
		   void setRadius ( float );					//设置半径值
		   float getRadius ( ) const { return 2*radius; }					//取得半径值
		   float area ( ) const { return Pi*Pi*radius; }						//计算圆面积
		protected:
		   float radius;
		   Point center;
		} ;

		ostream & operator << (ostream& os, const Point & p) {
		    os << endl << "the point is located at ( " ;
		    os << p.x << "," << p.y << ")" << endl;
		    return os;
		}

		ostream & operator << (ostream& os, const Circle & c) {
		    os << "the center of circle is located at ( ";
		    os << " )" <<endl;
		    os << "the radius is " << c.radius << endl;
		    return os;
		}

		main () {
		   Point * pointPtr, p ( 3.5, 5.3 );				//点p坐标为3.5, 5.3
		   Circle * circlePtr, c ( 2.7, 1.2, 8.9 );				//圆c半径为2.7, 坐标为1.2, 8.9
		   cout << "Point p: " << p << "\n Circle c: " << c << endl;
		   pointPtr = & c;							//把派生类Circle对象的地址赋给了基类指针pointPtr
		   circlePtr = ( Circle * ) pointPtr;				//把基类指针强制转换为派生类指针
		   cout << "\n Area of c (via circlePtr) : " << circlePtr -> area ( ) << endl;
		   pointPtr = & p;							//把基类Point对象地址赋给基类指针pointPtr
		   circlePtr = ( Circle * ) pointPtr;				//把基类指针强制转换为派生类指针
		   cout << "\n Radius of object circlePtr point to : " << circlePtr -> getRadius ( ) << endl;
		   return 0;
		}
