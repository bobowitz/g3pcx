//This routine is the implementation of PCX operator and associated functions
//Do not change anything here without understanding the paper

#include <immintrin.h>
#include <math.h>

double modu_simd(__m256d x[])
{
  int j;
  __m256d mul_arr[5];
  __m256d sum_arr;
  for (j = 0; j < 5; j++)
    mul_arr[j] = _mm256_mul_pd(x[j], x[j]);
  mul_arr[0] = _mm256_hadd_pd(mul_arr[0], mul_arr[1]);
  mul_arr[2] = _mm256_hadd_pd(mul_arr[2], mul_arr[3]);
  mul_arr[1] = _mm256_hadd_pd(mul_arr[0], mul_arr[2]);
  mul_arr[3] = _mm256_hadd_pd(mul_arr[1], mul_arr[4]);
  sum_arr = _mm256_hadd_pd(mul_arr[3], mul_arr[3]);
  double sum = sum_arr[0] + sum_arr[2];
  return sqrt(sum);
}

// calculates the magnitude of a vector
double modu(double index[])
{
  int i;
  double sum,modul;
  
  sum=0.0;
  for(i=0;i<20;i++)
    sum+=(index[i]*index[i]);
  
  modul=sqrt(sum);
  return modul;
}   

