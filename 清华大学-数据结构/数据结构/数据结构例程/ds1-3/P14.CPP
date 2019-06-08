#include <fstream.h>
#include <stdlib.h>
#include <process.h>

void main() {
    ofstream outFile ("my.out");
    if (! outFile ) {
	cout << "Cannot open my.out" << endl; exit(1);
    }
    int n = 50; float f = 20.3;
    outFile << "n:" << n << endl;
    outFile << "f:" << f << endl;
}