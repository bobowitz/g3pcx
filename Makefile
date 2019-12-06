build:
	gcc -O0 g3pcx.c -o test_obj_simd0.x -lm -mavx -mfma
	gcc -O1 g3pcx.c -o test_obj_simd1.x -lm -mavx -mfma
	gcc -O2 g3pcx.c -o test_obj_simd2.x -lm -mavx -mfma

test_modu:
	gcc -O0 test_modu.c -o test_modu0.x -lm -mavx -mfma
	gcc -O1 test_modu.c -o test_modu1.x -lm -mavx -mfma
	gcc -O2 test_modu.c -o test_modu2.x -lm -mavx -mfma
	gcc -O3 test_modu.c -o test_modu3.x -lm -mavx -mfma

test_innerprod:
	gcc -O0 test_innerprod.c -o test_innerprod0.x -lm -mavx -mfma
	gcc -O1 test_innerprod.c -o test_innerprod1.x -lm -mavx -mfma
	gcc -O2 test_innerprod.c -o test_innerprod2.x -lm -mavx -mfma
	gcc -O3 test_innerprod.c -o test_innerprod3.x -lm -mavx -mfma

generate:
	gcc -O0 g3pcx.c -o generate0.x -lm
	gcc -O1 g3pcx.c -o generate1.x -lm
	gcc -O2 g3pcx.c -o generate2.x -lm

clean:
	rm -f *.x
	rm -f *~
