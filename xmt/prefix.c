//
// gcc -fopenmp summation.c
//
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
//
int main()
{
    int k , j , nt ;
    srand(time(NULL));
    int A[8] = {1, 1, 2, 3, 5, 2, 1, 2} ;
    //int A[8] = {rand()%20, rand()%20, rand()%20, rand()%20, rand()%20, rand()%20, rand()%20, rand()%20} ;
    int B[4][8] = { 0 } ;
    int C[4][8] = { 0 } ;
    
    omp_set_num_threads( 8 ) ;
    #pragma omp parallel private(j)
    {
        j = omp_get_thread_num() ;
        B[3][j] = A[j] ;
    }
    nt = 4 ;
    for( k = 2 ; k >= 0 ; k-- )
    {
        omp_set_num_threads( nt ) ;
        #pragma omp parallel private(j)
        {
            j = omp_get_thread_num() ;
            B[k][j] = B[k+1][2*j] + B[k+1][2*j+1] ;
        }
        nt /= 2 ;
    }

    nt = 2;
    C[0][0] = B[0][0];
    for (k=1; k < 4; k++) {
        omp_set_num_threads( nt ) ;
        #pragma omp parallel private(j) 
        {
            j = omp_get_thread_num();
            if (j%2 == 0) { //is Left
                C[k][j] = B[k][j] + (j/2-1 >= 0 ? C[k-1][j/2-1] : 0);
            } else { //is Right
                C[k][j] = C[k-1][(j-1)/2];
            }
        }
        nt *= 2;
    }
    
    for ( k = 0 ; k <= 3 ; k++ ) {
        for ( j = 0 ; j < 8 ; j++ ) {
            printf( "%2d " , B[k][j] ) ;
        }
        printf( "\n" ) ;
    }
    printf( "Prefix Sum:\n" ) ;
    for ( k = 0 ; k <= 3 ; k++ ) {
        for ( j = 0 ; j < 8 ; j++ ) {
            printf( "%2d " , C[k][j] ) ;
        }
        printf( "\n" ) ;
    }
}