/////////////////////////////////////////////////////////////////////////////
// foo6.cpp, test file for CS254, assignment 5
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdlib.h>
#include "tombstones.h"

using namespace std;

void error(const char *text)
{
    cout << "ERROR: " << text << endl;
    exit(-1);
}

Pointer<int> &rec(int n, Pointer<int> foo)
{
		cout << "rec\n";
    static Pointer<int> result(new int(*foo));
    if (0 == n)
			return result;
    result = (Pointer<int>&)(rec(n-1, foo));
    *result += 1;
    return result;
}

Pointer<int> &recref(int n, Pointer<int> &foo)
{
		cout << "recref\n";
    if (0 == n)
	return foo;
    *foo += 1;
    return rec(n-1, foo);
}

void proc()
{
	cout << "1\n";
    Pointer<int> foo(new int(0));
	cout << "2\n";
    Pointer<int> bar(rec(100, foo));
	cout << "3\n";
    if (*bar != 100 || *foo != 0)
	error("Foo or bar incorrect after rec()!");

    foo = recref(100, bar);
    if (*foo != 200)
	error("Foo incorrect after recref()!");
	printf("foo: %p, bar: %p\n", &foo, &bar);
    if (foo != bar)
			error("Foo not an alias for bar after recref()!");
		cout <<"safe maybe?\n";
    free(foo);
}

int main(int argc, char **argv)
{
    proc();
    error("Didn't blow up when leaking memory!");

    return 0;
}
