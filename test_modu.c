#include "modu.h" //generates a child from participating parents:PCX 
#include <stdio.h>
#include <immintrin.h>
#include "fast_code_utils.h"
#include <math.h>

main()
{
  int j;
  unsigned long long start_t, end_t, cycles = 0.0;
  double exec_time = 0.0;
  
  double vector[20];
  __m256d vector_simd[5];
  for (j = 0; j < 20; j++)
    vector[j] = (double) j;
  for (j = 0; j < 20; j+=4)
    vector_simd[j / 4] =
        _mm256_setr_pd((double) j,   (double) j+1,
                       (double) j+2, (double) j+3);

  printf("%f, %f\n", modu(vector), modu_simd(vector_simd));

  double res = 0.0;
  double res_simd = 0.0;

  start_t = rdtsc();
  for (j = 0; j < 1000; j++) res += modu(vector);
  end_t = rdtsc();

  cycles = end_t - start_t;
  exec_time = cycles * 3.4 / 2400000000;
  printf("Magnitude in      %u cycles or %f seconds.\n", cycles, exec_time);
  
  start_t = rdtsc();
  for (j = 0; j < 1000; j++) res_simd += modu_simd(vector_simd);
  end_t = rdtsc();

  cycles = end_t - start_t;
  exec_time = cycles * 3.4 / 2400000000;
  printf("Magnitude SIMD in %u cycles or %f seconds.\n", cycles, exec_time);
  printf("Results: %f, %f\n", res, res_simd);
}

