//
// gcc -fopenmp summation.c
//
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
//
void printArr(int arr[][8], char name[]) {
    printf( "%s:\n", name ) ;
    for ( int k = 0 ; k <= 3 ; k++ ) {
        for ( int j = 0 ; j < 8 ; j++ ) {
            printf( "%2d " , arr[k][j] ) ;
        }
        printf( "\n" ) ;
    }
}
void printTree(int arr[][8], char name[]) {
    printf( "%s:\n", name ) ;
    for ( int k = 0 ; k < 4 ; k++ ) {
        for (int l=0; l<(4-k-1); l++) {
            printf("   ");
        }
        for ( int j = 0 ; j < (8/pow(2,(4-k-1))) ; j++ ) {
            printf( "%2d " , arr[k][j] ) ;
            for (int l=0; l<(4-k-1); l++) {
                printf("  ");
            }
        }
        printf( "\n" ) ;
    }
}
int main()
{
    int k , j , nt ;
    int A[8] = {1, 0, 1, 0, 0, 1, 0, 1} ;
    int B[4][8] = { 0 } ;
    int C[4][8] = { 0 } ;
    int D[8] = {0};
    
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
    
    #pragma omp parallel private(j) 
    {
        j = omp_get_thread_num();
        if (A[j] == 1) {
            D[j] = j;
        } else {
            int i=j;
            while (B[3][i] != 1) {
                i--;
                D[j] = i;
            }
        }
    }
    
    printArr(B, "Sum");
    printArr(C, "Prefix Sum");
    
    printTree(B, "Sum");
    printTree(C, "Prefix Sum");
    
    printf("Array:\n");
    for (int i=0; i < 8; i++) printf("%2d ", A[i]);
    printf("\nNearest One:\n");
    for (int i=0; i < 8; i++) printf("%2d ", D[i]); 
    printf("\nCorrect:\n");
    printf(" 0  0  2  2  2  5  5  7\n");
}