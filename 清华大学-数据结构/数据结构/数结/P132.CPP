#include <iostream.h>

long Factorial(long n){
  if(n==0) return 1;
  else return n*Factorial(n-1);
  }


void main(void){
  cout<<"Input N:";
  int n;
  cin>>n;
  cout<<Factorial(n)<<endl;
}