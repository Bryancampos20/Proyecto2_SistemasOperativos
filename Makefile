CC = gcc
CFLAGS = -lpthread

all: test_case1 test_case2 test_case3 test_case4 test_case5 test_case6 test_case7 test_case8

test_case1: test_case1.c node.c network.c
	$(CC) test_case1.c node.c network.c -o test_case1 $(CFLAGS)

test_case2: test_case2.c node.c
	$(CC) test_case2.c node.c -o test_case2 $(CFLAGS)

test_case3: test_case3.c node.c
	$(CC) test_case3.c node.c -o test_case3 $(CFLAGS)

test_case4: test_case4.c node.c
	$(CC) test_case4.c node.c -o test_case4 $(CFLAGS)

test_case5: test_case5.c node.c
	$(CC) test_case5.c node.c -o test_case5 $(CFLAGS)

test_case6: test_case6.c node.c
	$(CC) test_case6.c node.c -o test_case6 $(CFLAGS)

test_case7: test_case7.c node.c
	$(CC) test_case7.c node.c -o test_case7 $(CFLAGS)

test_case8: test_case8.c node.c
	$(CC) test_case8.c node.c -o test_case8 $(CFLAGS)

clean:
	rm -f test_case1 test_case2 test_case3 test_case4 test_case5 test_case6 test_case7 test_case8
