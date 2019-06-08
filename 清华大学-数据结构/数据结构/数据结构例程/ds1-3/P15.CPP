#include <iostream.h>
char & replace ( int m );
char s[80] = "Hello There";

main () {
    replace (5) = 'x'; cout << s << endl; return 0;
}

char & replace (int m) {
    return s[m];
}