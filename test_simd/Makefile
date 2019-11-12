build:
	gcc -O0 test_obj.c -o test_obj0.x -lm
	gcc -O0 test_obj_simd.c -o test_obj_simd0.x -lm -mavx
	gcc -O1 test_obj.c -o test_obj1.x -lm
	gcc -O1 test_obj_simd.c -o test_obj_simd1.x -lm -mavx

generate:
	gcc -O0 g3pcx.c -o generate0.x -lm
	gcc -O1 g3pcx.c -o generate1.x -lm
	gcc -O2 g3pcx.c -o generate2.x -lm

clean:
	rm -f *.x
	rm -f *~
