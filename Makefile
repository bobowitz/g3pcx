build:
	gcc -O0 *.c -o bin/g3pcx0 -lm
	gcc -O1 *.c -o bin/g3pcx1 -lm
	gcc -O2 *.c -o bin/g3pcx2 -lm

clean:
	rm bin/*
