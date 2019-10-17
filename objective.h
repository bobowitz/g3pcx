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
  
  // Rosenbrock's function
  /* 1. x[j] ^ 2
   * 2. (result from 1) - x[j + 1]
   * 3. (result from 2) ^ 2
   * 4. (result from 3) * 100.0
   * 5. x[j] - 1
   * 6. fit += (result from 5) ^ 2
   * 7. add up fit
   */
#ifdef rosen_simd
  __m256d x_v[5];
  __m256d x_plus_1[5];
  __m256d tmp[5];
  __m256d c = _mm256_set_pd(100.0, 100.0, 100.0, 100.0);
  x_v[0] = _mm256_load_pd(x);
  x_v[1] = _mm256_load_pd(x + 4);
  x_v[2] = _mm256_load_pd(x + 8);
  x_v[3] = _mm256_load_pd(x + 12);
  x_v[4] = _mm256_set_pd(x[16], x[17], x[18], 0.0);

  x_plus_1[0] = _mm256_set_pd(x[1], x[2], x[3], x[4]);
  x_plus_1[1] = _mm256_set_pd(x[5], x[6], x[7], x[8]);
  x_plus_1[2] = _mm256_set_pd(x[9], x[10], x[11], x[12]);
  x_plus_1[3] = _mm256_set_pd(x[13], x[14], x[15], x[16]);
  x_plus_1[4] = _mm256_set_pd(x[17], x[18], x[19], 0.0);
  // square
  for (i = 0; i < 5; i++) 
    tmp[i] = _mm256_mul_pd(x_v[i], x_v[i]);
  // sub
  for (i = 0; i < 5; i++)
    tmp[i] = _mm256_sub_pd(tmp[i], x_plus_1[i]);
  // square
  for (i = 0; i < 5; i++) 
    tmp[i] = _mm256_mul_pd(tmp[i], tmp[i]);

  // * 100.0
  for (i = 0; i < 5; i++) 
    tmp[i] = _mm256_mul_pd(tmp[i], c);
  // - 1.0
  c = _mm256_set_pd(1.0, 1.0, 1.0, 1.0);
  for (i = 0; i < 5; i++) 
    x_v[i] = _mm256_sub_pd(x_v[i], c);
  // add
  for (i = 0; i < 5; i++) 
    x_v[i] = _mm256_add_pd(x_v[i], tmp[i]);

  x_v[0] = _mm256_add_pd(x_v[0], x_v[1]);
  x_v[2] = _mm256_add_pd(x_v[2], x_v[3]);
  x_v[0] = _mm256_add_pd(x_v[0], x_v[4]);
  x_v[0] = _mm256_add_pd(x_v[0], x_v[2]);

  fit += x_v[0][0] + x_v[0][1] + x_v[0][2] + x_v[0][3];
#else
  #ifdef rosen
  for(j=0; j<MAXV-1; j++)
    fit += 100.0*(x[j]*x[j] - x[j+1])*(x[j]*x[j] - x[j+1]) + (x[j]-1.0)*(x[j]-1.0);
  
  #endif
#endif
  
  return(fit);
}
