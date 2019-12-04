//This routine initializes the population (choose the variable bounds according to the need)

void initpop();

void initpop()
{
  double x,y, objbest, cycles;
  int i,j;
  unsigned long long start, end;
  
  randomize();  // starts the random number generator
  
  for(i=0;i<MAXP;i++)
    oldpop[i].obj = 0.0;
  
  for(i=0;i<MAXP;i++)
    for(j=0;j<MAXV;j++)
      {
	x=randomperc();    // x is a uniform random number in (0,1)
	y=(-10.0)+(5.0*x); // the formula used is y=a+(b-a)*x if y should be a random number in (a,b)
	oldpop[i].vari[j] = y;
      }

  // solutions are evaluated and best id is computed
  start = rdtsc();
  for (i = 0; i < 50; i++) {
    oldpop[0].obj=objective(oldpop[0].vari);
    oldpop[1].obj=objective(oldpop[1].vari);
    oldpop[2].obj=objective(oldpop[2].vari);
    oldpop[3].obj=objective(oldpop[3].vari);
  }
  end = rdtsc();
  cycles = (end - start) * 3.4 / 2.4 / 200.0;
  //printf("objective: %f\n", oldpop[0].obj);
  printf("objective takes average of %f cycles.\n", cycles);

  objbest = oldpop[0].obj;
  best = 0;
  for(i=1;i<MAXP;i++)
    {
      oldpop[i].obj=objective(oldpop[i].vari);
      if (MINIMIZE * objbest > MINIMIZE * oldpop[i].obj)
	{
	  objbest = oldpop[i].obj;
	  best = i;
	}
    }
}

