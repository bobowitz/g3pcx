//This routine calculates the objective function
//Code your objective function here

#include <immintrin.h>	  // for simd instructions and data type

unsigned long long obj_count = 0;
unsigned long long time = 0;

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
  /* 0. fit = 19.0
   * 1. x[j] ^ 2
   * 2. fit += (result from 1) - 2 * x[j]
   * 3. (result from 1) - x[j + 1]
   * 4. (result from 3) ^ 2
   * 5. fit += (result from 4) * 100.0
   */
#ifdef rosen_simd
  __m256d x_v[5];
  __m256d x_plus_1[5];
  __m256d second[5];
  __m256d c;
  fit = 19.0;

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
  // -2 * x[j]
  c = _mm256_set_pd(-2.0, -2.0, -2.0, -2.0);
  second[0] = _mm256_mul_pd(x_v[0], c);
  second[1] = _mm256_mul_pd(x_v[1], c);
  second[2] = _mm256_mul_pd(x_v[2], c);
  second[3] = _mm256_mul_pd(x_v[3], c);
  second[4] = _mm256_mul_pd(x_v[4], c);
  // square
  x_v[0] = _mm256_mul_pd(x_v[0], x_v[0]);
  x_v[1] = _mm256_mul_pd(x_v[1], x_v[1]);
  x_v[2] = _mm256_mul_pd(x_v[2], x_v[2]);
  x_v[3] = _mm256_mul_pd(x_v[3], x_v[3]);
  x_v[4] = _mm256_mul_pd(x_v[4], x_v[4]);

  second[0] = _mm256_add_pd(second[0], x_v[0]);
  second[1] = _mm256_add_pd(second[1], x_v[1]);
  second[2] = _mm256_add_pd(second[2], x_v[2]);
  second[3] = _mm256_add_pd(second[3], x_v[3]);
  second[4] = _mm256_add_pd(second[4], x_v[4]);

  
  // sub x[j + 1]
  x_v[0] = _mm256_sub_pd(x_v[0], x_plus_1[0]);
  x_v[1] = _mm256_sub_pd(x_v[1], x_plus_1[1]);
  x_v[2] = _mm256_sub_pd(x_v[2], x_plus_1[2]);
  x_v[3] = _mm256_sub_pd(x_v[3], x_plus_1[3]);
  x_v[4] = _mm256_sub_pd(x_v[4], x_plus_1[4]);
  // square
  x_v[0] = _mm256_mul_pd(x_v[0], x_v[0]);
  x_v[1] = _mm256_mul_pd(x_v[1], x_v[1]);
  x_v[2] = _mm256_mul_pd(x_v[2], x_v[2]);
  x_v[3] = _mm256_mul_pd(x_v[3], x_v[3]);
  x_v[4] = _mm256_mul_pd(x_v[4], x_v[4]);

  // * 100.0
  c = _mm256_set_pd(100.0, 100.0, 100.0, 100.0);
  x_v[0] = _mm256_mul_pd(x_v[0], c);
  x_v[1] = _mm256_mul_pd(x_v[1], c);
  x_v[2] = _mm256_mul_pd(x_v[2], c);
  x_v[3] = _mm256_mul_pd(x_v[3], c);
  x_v[4] = _mm256_mul_pd(x_v[4], c);
  
  second[0] = _mm256_add_pd(second[0], second[1]);
  second[2] = _mm256_add_pd(second[2], second[3]);
  second[0] = _mm256_add_pd(second[0], second[4]);
  second[0] = _mm256_add_pd(second[0], second[2]);

  x_v[0] = _mm256_add_pd(x_v[0], x_v[1]);
  x_v[2] = _mm256_add_pd(x_v[2], x_v[3]);
  x_v[0] = _mm256_add_pd(x_v[0], x_v[4]);
  x_v[0] = _mm256_add_pd(x_v[0], x_v[2]);

  fit += second[0][0] + second[0][1] + second[0][2] + second[0][3];
  fit += x_v[0][0] + x_v[0][1] + x_v[0][2] + x_v[0][3];
#else
  #ifdef rosen
  time++;
  unsigned long long start = rdtsc();
  for(j=0; j<MAXV-1; j++) 
    fit += 100.0*(x[j]*x[j] - x[j+1])*(x[j]*x[j] - x[j+1]) + (x[j]-1.0)*(x[j]-1.0);
  obj_count += rdtsc() - start;
  #endif
#endif
  
  return(fit);
}
