all: mid19 unit_test

mid19: mid19.cpp
	g++ -Wall mid19.cpp -o mid19;
unit_test: mid19.cpp
	g++ -Wall mid19.cpp -DUNIT_TEST -o unit_test
clean:
	rm mid19 unit_test