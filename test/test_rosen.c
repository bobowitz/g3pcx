#include <stdio.h>
#include <immintrin.h>
#include "../simd_macro.h"
#include "../asm_functions.h"
#define MAXV 20

int main()
{
  double *x = _mm_malloc(8 * MAXV, 32);
  int j;
  double sum = -1.0;
  double x_test[20];
  double sum_test = 0.0; 


  for (j = 0; j < MAXV + 1; j++) x[j] = (double) j;
  rosen_vmovapd(x);
  // step1. x[j] ^ 2
  square_ymm0toymm1; 
  square_ymm3toymm4; 
  square_ymm6toymm7; 
  square_ymm9toymm10; 
  square_ymm12toymm13;
  // step2. subtract from x[j + 1]
  sub_ymm1_ymm2;
  sub_ymm4_ymm5;
  sub_ymm7_ymm8;
  sub_ymm10_ymm11;
  sub_ymm13_ymm14;
  // step3. square 
  square_ymm1;
  square_ymm4;
  square_ymm7;
  square_ymm10;
  square_ymm13; 
  rosen_mov_100_1();

  // step4. mul
  rosen_mul_4();
  rosen_sub_5();
  rosen_fma_6();
  rosen_add_7();
  rosen_vmovapd_out(x);
  for (j = 0; j < 4; j++)
    sum += x[j];
  printf("sum = %lf\n", sum);

  for (j = 0; j < 20; j++) x[j] = j;
  for (j = 0; j < 19; j++) {
    sum_test += 100.0 * (x[j] * x[j] - x[j + 1]) * (x[j] * x[j] - x[j + 1]) + (x[j] - 1) * (x[j] - 1);
  }
  printf("sum_test = %lf\n", sum_test);
  if (sum == sum_test)
  	printf("success!\n");
  else 
    printf("fail!\n");

  return 0;	
}
