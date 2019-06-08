#include <ctype.h>
#include <iostream.h>
#include <stack.h>
int isp(char ch){
  switch (ch){
    case '#': return 0;
    case '(': return 1;
    case '^': return 7;
    case '*':
    case '/':
    case '%': return 5;
    case '+':
    case '-': return 3;
    case ')': return 8;
    }
  return -1;
  }

int icp(char ch){
  switch (ch){
    case '#': return 0;
    case '(': return 8;
    case '^': return 6;
    case '*':
    case '/':
    case '%': return 4;
    case '+':
    case '-': return 2;
    case ')': return 1;
    }
  return -1;
  }

void postfix(){
  Stack<char> s;
  char ch,y;
  s.MakeEmpty();
  s.Push('#');
  while(cin.get(ch),ch!='#'){
    if(isdigit(ch)) cout<<ch;
      else if(ch==')')
	     for(y=s.Pop();y!='(';y=s.Pop()) cout<<y;
	     else {
	       for(y=s.Pop();isp(y)>icp(ch);y=s.Pop()) cout<<y;
	       s.Push(y);
	       s.Push(ch);
      }
    }
   while(!s.IsEmpty()){
     y=s.Pop();
     cout<<y;
      }
  cout<<endl;
  }

void main(){
  cout<<"Now,input your expression:"<<endl;
  postfix();
  }