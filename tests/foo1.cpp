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
		foo.printInfo("foo");
		//cout << "1 "<<"\n";
    Pointer<int> tmp((int*)NULL);
		//foo.printInfo("tmp");
		//cout << 2 <<"\n";
    Pointer<int> bar = tmp;
		//bar.printInfo("bar");
		//cout << 3 <<"\n";

    if (foo == 0)
			error("Foo shouldn't be null!");
		cout << 4 <<"\n";
		if(tmp != 0)
			error("tmp should be null!");
		cout << 5 <<"\n";
    if (bar != 0)
			error("Bar should be null!");

		cout << 6 <<"\n";
    bar = new int(12);
		cout << 7 <<"\n";
		//printf("bar- %p %d\n", &(*bar), *bar);
    if (foo == bar)
			error("Foo and bar are distinct pointers!");
		cout << 8 <<"\n";
    if (*foo != *bar)
			error("Foo and bar should have the same value here!");
		cout << 8 <<"\n";

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
