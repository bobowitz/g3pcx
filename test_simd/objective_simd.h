//This routine calculates the objective function
//Code your objective function here

double objective();

double  objective(x)
     __m256d *x;
{
  int i,j,k;
  double fit, sumSCH;
  
  fit=0.0;
  
#ifdef ellip
  // Ellipsoidal function
  for(j=0;j<MAXV;j++)
    fit+=((j+1)*(x[j]*x[j]));
#endif

#ifdef ellip_simd
  // Ellipsoidal with simd
  __m256d mul_arr[5];
  __m256d fit_arr;
 for (j = 0; j < 5; j++)
   mul_arr[j] = _mm256_mul_pd(x[j], x[j]);
 for (j = 0; j < 5; j++)
   mul_arr[j] = _mm256_mul_pd(mul_arr[j], step_arr[j]);
 mul_arr[0] = _mm256_hadd_pd(mul_arr[0], mul_arr[1]);
 mul_arr[2] = _mm256_hadd_pd(mul_arr[2], mul_arr[3]);
 mul_arr[1] = _mm256_hadd_pd(mul_arr[0], mul_arr[2]);
 mul_arr[3] = _mm256_hadd_pd(mul_arr[1], mul_arr[4]);
 fit_arr = _mm256_hadd_pd(mul_arr[3], mul_arr[3]);
 fit = fit_arr[0] + fit_arr[2]; // Can also use indices 1 and 3.
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
  for(j=0; j<MAXV-1; j++)
    fit += 100.0*(x[j]*x[j] - x[j+1])*(x[j]*x[j] - x[j+1]) + (x[j]-1.0)*(x[j]-1.0);
#endif
  
  return(fit);
}
