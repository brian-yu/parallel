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
    //
    srand(time(NULL));
    int A[8] = {1, 1, 2, 3, 5, 2, 1, 2} ;
    //int A[8] = {rand()%20, rand()%20, rand()%20, rand()%20, rand()%20, rand()%20, rand()%20, rand()%20} ;
    int B[4][8] = { 0 } ;
    int C[4][8] = { 0 } ;
    //
    
    
    omp_set_num_threads( 8 ) ;
    #pragma omp parallel private(j)
    {
        j = omp_get_thread_num() ;
        //
        B[3][j] = A[j] ;
    }
    //
    nt = 4 ;
    //
    for( k = 2 ; k >= 0 ; k-- )
    {
        omp_set_num_threads( nt ) ;
        //
        #pragma omp parallel private(j)
        {
            j = omp_get_thread_num() ;
            //
            B[k][j] = B[k+1][2*j] + B[k+1][2*j+1] ;
        }
        //
        nt /= 2 ;
    }
    
    int current;
    nt = 1;
    C[0][0] = B[0][0];
    for (k=0; k < 3; k++) {
        omp_set_num_threads( nt ) ;
        #pragma omp parallel private(j) 
        {
            j = omp_get_thread_num();
            current = C[k][j];
            //leftchild -- fix this
            /*
            [3][6] -> [2][2]
            [3][4] -> [2][1]
            [2][2] -> [1][0]
            */
            C[k+1][2*j] = B[k+1][2*j] + (j-1 > 0 ? C[k][j-1] : 0);
            //rightchild
            C[k+1][2*j+1] = current;
        }
        nt *= 2;
    }
    
    
    
    
    //
    for ( k = 0 ; k <= 3 ; k++ ) {
        for ( j = 0 ; j < 8 ; j++ ) {
            printf( "%2d " , B[k][j] ) ;
        }
        printf( "\n" ) ;
    }
    printf( "\n" ) ;
    for ( k = 0 ; k <= 3 ; k++ ) {
        for ( j = 0 ; j < 8 ; j++ ) {
            printf( "%2d " , C[k][j] ) ;
        }
        printf( "\n" ) ;
    }
}
//
// end of file
//
