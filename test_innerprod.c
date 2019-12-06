#include "innerprod.h"  
#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include "fast_code_utils.h"

int main()
{
  int i, j;
  unsigned long long start_t, end_t, cycles = 0.0;
  double exec_time = 0.0;

  volatile double* volatile vector[1000];
  volatile __m256d* volatile vector_simd[1000];
  volatile __m256d* volatile vector_simdx[1000];
  for (i = 0; i < 1000; i++){
    vector[i] = malloc(sizeof(double) * 20);
    posix_memalign(&vector_simd[i], 32, sizeof(__m256d) * 5);
    posix_memalign(&vector_simdx[i], 32, sizeof(__m256d) * 20);
    for (j = 0; j < 20; j++)
      vector[i][j] = (double) j;
    for (j = 0; j < 20; j+=4)
      vector_simd[i][j / 4] =
          _mm256_setr_pd((double) j,   (double) j+1,
                         (double) j+2, (double) j+3);
    for (j = 0; j < 20; j++)
      vector_simdx[i][j] =
          _mm256_setr_pd((double) j, (double) j,
                         (double) j, (double) j);
  }

  double res = 0.0;
  double res_simd = 0.0;
  __m256d res_simdx = _mm256_set_pd(0.01, 0.01, 0.01, 0.01);
  long s_overhead = 0;
  long v_overhead = 0;

  start_t = rdtsc();
  for (j = 0; j < 1000; j++) res += j;
  end_t = rdtsc();

  s_overhead = end_t - start_t;
  printf("Scalar overhead: %d, %u cycles\n", j, end_t - start_t);
  
  start_t = rdtsc();
  for (j = 0; j < 1000; j++) res_simdx = _mm256_add_pd(res_simdx, res_simdx);
  end_t = rdtsc();
  
  v_overhead = end_t - start_t;
  printf("SIMD overhead: %f, %u cycles\n", ((double*) &res_simdx)[1], end_t - start_t);

  res = 0.0;
  res_simd = 0.0;
  res_simdx = _mm256_set_pd(0.0, 0.0, 0.0, 0.0);

  start_t = rdtsc();
  for (j = 0; j < 1000; j++) res += innerprod(vector[j], vector[j]);
  end_t = rdtsc();

  cycles = (end_t - start_t - s_overhead) * 3.4 / 2400;
  printf("Magnitude in       %u cycles.\n", cycles);
  
  start_t = rdtsc();
  for (j = 0; j < 1000; j++) res_simd += innerprod_simd(vector_simd[j], vector_simd[j]);
  end_t = rdtsc();

  cycles = (end_t - start_t - s_overhead) * 3.4 / 2400;
  printf("Magnitude SIMD in  %u cycles.\n", cycles);

  start_t = rdtsc();
  for (j = 0; j < 1000; j++) res_simdx = _mm256_add_pd(res_simdx, innerprod_simdx(vector_simdx[j], vector_simdx[j]));
  end_t = rdtsc();

  cycles = (end_t - start_t - v_overhead) * 3.4 / 2400;
  printf("Magnitude SIMDX in %u cycles.\n", cycles);
  printf("Results: %f, %f, %f\n", res, res_simd, ((double *) &res_simdx)[0]);

  return 0;
}

