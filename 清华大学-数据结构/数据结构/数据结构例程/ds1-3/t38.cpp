#include "p38.cpp"
#include <iostream.h>
#include "testtool.cpp"
//this is a test for p38.cpp

Array<int> array1(10),array2(10000000);
void report(void)
{
  cout<<"========================================================="<<endl;
  cout<<"array1:"<<endl<<array1;
//  array1.Print();
  cout<<"array2:"<<endl<<array2;
//  array2.Print();
  cout<<"========================================================="<<endl;
}
void main(void)
{
  msg("array2 is a wrong array because of the extremly large size");
  report();
  msg("put 0--9 to array1");
  for (int i=0;i<array1.Length();i++)
  {
    array1[i]=i;
  }
  report();
  msg("copy array1 to array2");
  array2=array1;
  report();
  msg("Creat array3 from array2:");
  Array<int> array3(array2);
  cout<<array3<<endl;
  msg("ReSize array2 to 5:");
  array2.ReSize(5);
  report();
  msg("ReSize array1 to 1000000000: (should be error)");
  array1.ReSize(1000000000);
  report();
  msg("ReSize array1 to 0");
  array1.ReSize(0);
  report();
  msg("The last test to check the situation when overflow:");
  i=0;
  while (array3.Length())
  {
    cout<<(i++)<<endl;
    array3=Array<int>(100000);
  }
  array3=Array<int>(array2);
  while (array3.Length())
  {
    cout<<(i++)<<endl;
    array3=Array<int>(array2);
  }
  msg("Test finished");
}
