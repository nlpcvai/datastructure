#include <iostream.h>

long Factorial(long n){
  if(n==0) return 1;
  else return n*Factorial(n-1);
  }


void main(){
  int n=10;
  cout<<Factorial(n)<<endl;
  }