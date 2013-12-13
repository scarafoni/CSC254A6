/////////////////////////////////////////////////////////////////////////////
// foo2.cpp, test file for CS254, assignment 5
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

int main(int argc, char **argv)
{
    Pointer<int> foo;
		cout << 1 << "\n";
    foo = new int(12);
		cout << 2 << "\n";
    Pointer<int> bar(foo);
		cout << 3 << "\n";

    if (bar == 0)
			error("Bar should not be null!");
		cout << "2\n";
    if (*bar != 12)
			error("Bar got the wrong value!");
    if (foo != bar)
			error("Foo and bar are NOT distinct pointers!");
    if (*foo != *bar)
			error("Foo and bar should have the same value here!");
    *foo = 15;
		printf("checking bar\n");
    if (*bar != 15)
			error("Bar should still match foo!");

		printf("freeing foo \n");
    free(foo);
		printf("freeing bar \n");
    free(bar);
    error("Attempt to double-delete pointer not flagged!");

    return 0;
}
