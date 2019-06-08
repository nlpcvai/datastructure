const int MaxTerms = 100;

class Polynomial;						//����ʽ���ǰ������

class term { 							//����ʽ������ඨ��
	friend Polynomial;						//����Polynomial��Ϊterm�����Ԫ��
	private:
	float coef;							//ϵ��
	int exp;							//ָ��
};

class Polynomial {

public:
	//�ڶ���2.3���г��Ķ���ʽ�Ĺ�������
	//   ����
       Polynomial ( );						//���ض���ʽp(x)=0
		   int operator ! ( );						//��*this�������ʽ, �򷵻�1, ���򷵻�0��
		   int Coef (int e);				//���ض���ʽ*this��ָ��e��ϵ����
		   int LeadExp ( );					//���ض���ʽ*this������ָ����
		   Polynomial Add (Polynomial poly);			//���ض���ʽ*this�����ʽpoly�ĺ͡�
		   Polynomial Mult (Polynomial poly);   	    //���ض���ʽ*this�����ʽpoly�ĳ˻���
		   void NewTerm (float c, int e);
		   float Eval ( float x);					//�������ʽ*this�ڱ���Ϊxʱ��ֵ��
private:

    static term termArray[MaxTerms];			//��Ŷ���ʽ������
    static int free;						//����ʽ��Ч��������һλ��
    //Ҫ�����ඨ��֮�ⶨ�壺
    // term Polynomial::termArray[MaxTerms];
    // int Polynomial::free = 0;				//��termArray����һ������λ��

    int start, finish ;						//����ʽ��ʼ�����λ��
};

#include <iostream.h>
void Polynomial::NewTerm ( float c, int e ) {
		//��һ���µ���ӵ�����ʽC (x)��
    if ( free >= MaxTerms ) {
	cout << "Too many terms in polynomials" << endl;  return;
    }
    termArray[free].coef = c;	 termArray[free].exp = e;  free++;
}


Polynomial Polynomial::Add ( Polynomial B ) {
	//������������ʽA(x) {��*this��}��B(x)�ĺ�
    Polynomial C;   int a = start;   int b = B.start;   C.start = free;		//a, b�ֱ�Ϊ������ʽ���ָ��
    float c;									//cΪ�������ʽ�Ĵ��ָ��
    while ( a <= finish && b <= B.finish )
	if ( termArray[a].exp == termArray[b].exp)  {	//�Ƚ϶�Ӧ���ָ��
	     c = termArray[a].coef + termArray[b].coef;		//��ȣ�ϵ�����
	     if ( c ) NewTerm ( c, termArray[a].exp );		//�Ͳ�Ϊ0����������
	     a++;  b++;
	}
	else if ( termArray[a].exp < termArray[b].exp ) {
	    NewTerm ( termArray[b].coef, termArray[b].exp );	//���ȣ���������
	    b++;
	}
	else if ( termArray[a].exp < termArray[b].exp ) {
	    NewTerm ( termArray[a].coef, termArray[a].exp ); 	//���ȣ���������
	    a++;
	}

    for ( ; a<=finish; a++ )							//��A(x)��ʣ�����
	NewTerm ( termArray[a].coef, termArray[a].exp );
    for ( ; b<=B.finish; b++ )						//��B(x)��ʣ�����
	NewTerm ( termArray[b].coef, termArray[b].exp );
    C.finish = free-1;
    return C;
}


