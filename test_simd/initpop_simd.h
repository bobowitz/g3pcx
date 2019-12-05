//This routine initializes the population (choose the variable bounds according to the need)

void initpop();

void initpop()
{
  double x[4],y[4], objbest, cycles;
  int i,j;
  unsigned long long start, end;
  __m256d fits;
  
  randomize();  // starts the random number generator
  /* unnecessary code
  for(i=0;i<MAXP;i++)
    oldpop[i].obj = 0.0;
  */
  
  for(i=0;i<MAXP_GROUPS;i++)
    for(j=0;j<MAXV;j++)
      {
	x[0]=randomperc();    // x is a uniform random number in (0,1)
	y[0]=(-10.0)+(5.0*x[0]); // the formula used is y=a+(b-a)*x if y should be a random number in (a,b)
	x[1]=randomperc();
	y[1]=(-10.0)+(5.0*x[1]);
	x[2]=randomperc();
	y[2]=(-10.0)+(5.0*x[2]);
	x[3]=randomperc();
	y[3]=(-10.0)+(5.0*x[3]);
	// Because of indexing and endianness, we have to use setr instead of
	// set.
	oldpop[i].vari[j] = _mm256_loadu_pd(y);
      }

  // solutions are evaluated and best id is computed
  start = rdtsc();
  for (i = 0; i < 200; i++) {
    fits = objective(oldpop[0].vari);
  }
  end = rdtsc();
  //printf("objectives: %f %f %f %f\n", fits[0], fits[1], fits[2], fits[3]);
  cycles = (end - start) * 3.4 / 2.4 / 200.0;
  printf("Objective takes an average of %f cycles.\n", cycles);

  for (i = 0; i < MAXP_GROUPS; i++) {
    oldpop[i].obj = objective(oldpop[i].vari);
  }

  objbest = oldpop[0].obj[0];
  best = 0;
  for (i = 1; i < 4; i++) {
    if (MINIMIZE * objbest > MINIMIZE * oldpop[0].obj[i]) {
      objbest = oldpop[i].obj[i];
      best = i;
    }
  }
  for(i=1;i<MAXP_GROUPS;i++)
    {
      for (j = 0; j < 4; j++) {
	if (MINIMIZE * objbest > MINIMIZE * oldpop[i].obj[j])
	  {
	    objbest = oldpop[i].obj[j];
	    best = (i * 4) + j;
	  }
      }
    }
}

