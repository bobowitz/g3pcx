build:
	gcc -mavx -O0 *.c -o bin/g3pcx0 -lm
	gcc -mavx -O1 *.c -o bin/g3pcx1 -lm
	gcc -funroll-loops -mavx -O2 *.c -o bin/g3pcx2 -lm

clean:
	rm bin/*
