template <class Type>	class SparseMatrix {
	//����: ��һ����Ԫ��<row, column, value>�ļ��ϡ�����, row��column������, �������
	//Ԫ�����ڵ��кź��кţ���value�Ǿ���Ԫ�ص�ֵ��
public:
   SparseMatrix ( int MaxRow, int Maxcol );   	//���캯��
	//����һ��MaxRow��, Maxcol�е�ϡ�����
   SparseMatrix<Type> Transpose ( );
	//��*thisָʾ����Ԫ�������и�����Ԫ�齻�����С��е�ֵ, �õ���ת�þ���
   SparseMatrix<Type> Add ( SparseMatrix<Type> b );
	//������a(*thisָʾ)�����b���С�������ͬʱ, ������������Ķ�Ӧ����ӡ�
   SparseMatrix<Type> Multiply ( SparseMatrix<Type> b );
	//����ʽ c[i][j]=��(a[i][k]*b[k][j]) ʵ�־���a��b��ˡ�k=0, 1, ��, a������-1��
private:
   int Rows, Cols, Terms;
   Trituple<Type> smArray[MaxTerms];
}



template <class Type>	class SparseMatrix;			//ϡ������������

template <class Type>	class Trituple {			//��Ԫ����Trituple 
friend class SparseMatrix
private:
   int row, col;							//����Ԫ�ص��кš��к�
   Type value;							//����Ԫ�ص�ֵ
}
