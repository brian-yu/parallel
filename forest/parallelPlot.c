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
//
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
    double kjob[size];
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
    // boilerplate
    //
    MPI_Init(      &argc          , &argv ) ;
    MPI_Comm_size( MPI_COMM_WORLD , &size ) ; // same
    MPI_Comm_rank( MPI_COMM_WORLD , &rank ) ; // different
    //
    // manager has rank = 0
    srand(rank);
    //
    if( rank == 0 )
    {
        //
        int k, j;
        double kjob[size];
        double maximum = 0.0;
        double maximumPrb = 0.0;

	fprintf(fout, "%f %f\n", 0.0, 0.0);
        for( int k = 1 ; k < size ; k++ )
        {
            kjob[k] = prb;
            MPI_Send( &prb , 1 , MPI_DOUBLE , k , tag , MPI_COMM_WORLD ) ;
            prb += increment;
        }
        //
        while (prb < 1)
        {
            MPI_Recv( &result , 1 , MPI_DOUBLE , MPI_ANY_SOURCE , tag , MPI_COMM_WORLD , &status ) ;
            //
            k = status.MPI_SOURCE ;
            if(result > maximum) {
                maximum = result;
                maximumPrb = kjob[k];
            }
            fprintf(fout, "%f %f\n", kjob[k], result);
	    printf("%f %f\n", kjob[k], result);
            //
            kjob[k] = prb;
            MPI_Send(&prb, 1, MPI_DOUBLE, k, tag, MPI_COMM_WORLD);
            prb += increment;
        }
        //
        for (int j=1; j <size; j++) {
            MPI_Recv(&result, 1, MPI_DOUBLE, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
            k = status.MPI_SOURCE;
            
            fprintf(fout, "%f %f\n", kjob[k], result);
	        printf("%f %f\n", kjob[k], result);	  
            prb = -1.0;
            MPI_Send(&prb, 1, MPI_DOUBLE, k, tag, MPI_COMM_WORLD);
        }
	fprintf(fout, "%f %f\n", 1.0, 1.0);
		
        printf("Maximum occurs at (%f, %f)\n", maximumPrb, maximum);
	printf("Total time: %fs\n", gettime()-started);
    }
    //
    // workers have rank > 0
    //
    else
    {
	   
        while(1) 
        {
            MPI_Recv(&prb, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &status);
            if(prb<0)
                break;
            //
            // . . .
            //
            int n = 30;
            int t = 1000;

            //printf("%f", prb);
            int prbtotal = 0;
            for (int m = 0; m < t; m++) {

                char forest[n][n];
                for(int i = 0; i < n; i++) {
                    for(int j = 0; j < n; j++) {
                        float x = myrand();
                        if(x < prb) {
                            forest[i][j] = 'X';
                        } else {
                            forest[i][j] = '-';
                        }
                    }
                }



                int steps = 0;

                ListNode* head = NULL;
                ListNode* current = NULL;
                for(int i=0; i<n; i++) {
                    if(forest[i][0] == 'X') {
                        if(head != NULL) {
                            current->next = (ListNode*)malloc( sizeof(ListNode));
                            current->next->row = i;
                            current->next->col = 0;
                            current->next->next = NULL;
                            forest[i][0] = '*';
                            current = current->next;
                        } else {
                            head = (ListNode*)malloc(sizeof(ListNode));
                            head->row = i;  
                            head->col = 0;
                            head->next = NULL;
                            forest[i][0] = '*';
                            current = head;
                        }
                    }
                }
                //steps++;



                while (head != NULL) {

                    ListNode* current = head;
                    ListNode* newhead = NULL;
                    ListNode* prev = NULL;

                    while (current!=NULL) {
                        int r = current->row;
                        int c = current->col;
                        forest[r][c] = '-';


                        if(forest[r+1][c] == 'X' && r+1 < n) {
                            forest[r+1][c] = '*';

                            ListNode* l = NULL;
                            l = (ListNode*)malloc(sizeof(ListNode));
                            l->row = r+1;
                            l->col = c;
                            l->next = NULL;

                            if(prev == NULL) {
                                prev = l;
                            } else {
                                prev->next = l;
                                prev = l;
                            }

                            if(newhead == NULL) {
                                newhead = l;
                            }

                        }
                        if(forest[r-1][c] == 'X' && r-1 >= 0) {
                            forest[r-1][c] = '*';

                            ListNode* l = NULL;
                            l = (ListNode*)malloc(sizeof(ListNode));
                            l->row = r-1;
                            l->col = c;
                            l->next = NULL;

                            if(prev == NULL) {
                                prev = l;
                            } else {
                                prev->next = l;
                                prev = l;
                            }

                            if(newhead == NULL) {
                                newhead = l;
                            }

                        }
                        if(forest[r][c+1] == 'X' && c+1 < n) {
                            forest[r][c+1] = '*';

                            ListNode* l = NULL;
                            l = (ListNode*)malloc(sizeof(ListNode));
                            l->row = r;
                            l->col = c+1;
                            l->next = NULL;

                            if(prev == NULL) {
                                prev = l;
                            } else {
                                prev->next = l;
                                prev = l;
                            }

                            if(newhead == NULL) {
                                newhead = l;
                            }

                        }
                        if(forest[r][c-1] == 'X' && c-1 >= 0) {
                            forest[r][c-1] = '*';

                            ListNode* l = NULL;
                            l = (ListNode*)malloc(sizeof(ListNode));
                            l->row = r;
                            l->col = c-1;
                            l->next = NULL;

                            if(prev == NULL) {
                                prev = l;
                            } else {
                                prev->next = l;
                                prev = l;
                            }

                            if(newhead == NULL) {
                                newhead = l;
                            }

                        }

                        current = current->next;
                    }

                    freeList(head);

                    head = newhead;



                    steps++;

                }
                prbtotal += steps;

            }
            double avg = prbtotal/t;
            double normalized = avg/n;
            result = normalized;
		   
		   
            MPI_Send(&result, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
        }
      
    }
    //
    // boilerplate
    //
    MPI_Finalize() ;
    //
    return 0;
}
// 
// end of file
// 
