#include <iostream.h>

long Fib(long n){
  if(n<=1) return n;
  else return Fib(n-1)+Fib(n-2);
  }

void main(){
  int n=8;
  cout<<Fib(n)<<endl;
  }
