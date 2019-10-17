build:
	gcc -O0 test_obj.c -o test_obj0.x -lm
	gcc -O0 test_obj_simd.c -o test_obj_simd0.x -lm -mavx
	gcc -O1 test_obj.c -o test_obj1.x -lm
	gcc -O1 test_obj_simd.c -o test_obj_simd1.x -lm -mavx

clean:
	rm *.x
	rm *~
