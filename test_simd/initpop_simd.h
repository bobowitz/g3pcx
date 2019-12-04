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
  
  for(i=0;i<MAXP;i++)
    for(j=0;j<5;j++)
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
	oldpop[i].vari[j] = _mm256_setr_pd(y[0], y[1], y[2], y[3]);
      }

  // solutions are evaluated and best id is computed
  start = rdtsc();
  for (i = 0; i < 50; i++) {
    fits = objective(oldpop[0].vari, oldpop[1].vari, oldpop[2].vari,
		     oldpop[3].vari);
  }
  end = rdtsc();
  //printf("objectives: %f %f %f %f\n", fits[0], fits[1], fits[2], fits[3]);
  cycles = (end - start) * 3.4 / 2.4 / 50.0;
  printf("Objective takes an average of %f cycles.\n", cycles);

  for (i = 0; i < MAXP; i+=4) {
    fits = objective(oldpop[i].vari, oldpop[i+1].vari, oldpop[i+2].vari,
		     oldpop[i+3].vari);
    oldpop[i].obj = fits[0];
    oldpop[i+1].obj = fits[1];
    oldpop[i+2].obj = fits[2];
    oldpop[i+3].obj = fits[3];
  }

  objbest = oldpop[0].obj;
  best = 0;
  for(i=1;i<MAXP;i++)
    {
      if (MINIMIZE * objbest > MINIMIZE * oldpop[i].obj)
	{
	  objbest = oldpop[i].obj;
	  best = i;
	}
    }
}

