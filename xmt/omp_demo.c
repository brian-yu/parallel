//
// OpenMP demo
//
// gcc -fopenmp omp_demo.c
//
#include <omp.h>
#include <stdio.h>
//
#define N 4
//
int main(int argc,char* argv[])
{
	int tid, nthreads, j, total;
	//
	int count[N];
	//
	//
	//
	omp_set_num_threads(N);
	//
	//
	//
	for(j=0;j<N;j++)
	{
		count[j]=0;
	}	
	//
	//
	//
	#pragma omp parallel for private(tid)
	//
	for(j=0;j<1000000000;j++)
	{
		tid=omp_get_thread_num();
		//
		count[tid]++;
	}
	//
	total=0;
	for(j=0;j<N;j++)
	{
		printf("*** %d %d\n",j,count[j]);
		total+=count[j];
	}
	printf("%d\n",total);
	//
	return 0;
}
//
// end of file
//
