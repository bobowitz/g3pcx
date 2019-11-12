//This routine initializes the population (choose the variable bounds according to the need)

void initpop();

void initpop()
{
  double x[4],y[4], objbest;
  int i,j;
  
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
	oldpop[i].vari[j] = _mm256_setr_pd(x[0], x[1], x[2], x[3]);
      }

  // solutions are evaluated and best id is computed
  oldpop[0].obj=objective(oldpop[0].vari);
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
