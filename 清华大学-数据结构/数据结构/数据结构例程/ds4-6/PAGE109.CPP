#include <process.h>
#include <math.h>
#include <stack.h>
#include <iostream.h>
enum Boolean {False,True};

class Calculator{
  public:
    Calculator(int sz=20):s(sz){};
    void Run();
    void Clear();
  private:
    void AddOperand(double value);
    Boolean Get2Operands(double & left,double & right);
    void DoOperator(char op);
    Stack<double> s;
    };

  void Calculator::AddOperand(double value){
    s.Push(value);
    }

  Boolean Calculator::Get2Operands(double & left,double & right){
    if(s.IsEmpty()){
      cerr<<"Missing Operand!"<<endl;
      return False;
      }
    right=s.Pop();
    if(s.IsEmpty()){
      cerr<<"Missing Operand!"<<endl;
      return False;
      }
    left=s.Pop();
    return True;
  }

  void Calculator::DoOperator(char op){
    double left,right;
    Boolean result;
    result=Get2Operands(left,right);
    if(result==True)
      switch(op){
	case '+': s.Push(left+right); break;
	case '-': s.Push(left-right); break;
	case '*': s.Push(left*right); break;
	case '/': if(right==0.0){
		    cerr<<"Divided by 0!"<<endl;
		    s.MakeEmpty();
		    exit(0);
		    }
		    else s.Push(left/right); break;
	case '^': s.Push(pow(left,right)); break;
	}
	else s.MakeEmpty();
    };

  void Calculator::Run(){
    char ch;
    double newoperand;
    while(cin>>ch,ch!='='){
      switch(ch){
	case '+':
	case '-':
	case '*':
	case '/':
	case '^':  DoOperator(ch); break;
	default: cin.putback(ch);
		 cin>>newoperand;
		 AddOperand(newoperand);
		 break;
      }
    }
    assert(!s.IsEmpty());
    cout<<"The result is:"<<s.Pop()<<endl;
  }

  void Calculator::Clear(){
    s.MakeEmpty();
    }



void main(){
  Calculator cal(10);
  cal.Run();
  }