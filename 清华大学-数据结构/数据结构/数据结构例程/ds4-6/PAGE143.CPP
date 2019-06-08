#include <iostream.h>
const int m=9,p=4;
static int Maze[m+2][p+2]={{1,1,1,1,1,1},{0,0,0,0,1,1},
{1,1,1,1,0,1},{1,1,0,0,1,1},{1,0,1,1,1,1},{1,1,0,0,1,1},{1,1,1,1,0,1},
{1,1,0,0,1,1},{1,0,1,1,1,1},{1,1,0,0,0,0},{1,1,1,1,1,1}};
static int mark[m+2][p+2];


struct items{
  int x,y,dir;
  };


struct offsets{
  int a,b;
  };

enum directions{N,NE,E,SE,S,SW,W,NW};
static offsets move[8]={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};

#include <stack.h>
template<class Type> ostream & operator<<(ostream & os,Stack<Type>& s){
    for(int i=0;i<=s.top;i++)
    os<<s.elements[i]<<endl;
  return os;
  }

ostream & operator << (ostream & os,items & item){
  os<<item.x<<' '<<item.y;
  return os;
  }

void path(int m,int p){
  mark[1][1];
  Stack<items> st(m*p);
  items tmp;
  tmp.x=1;
  tmp.y=1;
  tmp.dir=E;
  st.Push(tmp);
  while(!st.IsEmpty()){
    tmp= st.Pop();
    int i=tmp.x;
    int j=tmp.y;
    int d=tmp.dir;
    while(d<8){
      int g=i+move[d].a;
      int h=j+move[d].b;
      if(g==m&&h==p){
	cout<<st;
	cout<<i<<" "<<j<<endl;
	cout<<m<<" "<<p<<endl;
	return;
	}
      if(!Maze[g][h]&&!mark[g][h]){
	mark[g][h]=1;
	tmp.x=i;
	tmp.y=j;
	tmp.dir=d+1;
	st.Push(tmp);
	i=g;
	j=h;
	d=N;
	}
	else d++;
      }
    }
  cout<<"no path in Maze"<<endl;
  }



void main(){
  cout<<"The path is(IF YOU WANT TO CHANGE THE MAZE,PLEASE MODIFY THE \nSTATIC ARRAY OF MAZE[M+2][P+2] AND THE VALUE OF M AND P):"<<endl;
  path(m,p);
  }
