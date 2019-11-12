//This routine is the implementation of PCX operator and associated functions
//Do not change anything here without understanding the paper

#include "modu.h"

double innerprod(double ind1[],double ind2[]); //gives innerproduct of 2 input vectors
int generate_new(int h); //main routine here

unsigned long long time_cent = 0;
unsigned long long count_cent = 0;
/*
unsigned long long time_innerprod = 0;
unsigned long long count_innerprod = 0;
unsigned long long time_modu = 0;
unsigned long long count_modu = 0;
*/

int generate_new(int pass)
{
  int i,j,num,k;
  double Centroid[MAXV];
  double tempvar,tempsum,D_not,dist;
  double tempar1[MAXV];
  double tempar2[MAXV];
  double D[RandParent];
  double d[MAXV];
  double diff[RandParent][MAXV];
  double temp1,temp2,temp3; 
  int temp;

  int arr1_0 = arr1[0];
  int arr1_j;
  #ifdef centroid_simd
  time_cent++;
  unsigned long long start = rdtsc();

  __m256d centroid_pd[5];
  __m256d *vari[3];

  vari[0] = oldpop[arr1[0]].vari;
  vari[1] = oldpop[arr1[1]].vari;
  vari[2] = oldpop[arr1[2]].vari;
  for (i = 0; i < 5; i++) {
    centroid_pd[i] = _mm256_add_pd(vari[0][i], vari[1][i]);
  }
  
  for (i = 0; i < 5; i++) {
    centroid_pd[i] = _mm256_add_pd(vari[2][i], centroid_pd[i]);
  }
  
  __m256d c = _mm256_set_pd(3.0, 3.0, 3.0, 3.0);

  for (i = 0; i < 5; i++) {
    centroid_pd[i] = _mm256_div_pd(centroid_pd[i], c);
  }
 /* 
  _mm256_store_pd(Centroid, centroid_pd[0]);
  _mm256_store_pd(Centroid + 4, centroid_pd[1]);
  _mm256_store_pd(Centroid + 8, centroid_pd[2]);
  _mm256_store_pd(Centroid + 12, centroid_pd[3]);
  _mm256_store_pd(Centroid + 16, centroid_pd[4]);
  */

  // calculate the distace (d) from centroid to the index parent arr1[0]  
  // also distance (diff) between index and other parents are computed
  __m256d d_v[5];
  __m256d diff_v[RandParent][5];
  for (i = 0; i < 5; i++) {
    d_v[i] = _mm256_sub_pd(centroid_pd[i], vari[0][i]);
  }
  // store in (double *) d
  _mm256_store_pd(d, d_v[0]);
  _mm256_store_pd(d + 4, d_v[1]);
  _mm256_store_pd(d + 8, d_v[2]);
  _mm256_store_pd(d + 12, d_v[3]);
  _mm256_store_pd(d + 16, d_v[4]);

  for(j = 1; j < RandParent; j++) {
    for(i = 0; i < 5; i++)
      diff_v[j][i] = _mm256_sub_pd(vari[j][i], vari[0][i]);
    if (modu_simd(diff_v[j]) < EPSILON) {	
      #ifdef PRINTF
      printf("RUN=%d, Points are very close to each other. Quitting this run.\n",RUN);
      #endif
      return (0);
    }
  }
  count_cent += rdtsc() - start;
  #else
  time_cent++;
  unsigned long long start = rdtsc();
  for(i = 0; i < MAXV; i++) 
    Centroid[i] = 0.0;

  for (i = 0; i < MAXV; i++) {
    for (j = 0; j < RandParent; j++)
	  Centroid[i] += oldpop[arr1[j]].vari[i];
    Centroid[i] /= RandParent;
  }
  for(j = 1; j < RandParent; j++) {
    for (i = 0; i < MAXV; i++) {
      if (j == 1)
	    d[i] = Centroid[i] - oldpop[arr1[0]].vari[i];
      diff[j][i] = oldpop[arr1[j]].vari[i] - oldpop[arr1[0]].vari[i];
	}
    if (modu(diff[j]) < EPSILON) {	
      #ifdef PRINTF
	    printf("RUN=%d, Points are very close to each other. Quitting this run.\n",RUN);
      #endif
	  return (0);
	}
  }
  count_cent += rdtsc() - start;
  #endif

  dist=modu_simd(d_v); // modu calculates the magnitude of the vector
  
  if (dist < EPSILON) 
    {
      #ifdef PRINTF
      printf("RUN=%d, Points are very close to each other. Quitting this run.\n",RUN);
      #endif
      return (0);
    }
  
  // orthogonal directions are computed (see the paper)
  for(i=1;i<RandParent;i++)
    {
      temp1=innerprod(diff[i],d);
      temp2=temp1/(modu_simd(diff_v[i])*dist);
      temp3=1.0-pow(temp2,2.0);
      D[i]=modu_simd(diff_v[i])*sqrt(temp3);
    }
  
  D_not=0;
  for(i=1;i<RandParent;i++)
    D_not+=D[i];
  
  D_not/=(RandParent-1); //this is the average of the perpendicular distances from all other parents (minus the index parent) to the index vector
  
  // Next few steps compute the child, by starting with a random vector
  for(j=0;j<MAXV;j++)
    {
      tempar1[j]=noise(0.0,(D_not*sigma_eta));
      tempar2[j]=tempar1[j];
    }
  
  for(j=0;j<MAXV;j++)
    { 
      tempar2[j] = tempar1[j]-((innerprod(tempar1,d)*d[j])/pow(dist,2.0));
    }
  
  for(j=0;j<MAXV;j++)
    tempar1[j]=tempar2[j];

  // modify to simd version
  __m256d tempar1_pd[5];
  for (i = 0; i < 5; i++) {
    tempar1_pd[i] = _mm256_load_pd(tempar1 + 4*i);
	newpop[pass].vari[i] = _mm256_add_pd(oldpop[arr1[0]].vari[i], tempar1_pd[i]);
  }
  /*
  for(k=0;k<MAXV;k++)
    newpop[pass].vari[k]=oldpop[arr1[0]].vari[k]+tempar1[k];
  */
  tempvar=noise(0.0,(sigma_zeta));
 
  // modify to simd version
  __m256d tempvar_pd = _mm256_set_pd(tempvar, tempvar, tempvar, tempvar);
  for (i = 0; i < 5; i++) {
    d_v[i] = _mm256_mul_pd(d_v[i], tempvar_pd);
	newpop[pass].vari[i] = _mm256_add_pd(d_v[i], newpop[pass].vari[i]);
   // newpop[pass].vari[i] = _mm256_fmadd_pd(d_v[i], tempvar_pd, newpop[pass].vari[i]);
  }
/*  
  for(k=0;k<MAXV;k++)
      newpop[pass].vari[k] += (tempvar*d[k]);
*/

  // the child is included in the newpop and is evaluated
  newpop[pass].obj = objective(newpop[pass].vari);

  return (1);
} 

// calculates the inner product of two vectors
double innerprod(double ind1[],double ind2[])
{
//  time_innerprod++;
//  unsigned long long start = rdtsc();
  int i;
  double sum;
  
  sum=0.0;
  
  for(i=0;i<MAXV;i++)
    sum+=(ind1[i]*ind2[i]);
  
//  count_innerprod += rdtsc() - start;
  return sum;
}  
