//This routine is the implementation of PCX operator and associated functions
//Do not change anything here without understanding the paper

#include "modu.h"
#include "innerprod.h"

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
  double tempvar,tempsum,D_not,dist;
  double D[RandParent];
  double temp1,temp2,temp3; 
  int temp;

  int arr1_0 = arr1[0];
  int arr1_j;
  #ifdef centroid_simd
  time_cent++;
  unsigned long long start = rdtsc();

  __m256d centroid_v[5];
  __m256d *vari[3];

  vari[0] = oldpop[arr1[0]].vari;
  vari[1] = oldpop[arr1[1]].vari;
  vari[2] = oldpop[arr1[2]].vari;

  // Sum each variable of oldpop[arr[0-2]] and take average
  for (i = 0; i < 5; i++) {
    centroid_v[i] = _mm256_add_pd(vari[0][i], vari[1][i]);
  }
  for (i = 0; i < 5; i++) {
    centroid_v[i] = _mm256_add_pd(vari[2][i], centroid_v[i]);
  }
  __m256d c = _mm256_set_pd(3.0, 3.0, 3.0, 3.0);
  for (i = 0; i < 5; i++) {
    centroid_v[i] = _mm256_div_pd(centroid_v[i], c);
  }

  // calculate the distace (d) from centroid to the index parent arr1[0]  
  // also distance (diff) between index and other parents are computed
  __m256d d_v[5];
  __m256d diff_v[RandParent][5];
  for (i = 0; i < 5; i++) {
    d_v[i] = _mm256_sub_pd(centroid_v[i], vari[0][i]);
  }
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
  double Centroid[MAXV];
  double d[MAXV];
  double diff[RandParent][MAXV];
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

  #ifdef centroid_simd
  // orthogonal directions are computed (see the paper)
  for(i=1;i<RandParent;i++) {
    temp1 = innerprod_simd(diff_v[i], d_v);
    temp2=temp1/(modu_simd(diff_v[i])*dist);
    temp3=1.0-pow(temp2,2.0);
    D[i]=modu_simd(diff_v[i])*sqrt(temp3);
  }
  D_not = (D[1] + D[2]) / 2;

  // Next few steps compute the child, by starting with a random vector
  __m256d tempar1_v[5];
  for(j = 0; j < 5; j++) {
    tempar1_v[j] = _mm256_set_pd(noise(0.0, (D_not*sigma_eta)), noise(0.0, (D_not*sigma_eta)),
								  noise(0.0, (D_not*sigma_eta)), noise(0.0, (D_not*sigma_eta)));
  }
  double innerprod_val = innerprod_simd(tempar1_v, d_v);
  for (j = 0; j < 5; j++) {
	tempar1_v[j] = _mm256_sub_pd(tempar1_v[j], ((innerprod_val*d_v[j])/pow(dist, 2.0)));
  }
  
  for (i = 0; i < 5; i++) {
	newpop[pass].vari[i] = _mm256_add_pd(oldpop[arr1_0].vari[i], tempar1_v[i]);
  }
  

  tempvar=noise(0.0,(sigma_zeta));
 
  __m256d tempvar_v = _mm256_setr_pd(tempvar, tempvar, tempvar, tempvar);
  for (i = 0; i < 5; i++) {
    d_v[i] = _mm256_mul_pd(d_v[i], tempvar_v);
	newpop[pass].vari[i] = _mm256_add_pd(d_v[i], newpop[pass].vari[i]);
//    newpop[pass].vari[i] = _mm256_fmadd_pd(d_v[i], tempvar_v, newpop[pass].vari[i]);
  }

  // the child is included in the newpop and is evaluated
  newpop[pass].obj = objective(newpop[pass].vari);

  #else
  double tempar1[MAXV];
  double tempar2[MAXV];
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

  for(k=0;k<MAXV;k++)
    newpop[pass].vari[k]=oldpop[arr1[0]].vari[k]+tempar1[k];

  tempvar=noise(0.0,(sigma_zeta));
 
  for(k=0;k<MAXV;k++)
      newpop[pass].vari[k] += (tempvar*d[k]);

  // the child is included in the newpop and is evaluated
  newpop[pass].obj = objective(newpop[pass].vari);

  #endif

  return (1);
} 
