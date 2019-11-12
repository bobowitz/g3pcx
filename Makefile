build:
	gcc -O0 g3pcx.c -o test_obj_simd0.x -lm -mavx
	gcc -O1 g3pcx.c -o test_obj_simd1.x -lm -mavx

test_modu:
	gcc -O0 test_modu.c -o test_modu.x -lm -mavx

generate:
	gcc -O0 g3pcx.c -o generate0.x -lm
	gcc -O1 g3pcx.c -o generate1.x -lm
	gcc -O2 g3pcx.c -o generate2.x -lm

clean:
	rm -f *.x
	rm -f *~
