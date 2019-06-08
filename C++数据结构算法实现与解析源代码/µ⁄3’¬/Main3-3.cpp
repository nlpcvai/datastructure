//Main3-3.cpp 验证稀疏矩阵RLSMatrix类的成员函数
#include "C.h"
#include "RLSMatrix.h"
void main()
{
	bool f;
	RLSMatrix<int> A("F3-2.txt"), B, C;
	
	cout<<"矩阵A="<<endl;
	A.PrintSMatrix();
	f=B.CreateSMatrixFromFile();
	if(f)
	{
		cout<<"矩阵B="<<endl;
		B.PrintSMatrix();
	}
	C.CopySMatrix(A);
	cout<<"由矩阵A复制的矩阵C="<<endl;
	C.PrintSMatrix();
	f=C.CreateSMatrixFromFile("F3-3.txt");
	if(f)
	{
		cout<<"由文件F3-3.txt创建矩阵C="<<endl;
		C.PrintSMatrix();
	}
	f=B.AddSMatrix(A, C);
	if(f)
	{
		cout<<"矩阵B1=A+C="<<endl;
		B.PrintSMatrix();
	}
	f=C.SubtSMatrix(B, A);
	if(f)
	{
		cout<<"矩阵C1=B-A="<<endl;
		C.PrintSMatrix();
	}
	A.TransposeSMatrix(C);
	cout<<"矩阵A1=C的转置"<<endl;
	A.PrintSMatrix();
	f=B.MultSMatrix(C, A);
	if(f)
	{
		cout<<"矩阵B2=C×A="<<endl;
		B.PrintSMatrix();
	}
}

