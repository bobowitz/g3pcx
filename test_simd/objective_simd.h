//This routine calculates the objective function
//Code your objective function here

__m256d objective();

__m256d objective(w,x,y,z)
     __m256d *w;
     __m256d *x;
     __m256d *y;
     __m256d *z;
{
  int i,j;
  double fit, zero = 0.0;
  
  fit=0.0;
  
#ifdef ellip
  // Ellipsoidal function
  for(j=0;j<MAXV;j++)
    fit+=((j+1)*(x[j]*x[j]));
#endif

#ifdef ellip_simd
  // Ellipsoidal with simd
  __m256d mul_arr[4];
  __m256d fit_arr[4];
  double fit_totals[4];
  __m256d fits;
  
  for (i = 0; i < 4; i++)
    fit_arr[i] = _mm256_broadcast_sd(&zero);
  for (j = 0; j < 5; j++) {
    mul_arr[0] = _mm256_mul_pd(w[j], w[j]);
    mul_arr[1] = _mm256_mul_pd(x[j], x[j]);
    mul_arr[2] = _mm256_mul_pd(y[j], y[j]);
    mul_arr[3] = _mm256_mul_pd(z[j], z[j]);
    fit_arr[0] = _mm256_fmadd_pd(mul_arr[0], step_arr[j], fit_arr[0]);
    fit_arr[1] = _mm256_fmadd_pd(mul_arr[1], step_arr[j], fit_arr[1]);
    fit_arr[2] = _mm256_fmadd_pd(mul_arr[2], step_arr[j], fit_arr[2]);
    fit_arr[3] = _mm256_fmadd_pd(mul_arr[3], step_arr[j], fit_arr[3]);
  }
  fit_arr[0] = _mm256_hadd_pd(fit_arr[0], fit_arr[0]);
  fit_arr[1] = _mm256_hadd_pd(fit_arr[1], fit_arr[1]);
  fit_arr[2] = _mm256_hadd_pd(fit_arr[2], fit_arr[2]);
  fit_arr[3] = _mm256_hadd_pd(fit_arr[3], fit_arr[3]);

  for (i = 0; i < 4; i++)
    fit_totals[i] = fit_arr[i][0] + fit_arr[i][2];
  // Can also use indices 1 and 3 within each array.

  fits = _mm256_loadu_pd(fit_totals);
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
