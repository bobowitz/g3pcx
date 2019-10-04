build:
	gcc -O0 *.c -o g3pcx0 -lm
	gcc -O1 *.c -o g3pcx1 -lm
	gcc -O2 *.c -o g3pcx2 -lm

clean:
	rm g3pcx0 g3pcx1 g3pcx2
