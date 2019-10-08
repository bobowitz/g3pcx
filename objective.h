//This routine calculates the objective function
//Code your objective function here

#include <immintrin.h>	  // for simd instructions and data type
#include "simd_macro.h"  // instruction macros
#include "asm_functions.h" // functions with a set of asm

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
   * 4. fit += (result from 3) * 100.0
   * 5. x[j] - 1
   * 6. fit += (result from 5) ^ 2
   */
  double *x_mm = _mm_malloc(8 * MAXV, 32);
  for (j = 0; j < MAXV; j++) x_mm[j] = x[j];
  rosen_vmovapd(x_mm);
  // step1. x[j] ^ 2
  rosen_sq_1();
  // step2. subtract from x[j + 1]
  rosen_sub_2();
  // step3. square
  rosen_sq_3();


  
//  for(j=0; j<MAXV-1; j++)
//    fit += 100.0*(x[j]*x[j] - x[j+1])*(x[j]*x[j] - x[j+1]) + (x[j]-1.0)*(x[j]-1.0);

  _mm_free(x_mm);
#endif
  
  return(fit);
}
