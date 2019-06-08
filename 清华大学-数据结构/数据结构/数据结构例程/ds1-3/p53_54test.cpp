template <class Type>	class SparseMatrix {
	//对象: 是一个三元组<row, column, value>的集合。其中, row和column是整数, 记忆矩阵
	//元素所在的行号和列号，而value是矩阵元素的值。
public:
   SparseMatrix ( int MaxRow, int Maxcol );   	//构造函数
	//建立一个MaxRow行, Maxcol列的稀疏矩阵。
   SparseMatrix<Type> Transpose ( );
	//对*this指示的三元组数组中各个三元组交换其行、列的值, 得到其转置矩阵。
   SparseMatrix<Type> Add ( SparseMatrix<Type> b );
	//当矩阵a(*this指示)与矩阵b的行、列数相同时, 将这两个矩阵的对应项相加。
   SparseMatrix<Type> Multiply ( SparseMatrix<Type> b );
	//按公式 c[i][j]=∑(a[i][k]*b[k][j]) 实现矩阵a与b相乘。k=0, 1, …, a的列数-1。
private:
   int Rows, Cols, Terms;
   Trituple<Type> smArray[MaxTerms];
}



template <class Type>	class SparseMatrix;			//稀疏矩阵的类声明

template <class Type>	class Trituple {			//三元组类Trituple 
friend class SparseMatrix
private:
   int row, col;							//非零元素的行号、列号
   Type value;							//非零元素的值
}
