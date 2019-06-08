#include "datalist.h"
#include "selecttm.h"
const int size = 10;

int main() {
    dataList <int> TestList (size) ;
    cin >> TestList;
    cout << "Testing Selection Sort: \n" << TestList << endl;
    TestList.Sort();
    cout << "After sorting: \n" << TestList << endl;
    return 0;
}