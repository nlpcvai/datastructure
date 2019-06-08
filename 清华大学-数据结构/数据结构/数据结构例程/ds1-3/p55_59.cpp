//Test is T55_59.cpp

#include <iostream.h>

const int MaxTerms = 100;

template <class Type>	class SparseMatrix;			//稀疏矩阵的类声明

template <class Type>	class Trituple {			//三元组类Trituple
friend class SparseMatrix<Type> ;
friend istream & operator >> ( istream & , SparseMatrix<Type> & );
friend ostream & operator << ( ostream & , SparseMatrix<Type> & );
private:
   int row, col;							//非零元素的行号、列号
   Type value;							//非零元素的值
};


template <class Type>	class SparseMatrix {
	//对象: 是一个三元组<row, column, value>的集合。其中, row和column是整数, 记忆矩阵
	//元素所在的行号和列号，而value是矩阵元素的值。
friend istream & operator >> ( istream & , SparseMatrix<Type> & );
friend ostream & operator << ( ostream & , SparseMatrix<Type> & );
public:
   SparseMatrix ();
   SparseMatrix ( int MaxRow, int MaxCol ): Rows( MaxRow ), Cols( MaxCol ){};   	//构造函数
	//建立一个MaxRow行, Maxcol列的稀疏矩阵。
   SparseMatrix<Type> Transpose ( );
	//对*this指示的三元组数组中各个三元组交换其行、列的值, 得到其转置矩阵。
   SparseMatrix<Type> Add ( SparseMatrix<Type> b );
	//当矩阵a(*this指示)与矩阵b的行、列数相同时, 将这两个矩阵的对应项相加。
   SparseMatrix<Type> Multiply ( SparseMatrix<Type> b );
	//按公式 c[i][j]=∑(a[i][k]*b[k][j]) 实现矩阵a与b相乘。k=0, 1, …, a的列数-1。
   SparseMatrix<Type> FastTranspose ( );
   SparseMatrix<Type> EmptyMatrix ( );
private:
   int Rows, Cols, Terms ;
   Trituple<Type> smArray[MaxTerms];
};


template <class Type> SparseMatrix<Type> SparseMatrix<Type>::Transpose ( ) {
	//将稀疏矩阵a(*this指示)转置, 结果在稀疏矩阵b中。
	   SparseMatrix<Type> b ( Cols, Rows );					//创建一个稀疏矩阵类的对象b
	   b.Rows = Cols;							//矩阵b的行数=矩阵a的列数
	   b.Cols = Rows;							//矩阵b的列数=矩阵a的行数
	   b.Terms = Terms;						//矩阵b的非零元素数=矩阵a的非零元素数
	   if ( Terms > 0 ) {							//非零元素个数不为零
	      int CurrentB = 0;						//存放位置指针
	      for ( int k=0; k<Cols; k++ )					//按列号做扫描，做Cols趟
	   for ( int i=0; i<Terms; i++ ) 					//在数组中找列号为k的三元组
		  if ( smArray[i].col == k ) {				//第i个三元组中元素的列号为k
			b.smArray[CurrentB].row = k;			//新三元组的行号
			b.smArray[CurrentB].col = smArray[i].row;	//新三元组的列号
			b.smArray[CurrentB].value = smArray[i].value;	//新三元组的值
			CurrentB++;						//存放指针进1
		  }
	   }
	   return b;
}


template <class Type> SparseMatrix<Type> SparseMatrix<Type>::FastTranspose ( ) {
	//对稀疏矩阵a(*this指示)做快速转置, 结果放在b中, 时间代价为O(Terms+Columns)
	   int *rowSize = new int[Cols];					//辅助数组, 统计各列非零元素个数
	   int *rowStart = new int[Cols];					//辅助数组, 预计转置后各行存放位置
	   SparseMatrix<Type> b ( Cols, Rows );					 //存放转置结果
	   b.Rows = Cols;  b.Cols = Rows;  b.Terms = Terms;
	   if ( Terms > 0 ) {
		 for ( int i=0; i<Cols; i++ ) rowSize[i] = 0; 		//统计矩阵b中第i行非零元素个数
		 for ( i=0; i<Terms; i++ ) rowSize[smArray[i].col]++;
	      //根据矩阵a中第i个非零元素的列号, 将rowSize相当该列的计数加1
		 rowStart[0] = 0;						//计算矩阵b第i行非零元素的开始存放位置
		 for ( i=1; i <Cols; i++ )					//rowStart[i] = 矩阵b的第i行的开始存放位置
		   rowStart[i] = rowStart[i-1]+rowSize[i-1];
		 for ( i=0; i<Terms; i++ ) {					//从a向b传送
		   int j = rowStart[smArray[i].col];			// j为第i个非零元素在b中应存放的位置
		   b.smArray[j].row = smArray[i].col;
		   b.smArray[j].col = smArray[i].row;
		   b.smArray[j].value = smArray[i].value;
		   rowStart[smArray[i].col]++;				//矩阵b第i行非零元素的存放位置加一
		 }
	   }
	   delete [ ] rowSize;   delete [ ] rowStart;
	   return b;
}

template <class Type> SparseMatrix<Type> SparseMatrix<Type>::Multiply(SparseMatrix<Type> b)
	//两个稀疏矩阵A (*this指示) 与B (参数表中的b) 相乘, 结果在Result中
{
    if ( Cols != b.Rows ) {
	 cout << "Incompatible matrices" << endl;			//A矩阵列数与B矩阵行数不等
	 return EmptyMatrix ( );					//不能做乘法的矩阵，返回空矩阵
    }
    if ( Terms == MaxTerms || b.Terms == MaxTerms ) {		//有一个矩阵的项数达到最大
       cout << "One additional space in a or b needed" << endl;
	 return EmptyMatrix ( );					//空间不足，返回空矩阵
    }
    int *rowSize = new int[b.Rows];		 		//辅助数组, 矩阵B各行非零元素个数
    int *rowStart = new int[b.Rows+1]; 				//辅助数组, 矩阵B各行在三元组开始位置
    Type * temp = new Type[b.Cols];				//临时数组, 暂存每一行计算结果
    SparseMatrix<Type> result ( Rows, b.Cols );			//结果矩阵的三元组表result
    for ( int i=0; i<b.Cols; i++ ) rowSize[i] = 0; 		//统计矩阵B中第i行非零元素个数
    for ( i=0; i<b.Terms; i++ ) rowSize[smArray[i].row]++;
    rowStart[0] = 0;							//计算矩阵B第i行非零元素的开始位置
    for ( i=1; i <=b.Cols; i++ ) rowStart[i] = rowStart[i-1] + rowSize[i-1];
    int Current = 0,  lastInResult = -1;				//a.smArray扫描指针及result存放指针
    while ( Current < Terms ) {					//生成result的当前行temp
	  int RowA = smArray[Current].row;			//当前行的行号
	  for ( i=0; i<b.Cols; i++ ) temp[i] = 0;			//temp初始化
	  while ( Current < Terms && smArray[Current].row == RowA ) {
	     int ColA = smArray[Current].col;			//矩阵A当前扫描到元素的列号
	     for ( i=rowStart[ColA]; i<rowStart[ColA+1]; i++ ) {
		  int ColB = b.smArray[i].col;			//矩阵B中相乘元素的列号
		  temp[ColB] = temp[ColB] + smArray[Current].value * b.smArray[i].value;
	     }								//A的RowA行与B的ColB列相乘
	    Current++;
	  }
	  for ( i=0; i<b.Cols; i++ )
	    if ( temp[i] != 0 ) {					//将temp中的非零元素压缩到result中去
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

