#include "bench_functions.h"

/* Loop test functions*/

/*a very simple function to start with.*/
void loop_func(void *arg, int start, int stop)
{
	int * test_pt=(int *)arg;
	int i,test = *test_pt;
	for(i=start;i<=stop;i++)
	{
		test+=i;
		printf("i:%d test(test+i):%d\n",i,test);
		test-=i;
	}
	*test_pt=40;
}

/*a given test function which implements an array*/
void ploop_func(void *arg, int low, int high)
{
	double *A = (double *) arg;
	int loop_counter;

	for(loop_counter=low;loop_counter<=high;loop_counter++)
	{
		A[loop_counter]=loop_counter+10;
		comp(20);
	}
}

/*function implements a vector addition*/
void vector_loop_func(void * arg, int low, int high)
{
	vectors * v = (vectors*) arg;
	
	int loop_counter;

	for(loop_counter=low;loop_counter<=high;loop_counter++)
	{
		v->C[loop_counter]=v->A[loop_counter]+v->B[loop_counter];
		comp(20);
	}

}

/*initializes the vectors with random values in order to be used in addtion*/
void init_vectors(void * arg, int size, int range)
{
	srand ( (unsigned)time(NULL) );

	vectors * v = (vectors*) arg;
	int i;
	/*allocate memory for each vector*/
	v->A = malloc(size * sizeof(int *));
	v->B = malloc(size * sizeof(int *));
	v->C = malloc(size * sizeof(int *));
	/* give random values*/
	for(i=0;i<size;i++)
	{
		v->A[i]=rand()%range +1;
		v->B[i]=rand()%range +1;
		v->C[i]=0;
	}
}

/*returns the current time*/
double return_time(void)
{
	gettimeofday(&tm, NULL);
	double time=tm.tv_sec+(tm.tv_usec/1000000.0);
	
	return time;
}

/* The following functions are used to create some artificial workload for measure purpouses*/

/* Produces artificial load of 1 millisecond*/
void one_milli(void)
{
	int i;
	double res = 4.0;
	for(i=0;i<28000;i++)
	{
		res=pow(sqrt(res),2.0);
	}

}

/*produces artificial load of given milliseconds*/
void comp(int millis)
{
	int i;
	for(i=0;i<millis;i++)
	{
		one_milli();
	}
}
