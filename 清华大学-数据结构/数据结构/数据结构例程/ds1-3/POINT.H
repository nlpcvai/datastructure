#ifndef POINT_H
#define POINT_H

class Point{
public:
    Point( int,int );
    Point( Point & );
    ~Point();
    int get_x();
    int get_x();
    Point operator + (Point);
    Point operator + ( int );
    Point operator * ( int );
    int operator > (Point);
    int operator < (Point);
    int operator = (Point & );
  private:
    int x;
    int y;
    friend istream& operator >> ( istream &,Point &);
    friend ostream& operator << ( istream &,Point &);
};
#endif
