//This routine calculates the objective function
//Code your objective function here

#include <immintrin.h>	  // for simd instructions and data type
#include "simd_macro.h"  // instruction macros
#include "asm_functions.h" // functions with a set of asm

#define fast

double objective();

double  objective(x)
     double *x;
{
  int i,j,k;
  double fit, sumSCH;
  
  fit=0.0;
  
#ifdef ellip
  // Ellipsoidal function
  for(j=0;j<MAXV;j++)
    fit+=((j+1)*(x[j]*x[j]));
#endif
  
#ifdef schwefel
  // Schwefel's function
  for(j=0; j<MAXV; j++)
    {
      for(i=0,sumSCH=0.0; i<j; i++)
	sumSCH += x[i];
      fit += sumSCH * sumSCH;
    }
#endif
  
#ifdef rosen
  // Rosenbrock's function
  /* 1. x[j] ^ 2
   * 2. (result from 1) - x[j + 1]
   * 3. (result from 2) ^ 2
   * 4. (result from 3) * 100.0
   * 5. x[j] - 1
   * 6. fit += (result from 5) ^ 2
   * 7. add up fit
   */
  #ifdef fast
  double *x_mm = _mm_malloc(8 * MAXV, 32);
  fit = -1.0;

  for (j = 0; j < MAXV; j++) x_mm[j] = x[j];
  rosen_vmovapd(x_mm);
  // step1. x[j] ^ 2
  rosen_sq_1();
  // step2. subtract from x[j + 1]
  rosen_sub_2();
  // step3. square
  rosen_sq_3();
  
  rosen_mov_100_1();

  // step4. * 100.0
  rosen_mul_4();
  // step5. x[j] - 1
  rosen_sub_5();
  // step6. fma
  rosen_fma_6();
  // step7. add up
  rosen_add_7();
  // final add up in C
  rosen_vmovapd_out(x_mm);
  for (j = 0; j < 4; j++)
	fit += x_mm[j];
  _mm_free(x_mm);
  
  #else 
  for(j=0; j<MAXV-1; j++)
    fit += 100.0*(x[j]*x[j] - x[j+1])*(x[j]*x[j] - x[j+1]) + (x[j]-1.0)*(x[j]-1.0);

  #endif
#endif
  
  return(fit);
}
