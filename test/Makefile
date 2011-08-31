# Copyright (c) 2011 Alexander Poluektov (alexander.poluektov@gmail.com)
#
# Use, modification and distribution are subject to the
# Boost Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

all: algorithm_test
	./algorithm_test

algorithm_test: algorithm_test.o
	g++ algorithm_test.o -o algorithm_test -lboost_unit_test_framework

algorithm_test.o: algorithm_test.cpp
	g++ -I../include -c -Wall algorithm_test.cpp

clean:
	rm -rf *o hello
