#include <stdio.h>
#include "omp.h"

#define NUM_THREADS 2 
int main(int argc, char const *argv[])
{
	omp_set_num_threads(NUM_THREADS);
	int nthreads;
	static long num_steps = 100000;
	double step;
	int i; 
	double pi = 0.0;


	step = 1.0/(double) num_steps;

	#pragma omp parallel
	{
		double sum;
		int nthrds;
		double x = 0;
		int ID = omp_get_thread_num();
		nthrds = omp_get_num_threads();
		if (ID == 0) nthreads = nthrds;

		for (i=ID, sum = 0.0; i < num_steps; i = i + nthrds)
		{
			x = (i+0.5)*step;
			sum += 4.0/(1.0+x*x);
		}

		#pragma omp critical
			pi += sum * step;
	}



	printf("Fläche ist %lf.\n", pi);
	return 0;
}