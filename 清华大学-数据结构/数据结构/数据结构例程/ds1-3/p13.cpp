#include <stdio.h>
#include <string.h>
#include "hello.h"

char *hello(char *name) {
char *value = new char [9+strlen(name)];
sprintf(value,"hello,%s.",name);
return value;
}

#include <iostream.h>
#include "hello.h"

main(){
cout << hello("world") << endl;
}



