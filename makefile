run:
	gcc main.c DLL-functions.c operations.c pre-functions.c -o main


testadd:
	./main 1000 + 2000;
	./main -1000 + 2000;
	./main 1000 + -2000;
	./main -1000 + -2000;

testsub:
	./main 1000 - 2000;
	./main -1000 - 2000;
	./main 1000 - -2000;
	./main -1000 - -2000;

testmul:
	./main 1000 x 2000;
	./main 1000 x -2000;
	./main -1000 x 2000;
	./main -1000 x -2000;

testdiv:
	./main 1000 / 1000;
	./main 2000 / -1000;
	./main -2000 / 1000;
	./main -2000 / -1000;
	./main 1234 / 12;
	./main 1000 / 10;
	./main 9999 / 9;
	./main 123 / 5;
	./main 7 / 9;
	./main 100 / 3;
	./main 10000 / 100;
	./main 123456789 / 123;


testerror:
	./main 1234 + 12b;
	./main 1ab4 + 12b;
	./main 1234 - 12b;
	./main 1AB4 x 123;

testall:
	./main 1234 + 123;
	./main 1234 - 123;
	./main 1234 x 123;
	./main 1234 / 123;
	./main +1234 + +123;
	./main +1234 - +123;
	./main +1234 x +123;
	./main +1234 / +123;
	./main -1234 + +123;
	./main -1234 - +123;
	./main -1234 x +123;
	./main -1234 / +123;
	./main -1234 + -123;
	./main -1234 - -123;
	./main -1234 x -123;
	./main -1234 / -123;
	./main +1234 + -123;
	./main +1234 - -123;
	./main +1234 x -123;
	./main +1234 / -123;
	./main 123 + 1234;
	./main 123 - 1234;
	./main 123 x 1234;
	./main 123 / 1234;
	./main +123 + +1234;
	./main +123 - +1234;
	./main +123 x +1234;
	./main +123 / +1234;
	./main +123 + -1234;
	./main +123 - -1234;
	./main +123 x -1234;
	./main +123 / -1234;
	./main -123 + -1234;
	./main -123 - -1234;
	./main -123 x -1234;
	./main -123 / -1234;
	./main -123 + +1234;
	./main -123 - +1234;
	./main -123 x +1234;
	./main -123 / +1234;
	./main 99 + 1;
	./main +99 + +1;
	./main -99 + +1;
	./main +99 + -1;
	./main -99 + -1;
	./main 999 + 1;
	./main +999 + +1;
	./main -999 + +1;
	./main +999 + -1;
	./main -999 + -1;
	./main 100 - 1;
	./main +100 - +1;
	./main +100 - -1;
	./main -100 - -1;
	./main -100 - +1;
	./main 0 x 100;
	./main 0 x +100;
	./main 0 x -100;
	./main 100 x 0;
	./main +100 x 0;
	./main -100 x 0;
	./main 1000 / 10;
	./main -100000 / 10;
	./main -10000000 / 10;
	./main 1000000000 / -10;
	./main 100000000000 / -10;
	./main 0 / 123;

dividebyzero:
	./main 1234 / 0;