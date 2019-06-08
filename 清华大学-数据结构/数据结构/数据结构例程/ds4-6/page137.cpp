struct Intersection{
  int left;
  int forward;
  int right;
  };

#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
class Maze{
  private:
    int MazeSize;
    int Exit;
    Intersection * intsec;
  public:
    Maze(char * filename);
    int TraverseMaze(int CurrentPos=1);
  };

  Maze::Maze(char * filename){
    ifstream fin;
    fin.open(filename,ios::in|ios::nocreate);
    if(!fin){
      cerr<<"The Maze data file "<<filename<<" cannot be opened!"<<endl;
      exit(1);
      }
    fin>>MazeSize;
    intsec=new Intersection[MazeSize+1];
    for(int i=1;i<=MazeSize;i++)
      fin>>intsec[i].left>>intsec[i].forward>>intsec[i].right;
      fin>>Exit;
      fin.close();
      }

  int Maze::TraverseMaze(int CurrentPos){
    if(CurrentPos>0){
      if(CurrentPos==Exit){
	cout<<CurrentPos<<"  ";
	return 1;
	}
	else if(TraverseMaze(intsec[CurrentPos].left)){
	  cout<<CurrentPos<<"  ";
	  return 1;
	  }
	  else if(TraverseMaze(intsec[CurrentPos].forward)){
	    cout<<CurrentPos<<"  ";
	    return 1;
	    }
	    else if(TraverseMaze(intsec[CurrentPos].right)){
	      cout<<CurrentPos<<"  ";
	      return 1;
	      }
      }
    return 0;
  }



void main(){
  int i;
  char * filename="D:\\Borlandc\\Bin\\Maze.txt";
  Maze maze(filename);
  i=maze.TraverseMaze();
  cout<<endl;
  if(!i)cout<<"There isn't any way to the entrance!"<<endl;
  }