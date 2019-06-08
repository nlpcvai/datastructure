#include <iostream.h>

class szcl {
    int e;
public:
    szcl () { e=0; }
    szcl ( int value ) { e = value; }
    int get_value() { return e; }
};

main() {
    int i;
    szcl a1[3] = { 3,5,7 }, *elem;
    for ( i=0; i<3; i++ ) cout << a1[i].get_value() << endl;
    elem = a1;
    for ( i=0; i<3; i++ ) {
	cout << elem->get_value() << endl;
	elem++;
    }
    return 0;
}