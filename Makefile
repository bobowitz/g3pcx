build:
	gcc -O0 *.c -o bin/g3pcx0 -lm -mavx
	gcc -O1 *.c -o bin/g3pcx1 -lm -mavx
	gcc -O2 *.c -o bin/g3pcx2 -lm -mavx
	gcc -O3 *.c -o bin/g3pcx3 -lm -mavx

clean:
	rm bin/*

