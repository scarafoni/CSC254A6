FOOS=foo1 foo2 foo3 foo4 foo5 foo6 foo7 foo8
TESTS=test1 test2 test3 test4 test5 test6 test7 test8

all: $(FOOS)

test: $(TESTS)

foo%: tests/foo%.cpp tombstones.h
	g++ $< -I . -o $@

test%: foo%
	./$<

clean:
	rm $(FOOS)
