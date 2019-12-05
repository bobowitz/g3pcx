//This routine calculates the objective function
//Code your objective function here

__m256d objective();

__m256d objective(x)
     __m256d *x;
{
  int i,j;
  double zero = 0.0;
  
#ifdef ellip
  // Ellipsoidal function
  for(j=0;j<MAXV;j++)
    fit+=((j+1)*(x[j]*x[j]));
#endif

#ifdef ellip_simd
  // Ellipsoidal with simd
  __m256d mul_arr[5];
  __m256d fit_arr[5];
  __m256d fits;
  
  for (i = 0; i < 5; i++)
    fit_arr[i] = _mm256_broadcast_sd(&zero);
  for (j = 0; j < MAXV; j+=5) {
    mul_arr[0] = _mm256_mul_pd(x[j], x[j]);
    mul_arr[1] = _mm256_mul_pd(x[j+1], x[j+1]);
    mul_arr[2] = _mm256_mul_pd(x[j+2], x[j+2]);
    mul_arr[3] = _mm256_mul_pd(x[j+3], x[j+3]);
    mul_arr[4] = _mm256_mul_pd(x[j+4], x[j+4]);
    fit_arr[0] = _mm256_fmadd_pd(mul_arr[0], step_arr[j], fit_arr[0]);
    fit_arr[1] = _mm256_fmadd_pd(mul_arr[1], step_arr[j+1], fit_arr[1]);
    fit_arr[2] = _mm256_fmadd_pd(mul_arr[2], step_arr[j+2], fit_arr[2]);
    fit_arr[3] = _mm256_fmadd_pd(mul_arr[3], step_arr[j+3], fit_arr[3]);
    fit_arr[4] = _mm256_fmadd_pd(mul_arr[4], step_arr[j+3], fit_arr[4]);
  }
  fit_arr[0] = _mm256_add_pd(fit_arr[0], fit_arr[1]);
  fit_arr[2] = _mm256_add_pd(fit_arr[2], fit_arr[3]);
  fit_arr[1] = _mm256_add_pd(fit_arr[0], fit_arr[4]);

  fits = _mm256_add_pd(fit_arr[1], fit_arr[2]);
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
  
  return fits;
}

double objective1(__m256d *x) {
  int j;
  // Ellipsoidal with simd
  __m256d mul_arr[5];
  __m256d fit_arr;
  double fit;

  for (j = 0; j < 5; j++)
    mul_arr[j] = _mm256_mul_pd(x[j], x[j]);
  for (j = 0; j < 5; j++)
    mul_arr[j] = _mm256_mul_pd(mul_arr[j], step_arr[j]);
  mul_arr[0] = _mm256_add_pd(mul_arr[0], mul_arr[1]);
  mul_arr[2] = _mm256_add_pd(mul_arr[2], mul_arr[3]);
  mul_arr[1] = _mm256_add_pd(mul_arr[0], mul_arr[2]);
  mul_arr[3] = _mm256_add_pd(mul_arr[1], mul_arr[4]);
  fit_arr = _mm256_hadd_pd(mul_arr[3], mul_arr[3]);
  fit = fit_arr[0] + fit_arr[2];

  return fit;
}

__m256d objective2(__m256d *x, __m256d *y) {
  int j;
  double fit, zero = 0.0;
  __m256d mul_arr[2];
  __m256d fit_arr[2];
  double fit_totals[4];
  __m256d fits;
  
  fit_arr[0] = _mm256_broadcast_sd(&zero);
  fit_arr[1] = _mm256_broadcast_sd(&zero);
  for (j = 0; j < 5; j++) {
    mul_arr[0] = _mm256_mul_pd(x[j], x[j]);
    mul_arr[1] = _mm256_mul_pd(y[j], y[j]);
    fit_arr[0] = _mm256_fmadd_pd(mul_arr[0], step_arr[j], fit_arr[0]);
    fit_arr[1] = _mm256_fmadd_pd(mul_arr[1], step_arr[j], fit_arr[1]);
  }
  fit_arr[0] = _mm256_hadd_pd(fit_arr[0], fit_arr[0]);
  fit_arr[1] = _mm256_hadd_pd(fit_arr[1], fit_arr[1]);

  fit_totals[0] = fit_arr[0][0] + fit_arr[0][2];
  fit_totals[1] = fit_arr[1][0] + fit_arr[1][2];
  fit_totals[2] = 0.0;
  fit_totals[3] = 0.0;
  // Can also use indices 1 and 3 within each array.

  fits = _mm256_loadu_pd(fit_totals);
  return fits;
}
