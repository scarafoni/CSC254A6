all: foo1 foo2 foo3 foo4 foo5 foo6 foo7 foo8

foo1: tests/foo1.cpp tombstones.h
	g++ -o foo1 tests/foo1.cpp -I . 
foo2: tests/foo2.cpp tombstones.h
	g++ -o foo2 tests/foo2.cpp -I .
foo3: tests/foo3.cpp tombstones.h
	g++ -o foo3 tests/foo3.cpp -I . 
foo4: tests/foo4.cpp tombstones.h
	g++ -o foo4 tests/foo4.cpp -I .
foo5: tests/foo5.cpp tombstones.h
	g++ -o foo5 tests/foo5.cpp -I .
foo6: tests/foo6.cpp tombstones.h
	g++ -o foo6 tests/foo6.cpp -I . 
foo7: tests/foo7.cpp tombstones.h
	g++ -o foo7 tests/foo7.cpp -I .
foo8: tests/foo8.cpp tombstones.h
	g++ -o foo8 tests/foo8.cpp -I .
