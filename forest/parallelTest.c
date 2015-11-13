//
// Torbert, 27 October 2014
//
// MPI Demo
//    mpicc mpiDemo.c
//    mpirun -np 4 a.out
//
// Manager-Worker model for parallel processing.
//
// time ... real ... user
//
// htop
//
#include <stdio.h>
//
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
//
#include "mpi.h"
//
double gettime()
{
	double t ;
	//
	struct timeval* ptr = (struct timeval*)malloc( sizeof(struct timeval) ) ;
	//
	gettimeofday( ptr , NULL ) ; // second argument is time zone... NULL
	//
	t = ptr->tv_sec * 1000000.0 + ptr->tv_usec ;
	//
	free( ptr ) ;
	//
	return t / 1000000.0 ;
}

double myrand()
{
    return ( rand() % 100 ) / 100.0 ;
}

typedef struct Node
{
    int row;
    int col;
    struct Node* next;
} ListNode ;

void freeList(ListNode* head)
{
    ListNode* tmp = NULL;

    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}


int main( int argc , char* argv[] )
{
    //
    // MPI variables
    //
    int        rank   ;
    int        size   ;
    MPI_Status status ;
    int        tag = 0;
    //
    // other variables
    //
    int        k , j  ;
    double     result ;
    double     stop = -1;
    int worker;
    //
    double started = gettime() ;
    int index;
    FILE *fout = fopen("parallelData.txt", "w");
    double prb = 0.01;
    double increment = 0.01;
    if(argv[1] != NULL) {
        prb = atof(argv[1]);
        increment = atof(argv[1]);
    }
    //
    //
    // boilerplate
    //
    MPI_Init(      &argc          , &argv ) ;
    MPI_Comm_size( MPI_COMM_WORLD , &size ) ; // same
    MPI_Comm_rank( MPI_COMM_WORLD , &rank ) ; // different
    //
    // manager has rank = 0
    //
    if( rank == 0 )
    {
        double workerPrb[size];

        for(int i=1; i < size; i++) {
            MPI_Send( &prb, 1, MPI_DOUBLE, i, tag, MPI_COMM_WORLD);
            workerPrb[i] = prb;
            prb += increment;
        }
        while(prb < 1) {
            MPI_Recv( &result, 1, MPI_DOUBLE, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);

            worker = status.MPI_SOURCE;
            printf("%d",worker);

            MPI_Send( &prb, 1, MPI_DOUBLE, index, tag, MPI_COMM_WORLD);


            fprintf(fout, "%f %f\n", workerPrb[worker], result);
            printf("%f %f\n", workerPrb[worker], result);

            workerPrb[worker] = prb;
            prb += increment;
        }
        // for(int i=1; i < size; i++) {
        //     MPI_Recv( &result, 1, MPI_DOUBLE, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
        //     index = status.MPI_SOURCE;
        //     fprintf(fout, "%f %f\n", workerPrb[index], result);
        //     MPI_Send( &stop, 1, MPI_DOUBLE, index, tag, MPI_COMM_WORLD);
        // }
    }
    //
    // workers have rank > 0
    //
    else
    {
        srand( rank );
        int n = 30;
        int t = 1000;

        MPI_Recv( &prb , 1 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD , &status ) ;
        //
        if (prb < 0) {
            result = -1;
            MPI_Send( &result , 1 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD ) ;
        }

        result = prb*10;
        //
        MPI_Send( &result , 1 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD ) ;
    }
    //
    // boilerplate
    //
    MPI_Finalize() ;
    //
    double stopped = gettime() ;
    printf("Time: %0.16f seconds\n" , stopped - started ) ;
    return 0;
}
//
// end of file
//
