//Test is T55_59.cpp

#include <iostream.h>

const int MaxTerms = 100;

template <class Type>	class SparseMatrix;			//ϡ������������

template <class Type>	class Trituple {			//��Ԫ����Trituple
friend class SparseMatrix<Type> ;
friend istream & operator >> ( istream & , SparseMatrix<Type> & );
friend ostream & operator << ( ostream & , SparseMatrix<Type> & );
private:
   int row, col;							//����Ԫ�ص��кš��к�
   Type value;							//����Ԫ�ص�ֵ
};


template <class Type>	class SparseMatrix {
	//����: ��һ����Ԫ��<row, column, value>�ļ��ϡ�����, row��column������, �������
	//Ԫ�����ڵ��кź��кţ���value�Ǿ���Ԫ�ص�ֵ��
friend istream & operator >> ( istream & , SparseMatrix<Type> & );
friend ostream & operator << ( ostream & , SparseMatrix<Type> & );
public:
   SparseMatrix ();
   SparseMatrix ( int MaxRow, int MaxCol ): Rows( MaxRow ), Cols( MaxCol ){};   	//���캯��
	//����һ��MaxRow��, Maxcol�е�ϡ�����
   SparseMatrix<Type> Transpose ( );
	//��*thisָʾ����Ԫ�������и�����Ԫ�齻�����С��е�ֵ, �õ���ת�þ���
   SparseMatrix<Type> Add ( SparseMatrix<Type> b );
	//������a(*thisָʾ)�����b���С�������ͬʱ, ������������Ķ�Ӧ����ӡ�
   SparseMatrix<Type> Multiply ( SparseMatrix<Type> b );
	//����ʽ c[i][j]=��(a[i][k]*b[k][j]) ʵ�־���a��b��ˡ�k=0, 1, ��, a������-1��
   SparseMatrix<Type> FastTranspose ( );
   SparseMatrix<Type> EmptyMatrix ( );
private:
   int Rows, Cols, Terms ;
   Trituple<Type> smArray[MaxTerms];
};


template <class Type> SparseMatrix<Type> SparseMatrix<Type>::Transpose ( ) {
	//��ϡ�����a(*thisָʾ)ת��, �����ϡ�����b�С�
	   SparseMatrix<Type> b ( Cols, Rows );					//����һ��ϡ�������Ķ���b
	   b.Rows = Cols;							//����b������=����a������
	   b.Cols = Rows;							//����b������=����a������
	   b.Terms = Terms;						//����b�ķ���Ԫ����=����a�ķ���Ԫ����
	   if ( Terms > 0 ) {							//����Ԫ�ظ�����Ϊ��
	      int CurrentB = 0;						//���λ��ָ��
	      for ( int k=0; k<Cols; k++ )					//���к���ɨ�裬��Cols��
	   for ( int i=0; i<Terms; i++ ) 					//�����������к�Ϊk����Ԫ��
		  if ( smArray[i].col == k ) {				//��i����Ԫ����Ԫ�ص��к�Ϊk
			b.smArray[CurrentB].row = k;			//����Ԫ����к�
			b.smArray[CurrentB].col = smArray[i].row;	//����Ԫ����к�
			b.smArray[CurrentB].value = smArray[i].value;	//����Ԫ���ֵ
			CurrentB++;						//���ָ���1
		  }
	   }
	   return b;
}


template <class Type> SparseMatrix<Type> SparseMatrix<Type>::FastTranspose ( ) {
	//��ϡ�����a(*thisָʾ)������ת��, �������b��, ʱ�����ΪO(Terms+Columns)
	   int *rowSize = new int[Cols];					//��������, ͳ�Ƹ��з���Ԫ�ظ���
	   int *rowStart = new int[Cols];					//��������, Ԥ��ת�ú���д��λ��
	   SparseMatrix<Type> b ( Cols, Rows );					 //���ת�ý��
	   b.Rows = Cols;  b.Cols = Rows;  b.Terms = Terms;
	   if ( Terms > 0 ) {
		 for ( int i=0; i<Cols; i++ ) rowSize[i] = 0; 		//ͳ�ƾ���b�е�i�з���Ԫ�ظ���
		 for ( i=0; i<Terms; i++ ) rowSize[smArray[i].col]++;
	      //���ݾ���a�е�i������Ԫ�ص��к�, ��rowSize�൱���еļ�����1
		 rowStart[0] = 0;						//�������b��i�з���Ԫ�صĿ�ʼ���λ��
		 for ( i=1; i <Cols; i++ )					//rowStart[i] = ����b�ĵ�i�еĿ�ʼ���λ��
		   rowStart[i] = rowStart[i-1]+rowSize[i-1];
		 for ( i=0; i<Terms; i++ ) {					//��a��b����
		   int j = rowStart[smArray[i].col];			// jΪ��i������Ԫ����b��Ӧ��ŵ�λ��
		   b.smArray[j].row = smArray[i].col;
		   b.smArray[j].col = smArray[i].row;
		   b.smArray[j].value = smArray[i].value;
		   rowStart[smArray[i].col]++;				//����b��i�з���Ԫ�صĴ��λ�ü�һ
		 }
	   }
	   delete [ ] rowSize;   delete [ ] rowStart;
	   return b;
}

template <class Type> SparseMatrix<Type> SparseMatrix<Type>::Multiply(SparseMatrix<Type> b)
	//����ϡ�����A (*thisָʾ) ��B (�������е�b) ���, �����Result��
{
    if ( Cols != b.Rows ) {
	 cout << "Incompatible matrices" << endl;			//A����������B������������
	 return EmptyMatrix ( );					//�������˷��ľ��󣬷��ؿվ���
    }
    if ( Terms == MaxTerms || b.Terms == MaxTerms ) {		//��һ������������ﵽ���
       cout << "One additional space in a or b needed" << endl;
	 return EmptyMatrix ( );					//�ռ䲻�㣬���ؿվ���
    }
    int *rowSize = new int[b.Rows];		 		//��������, ����B���з���Ԫ�ظ���
    int *rowStart = new int[b.Rows+1]; 				//��������, ����B��������Ԫ�鿪ʼλ��
    Type * temp = new Type[b.Cols];				//��ʱ����, �ݴ�ÿһ�м�����
    SparseMatrix<Type> result ( Rows, b.Cols );			//����������Ԫ���result
    for ( int i=0; i<b.Cols; i++ ) rowSize[i] = 0; 		//ͳ�ƾ���B�е�i�з���Ԫ�ظ���
    for ( i=0; i<b.Terms; i++ ) rowSize[smArray[i].row]++;
    rowStart[0] = 0;							//�������B��i�з���Ԫ�صĿ�ʼλ��
    for ( i=1; i <=b.Cols; i++ ) rowStart[i] = rowStart[i-1] + rowSize[i-1];
    int Current = 0,  lastInResult = -1;				//a.smArrayɨ��ָ�뼰result���ָ��
    while ( Current < Terms ) {					//����result�ĵ�ǰ��temp
	  int RowA = smArray[Current].row;			//��ǰ�е��к�
	  for ( i=0; i<b.Cols; i++ ) temp[i] = 0;			//temp��ʼ��
	  while ( Current < Terms && smArray[Current].row == RowA ) {
	     int ColA = smArray[Current].col;			//����A��ǰɨ�赽Ԫ�ص��к�
	     for ( i=rowStart[ColA]; i<rowStart[ColA+1]; i++ ) {
		  int ColB = b.smArray[i].col;			//����B�����Ԫ�ص��к�
		  temp[ColB] = temp[ColB] + smArray[Current].value * b.smArray[i].value;
	     }								//A��RowA����B��ColB�����
	    Current++;
	  }
	  for ( i=0; i<b.Cols; i++ )
	    if ( temp[i] != 0 ) {					//��temp�еķ���Ԫ��ѹ����result��ȥ
		 lastInResult++;
		 result.smArray[lastInResult].row = RowA;
		 result.smArray[lastInResult].col = i;
		 result.smArray[lastInResult].value = temp[i];
	    }
    }
    result.Rows = Rows;  result.Cols = b.Cols;  result.Terms = lastInResult+1;
    delete [ ] rowSize;  delete [ ] rowStart;  delete [ ] temp;
    return result;
}

template <class Type>  SparseMatrix<Type> SparseMatrix<Type>:: EmptyMatrix ( ) {
    SparseMatrix<Type> b(0,0);
    return b;
}

template <class Type> istream & operator >> ( istream & is , SparseMatrix<Type> & matrix) {
    cout << "Rows and Cols: " << endl;
    is >> matrix.Rows >> matrix.Cols;
    cout << "row col value : ( ended by row = -1 ) " << endl;
    matrix.Terms = -1 ;
    do {
	matrix.Terms ++;
	is >> matrix.smArray[matrix.Terms].row
	   >> matrix.smArray[matrix.Terms].col
	   >> matrix.smArray[matrix.Terms].value;
    } while ( matrix.smArray[matrix.Terms].row != -1 );
    return is;
}

template <class Type> ostream & operator << ( ostream & os , SparseMatrix<Type> & matrix) {
    if ( matrix.Terms == 0 ) { os << "It is empty."; return os}
    os << "Rows: " << matrix.Rows << endl;
    os << "Cols: " << matrix.Cols << endl;
    os << "col row value: " << endl;
    for (int i=0; i<matrix.Terms; i++) {
	os << matrix.smArray[i].row << " "
	   << matrix.smArray[i].col << " "
	   << matrix.smArray[i].value << endl;
    }
    return os;
}

