//This routine calculates the objective function
//Code your objective function here

#include <immintrin.h>

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
  
#ifdef schwefel_opt
  // Schwefel's function (optimized)
  sumSCH = 0;
  for(j=0; j<MAXV-1; j++)
    {
      sumSCH += x[j];
      fit += sumSCH * sumSCH;
    }
#endif

#ifdef schwefel_opt2
  // Schwefel's function (SIMD)
  __m256d vsumSCH = _mm256_set_pd(x[0], x[5], x[10], x[15]);
  __m256d squared = _mm256_set_pd(0.0, 0.0, 0.0, 0.0);
  __m256d xpack[0];
  xpack[0] = _mm256_set_pd(x[1], x[6], x[11], x[16]);
  xpack[1] = _mm256_set_pd(x[2], x[7], x[12], x[17]);
  xpack[2] = _mm256_set_pd(x[3], x[8], x[13], x[18]);
  xpack[3] = _mm256_set_pd(x[4], x[9], x[14], 0.0);
  
  squared = _mm256_add_pd(squared, _mm256_mul_pd(vsumSCH, vsumSCH));
  _mm256_add_pd(vsumSCH, xpack[0]);
  squared = _mm256_add_pd(squared, _mm256_mul_pd(vsumSCH, vsumSCH));
  _mm256_add_pd(vsumSCH, xpack[1]);
  squared = _mm256_add_pd(squared, _mm256_mul_pd(vsumSCH, vsumSCH));
  _mm256_add_pd(vsumSCH, xpack[2]);
  squared = _mm256_add_pd(squared, _mm256_mul_pd(vsumSCH, vsumSCH));
  _mm256_add_pd(vsumSCH, xpack[3]);
  squared = _mm256_hadd_pd(squared, squared);
  double vfit[4];
  _mm256_store_pd(vfit, squared);
  fit = vfit[0] + vfit[2];
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
