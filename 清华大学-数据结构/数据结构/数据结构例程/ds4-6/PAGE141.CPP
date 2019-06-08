#include <iostream.h>


long FibIter(long n){
  if(n<=1) return n;
    else{
      int Current;
      long twoback=1,oneback=0;
      for(int i=2;i<=n;i++){
	Current=twoback+oneback;
	oneback=twoback;
	twoback=Current;
	}
      return Current;
      }
    }

 void recfunc(int A[],int n){
   if(n>=0){
     cout<<A[n]<<"  ";
     n--;
     recfunc(A,n);
     }
   }

  void iterfunc(int A[],int n){
    while(n>=0){
      cout<<"value "<<A[n]<<endl;
      n--;
      }
    }

void main(){
  long n=9;
  cout<<FibIter(n)<<endl;
  static  int a[10]={0};
  recfunc(a,9);
  cout<<endl;
  iterfunc(a,9);
  }

