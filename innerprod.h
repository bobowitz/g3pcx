// calculates the inner product of two vectors
#include <immintrin.h>

double innerprod_simd(__m256d ind1[],__m256d ind2[])
{
//  time_innerprod++;
//  unsigned long long start = rdtsc();
  int i;
  double sum_out;
  
  __m256d sum[5];
  __m256d sum_arr;

  for(i=0;i<5;i++)
    sum[i] = _mm256_mul_pd(ind1[i], ind2[i]);

  sum[0] = _mm256_hadd_pd(sum[0], sum[1]);
  sum[2] = _mm256_hadd_pd(sum[2], sum[3]);
  sum[1] = _mm256_hadd_pd(sum[0], sum[2]);
  sum[3] = _mm256_hadd_pd(sum[1], sum[4]);
  sum_arr = _mm256_hadd_pd(sum[3], sum[4]);
  sum_out = sum_arr[0] + sum_arr[2];
  
//  count_innerprod += rdtsc() - start;
  return sum_out;
}  

double innerprod(double ind1[], double ind2[])
{
  int i;
  double sum = 0.0;

  for (i = 0; i < 20; i++) {
    sum += (ind1[i] * ind2[i]);
  }

  return sum;
}

__m256d innerprod_simdx(__m256d ind1[], __m256d ind2[])
{
  int i;
  __m256d psum[5];
  for (i = 0; i < 5; i++) psum[i] = _mm256_set_pd(0.0, 0.0, 0.0, 0.0);

  for (i = 0; i < 20; i += 5) {
    psum[0] = _mm256_fmadd_pd(ind1[i], ind2[i], psum[0]);
    psum[1] = _mm256_fmadd_pd(ind1[i + 1], ind2[i + 1], psum[1]);
    psum[2] = _mm256_fmadd_pd(ind1[i + 2], ind2[i + 2], psum[2]);
    psum[3] = _mm256_fmadd_pd(ind1[i + 3], ind2[i + 3], psum[3]);
    psum[4] = _mm256_fmadd_pd(ind1[i + 4], ind2[i + 4], psum[4]);
  }
  psum[0] = _mm256_add_pd(psum[0], psum[1]);
  psum[2] = _mm256_add_pd(psum[2], psum[3]);
  psum[4] = _mm256_add_pd(psum[0], psum[4]);

  return _mm256_add_pd(psum[2], psum[4]);
}
