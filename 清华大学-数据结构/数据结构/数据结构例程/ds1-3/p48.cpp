class Polynomial {
		//����: ��һ����������<ei, ai>�ļ��ϡ�����,
		//ei��ָ��, ai��ϵ�����ڴ˶�����, �趨ָ���Ǵ��ڵ������������
		public:
		   Polynomial ( );						//���ض���ʽp(x)=0
		   int operator ! ( );						//��*this�������ʽ, �򷵻�1, ���򷵻�0��
		   int Coef (int e);				//���ض���ʽ*this��ָ��e��ϵ����
		   int LeadExp ( );					//���ض���ʽ*this������ָ����
		   Polynomial Add (Polynomial poly);			//���ض���ʽ*this�����ʽpoly�ĺ͡�
		   Polynomial Mult (Polynomial poly);			//���ض���ʽ*this�����ʽpoly�ĳ˻���
		   float Eval ( float x);					//�������ʽ*this�ڱ���Ϊxʱ��ֵ��
		};


#include <iostream.h>
class power {							//������ֵ����
		   double x;							//����
		   int e;							//ָ��
		   double mul;						//���ݵ�ֵ
		public:
		   power (double val, int exp);				//���캯��
		   double get_power ( ) { return mul; }			//ȡ��ֵ
		};

		power::power (double val, int exp) {			//���캯��
		   x = val;	  e = exp;   mul = 1.0;			//Ϊ����Ļ���x��ָ��e��ֵ
		   if (exp == 0 ) return ;
		   for ( ; exp>0; exp--) mul = mul * x; 			//�������mul
}

void main ( ) {
		   power pwr ( 1.5, 3 );					//��������pwr������Ϊ1.5, ָ��Ϊ2
		   cout << pwr.get_power ( ) << "\n";			//������ݵ�ֵ
}
