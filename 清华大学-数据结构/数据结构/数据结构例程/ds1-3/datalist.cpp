#ifndef DATALIST_H
#define DATALIST_H
#include <iostream.h>

template < class Type >
class dataList {
    private:
	Type * Element;
	int ArraySize;
	void Swap (const int mark1, const int mark2);
	int MaxKey (cocnst int low, const int high);
    public:
	dataList (int size = 10):ArraySize(size),Element(new Type[Size]) {}
	~dataList () {delete[] Element; }
	void Sort ();
	friend ostream& operator << (ostream& outStream, const datalist<Type> & outList);
	friend istream& operator << (istream& inStream, const datalist<type> & inList);
};
#endif