//This routine is the implementation of PCX operator and associated functions
//Do not change anything here without understanding the paper

double modu(double index[]); //gives modulus of an input vector
double innerprod(double ind1[],double ind2[]); //gives innerproduct of 2 input vectors
int generate_new(int h); //main routine here

unsigned long long time_cent = 0;
unsigned long long count_cent = 0;

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
  __m256d vari[3][5];
  
  for (j = 0; j < 2; j++) {
    double *oldpop_arr1_j_vari = oldpop[arr1[j]].vari;
	for (i = 0; i < 5; i++) {
      vari[j][i] = _mm256_load_pd(oldpop_arr1_j_vari + 4 * i);
	}
  }
  
  centroid_pd[0] = _mm256_add_pd(vari[0][0], vari[1][0]);
  centroid_pd[1] = _mm256_add_pd(vari[0][1], vari[1][1]);
  centroid_pd[2] = _mm256_add_pd(vari[0][2], vari[1][2]);
  centroid_pd[3] = _mm256_add_pd(vari[0][3], vari[1][3]);
  centroid_pd[4] = _mm256_add_pd(vari[0][4], vari[1][4]);
 
  j = 2;
  double *oldpop_arr1_j_vari = oldpop[arr1[j]].vari;
  for (i = 0; i < 5; i++) {
    vari[2][i] = _mm256_load_pd(oldpop_arr1_j_vari + 4 * i);
  }
  
  centroid_pd[0] = _mm256_add_pd(vari[2][0], centroid_pd[0]);
  centroid_pd[1] = _mm256_add_pd(vari[2][1], centroid_pd[1]);
  centroid_pd[2] = _mm256_add_pd(vari[2][2], centroid_pd[2]);
  centroid_pd[3] = _mm256_add_pd(vari[2][3], centroid_pd[3]);
  centroid_pd[4] = _mm256_add_pd(vari[2][4], centroid_pd[4]);
  
  __m256d c = _mm256_set_pd(3.0, 3.0, 3.0, 3.0);

  centroid_pd[0] = _mm256_div_pd(centroid_pd[0], c);
  centroid_pd[1] = _mm256_div_pd(centroid_pd[1], c);
  centroid_pd[2] = _mm256_div_pd(centroid_pd[2], c);
  centroid_pd[3] = _mm256_div_pd(centroid_pd[3], c);
  centroid_pd[4] = _mm256_div_pd(centroid_pd[4], c);
  
  _mm256_store_pd(Centroid, centroid_pd[0]);
  _mm256_store_pd(Centroid + 4, centroid_pd[1]);
  _mm256_store_pd(Centroid + 8, centroid_pd[2]);
  _mm256_store_pd(Centroid + 12, centroid_pd[3]);
  _mm256_store_pd(Centroid + 16, centroid_pd[4]);
  // calculate the distace (d) from centroid to the index parent arr1[0]  
  // also distance (diff) between index and other parents are computed
  __m256d d_v[5];
  __m256d diff_v[RandParent][5];
  for (i = 0; i < 5; i++) {
    d_v[i] = _mm256_sub_pd(centroid_pd[i], vari[0][i]);
  }
  _mm256_store_pd(d, d_v[0]);
  _mm256_store_pd(d + 4, d_v[1]);
  _mm256_store_pd(d + 8, d_v[2]);
  _mm256_store_pd(d + 12, d_v[3]);
  _mm256_store_pd(d + 16, d_v[4]);
  for(j = 1; j < RandParent; j++) {
    for(i = 0; i < 5; i++) { 
	  diff_v[j][i] = _mm256_sub_pd(vari[j][i], vari[0][i]);
	  _mm256_store_pd(diff[j] + 4 * i, diff_v[j][i]);
	}
    if (modu(diff[j]) < EPSILON) {	
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

  dist=modu(d); // modu calculates the magnitude of the vector
  
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
      temp2=temp1/(modu(diff[i])*dist);
      temp3=1.0-pow(temp2,2.0);
      D[i]=modu(diff[i])*sqrt(temp3);
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

  return (1);
} 

// calculates the magnitude of a vector
double modu(double index[])
{
  int i;
  double sum,modul;
  
  sum=0.0;
  for(i=0;i<MAXV;i++)
    sum+=(index[i]*index[i]);
  
  modul=sqrt(sum);
  return modul;
}   

// calculates the inner product of two vectors
double innerprod(double ind1[],double ind2[])
{
  int i;
  double sum;
  
  sum=0.0;
  
  for(i=0;i<MAXV;i++)
    sum+=(ind1[i]*ind2[i]);
  
  return sum;
}  




