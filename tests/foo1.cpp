/////////////////////////////////////////////////////////////////////////////
// foo1.cpp, test file for CS254, assignment 5
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdlib.h>
#include "tombstones.h"
#include <stdio.h>
using namespace std;

void error(const char *text)
{
    cout << "ERROR: " << text << endl;
    exit(-1);
}

int main(int argc, char **argv)
{
    Pointer<int> foo(new int(12));
    Pointer<int> tmp((int*)NULL);
    Pointer<int> bar = tmp;

		printf("foo- %p %d\n", &foo, *foo);
    if (foo == 0)
			error("Foo shouldn't be null!");
		if(tmp != 0)
			error("tmp should be null!");
    if (bar != 0)
			error("Bar should be null!");
		//printf("bar1- %d\n",*bar);
    int *a = new int(13);
		printf("a- %p %d\n", a, *a);
		printf("bar- %p\n", &bar);
    bar = a;

		printf("bar- %p %d\n", &bar, *bar);
    if (foo == bar)
			error("Foo and bar are distinct pointers!");
    if (*foo != *bar)
			error("Foo and bar should have the same value here!");

    free(foo);
    free(bar);
    cout << "foo1: OK" << endl;
    return 0;
}


/*
Integer x = 10;
Integer y = x;

class Integer {
	int num;
}
*/
