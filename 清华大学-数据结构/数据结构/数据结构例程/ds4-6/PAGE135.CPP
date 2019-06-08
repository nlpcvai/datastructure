#include <iostream.h>
void Hanoi(int n,char A,char B,char C){
  if(n==1)cout<<"move "<<A<<" to "<<C<<endl;
  else{
    Hanoi(n-1,A,C,B);
    cout<<"move "<<A<<" to "<<C<<endl;
    Hanoi(n-1,B,A,C);
    }
  }

void main(){
  int n=3;
  char a='a',b='b',c='c';
  Hanoi(n,a,b,c);
  }