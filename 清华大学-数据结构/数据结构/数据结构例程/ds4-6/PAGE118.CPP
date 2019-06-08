#include <stdio.h>
#include <iostream.h>
#include "queue.h"
void YANGHUI(int n){
  Queue<int> q;
  q.MakeEmpty();
  q.EnQueue(1);
  q.EnQueue(1);
  int s=0;
  for(int i=1;i<=n;i++){
    cout<<endl;
    q.EnQueue(0);
    for(int j=1;j<=i+2;j++){
      int t=q.DeQueue();
      q.EnQueue(s+t);
      s=t;
      if(j!=i+2) cout<<s<<' ';
      }
    }
  }




void main(){
  YANGHUI(10);
  }