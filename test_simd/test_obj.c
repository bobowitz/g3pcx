/********************************************************************************************
 ***                      Parent Centric Recombination using G3 Model                     ***
 ***                                                                                      ***
 ***                      Developed by Prof. K. Deb with his students                     ***
 ***                                                                                      ***
 *** Last Edited : 06.05.2002 
     Last Edited : 10.07.2004 (nan problem is fixed)
 ***
 *** .....................................................................................***

This is an implementation of PCX operator using G3 model. This is an unconstrained optimization algorithm which is suitable for real parameter optimization. This algorithm is based on the paper "A Computationally Efficient Evolutionary Algorithm for Real-Parameter
   Optimization"  which can be downloaded from http://www.iitk.ac.in/kangal/pub.htm. For details of the algorithm please refer to the paper. 

A brief help on usage of the code is as follows.

Code your objective function to be optimized in "objective.h"
"random.h" is the random number generator.
Population is initialized in "initpop.h". Please change the initialization bounds according to the need. 
"generate_new.h" contains the main routine of PCX and certain allied functions.
"popvar.h" is used to calculate population mean and variances (only for study purposes).
"sort.h" sorts a subpopulation by fitness
"replace.h" contains routines to replace few parents by some good individuals.

Input parameters have to be defined as below. It is advised that some of them not be changed (from what we have set them) for optimum performance of this algorithm. However others will have to be set according to individual requirement.

Output shall be recorded in two files "1.out" which contains function evaluations versus best fitness (in the population) and "2.out" which contains details of the best solution obtained in each run. 

Further description of functions and routines shall accompany them. 

Please use this program for any purpose freely but make sure to refer to Prof K. Deb as the creater of PCX.*/ 

/********************************************************************************************/
/********************************************************************************************/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>
#include "fast_code_utils.h"

//------------------------------------------------------------------------------------------- 

//Please try to keep the following parameters fixed at these values
#define EPSILON 1e-40

#define MAXFUN 1000000  //upper bound for number of function evaluations
                        // in case best fitness does'nt reach the desired value
#define MAXP 100        //population size (best if chosen between 100-150)
#define KIDS 2          //pool size of kids to be formed (use 2,3 or 4)
#define M 1             //M+2 is the number of parents participating in xover (use 1)
#define family 2        //number of parents to be replaced by good individuals(use 1 or 2)
#define sigma_zeta 0.1
#define sigma_eta 0.1   //variances used in PCX (best if fixed at these values)

//--------------------------------------------------------------------------//
//Change the following parameters according to the needs of the problem

#define MAXV 20         //number of variables of the problem
#define MAXRUN 10       //number of runs each with different random initial population
#define LIMIT 1e-20     //accuracy of best solution fitness desired
#define MINIMIZE 1      //set 1 to minimize and -1 to maximize
#define RandParent M+2     //number of parents participating in PCX 


#define ellip // choose the function: ellip, schwefel, rosen

/*functions declaration*/
void arrnd();

/*global variables declaration*/
struct pop{
  double vari[MAXV];
  double obj;
} oldpop[MAXP],newpop[KIDS+2];


int count; 
int arr1[MAXP];
double seed,basic_seed;
int list[KIDS+2];
int mom[MAXP];
int RUN;
int gen,kids;
double d_not[MAXP];
double mean_d,var_d;
double dis_opt;
int best;

#include "objective.h"    //objective function
#include "random.h"       //random number generator
#include "initpop.h"      //population initialized
#include "generate_new.h" //generates a child from participating parents:PCX 
#include "popvar.h"       //population variance (used only for experiments)
#include "sort.h"         //subpopulation sorted by fitness 
#include "replace.h"      //good kids replace few parents

main()
{
  int i,j,h;
  double u,v,w;
  double tempfit;
  double exec_time, avg_time = 0.0;
  FILE *fpt1,*fpt2;
  int tag;
  unsigned long long start_t, end_t, cycles, avg_cycles = 0;
  
  basic_seed=0.4122;   //arbitrary choice
  kids = KIDS;
  
  gen = MAXFUN/kids;   //so that max number of function evaluations is fixed at 1 million set above


  for(RUN=1;RUN<=MAXRUN;RUN++)
    { 
      seed=basic_seed+(1.0-basic_seed)*(double)(RUN-1)/(double)MAXRUN;
      if(seed>1.0) printf("\n warning!!! seed number exceeds 1.0");
      start_t = rdtsc();
      initpop();   //population initialized
      end_t = rdtsc();

      cycles = end_t - start_t;
      avg_cycles += cycles;
      exec_time = cycles * 3.4 / 2400000000;
      avg_time += exec_time;
      //printf("Population initialized in %u cycles or %f seconds.\n", cycles, exec_time);
    }
  avg_cycles = avg_cycles / 10;
  avg_time = avg_time / 10.0;
  printf("Average cycles: %u\nAverage time: %f seconds.\n", avg_cycles, avg_time);
}

//random array of parents generator
void arrnd()
{
  int i,j,index;
  int swp;
  double u;
  int delta;
  
  for(i=0;i<MAXP;i++)
    arr1[i]=i;
  
  swp=arr1[0];
  arr1[0]=arr1[best];  // best is always included as a parent and is the index parent
                       // this can be changed for solving a generic problem
  arr1[best]=swp;
  
  for(i=1;i<RandParent;i++)  // shuffle the other parents
    {
    u=randomperc();
    index=(u*(MAXP-i))+i;
    
    if(index>(MAXP-1)) index=MAXP-1;
    swp=arr1[index];
    arr1[index]=arr1[i];
    arr1[i]=swp;
    }
}


















