		#include <iostream.h>
		#define Pi 3.1415926

		class Point {
		friend ostream &operator << (ostream &, const Point &);
		public:
		   Point ( float x = 0, float y = 0 ) : x(x) , y(y) { } ;					//Ĭ�ϵĹ��캯��
		   void setPoint ( float, float );					//��������ֵ
		   float getX ( ) const { return x; }				//ȡ��x����ֵ
		   float getY ( ) const { return y; }				//ȡ��y����ֵ
		protected:								//�������������
		   float x, y;							//��(��Point�Ķ���)������ֵ
		};

		class Circle : public Point {					//��Circle�̳�����Point
		friend ostream &operator << ( ostream &, const Circle & );
		public:
		   Circle ( float r = 0.0, float x = 0, float y = 0 ):
			radius(r) { center.x = x; center.y = y; }; 		//Ĭ�ϵĹ��캯��
		   void setRadius ( float );					//���ð뾶ֵ
		   float getRadius ( ) const { return 2*radius; }					//ȡ�ð뾶ֵ
		   float area ( ) const { return Pi*Pi*radius; }						//����Բ���
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
		   Point * pointPtr, p ( 3.5, 5.3 );				//��p����Ϊ3.5, 5.3
		   Circle * circlePtr, c ( 2.7, 1.2, 8.9 );				//Բc�뾶Ϊ2.7, ����Ϊ1.2, 8.9
		   cout << "Point p: " << p << "\n Circle c: " << c << endl;
		   pointPtr = & c;							//��������Circle����ĵ�ַ�����˻���ָ��pointPtr
		   circlePtr = ( Circle * ) pointPtr;				//�ѻ���ָ��ǿ��ת��Ϊ������ָ��
		   cout << "\n Area of c (via circlePtr) : " << circlePtr -> area ( ) << endl;
		   pointPtr = & p;							//�ѻ���Point�����ַ��������ָ��pointPtr
		   circlePtr = ( Circle * ) pointPtr;				//�ѻ���ָ��ǿ��ת��Ϊ������ָ��
		   cout << "\n Radius of object circlePtr point to : " << circlePtr -> getRadius ( ) << endl;
		   return 0;
		}
