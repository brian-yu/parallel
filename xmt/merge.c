//
// gcc -fopenmp summation.c
//
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
//
//

void printArr(int arr[], int size, char name[]) {
    printf("\n%s\n", name);
    for (int i=0; i < size; i++) printf("%2d ", arr[i]);
}

void mergeSort(int a1[], int a2[], int result[])
{
    int i;
    int rank;
    int elem;
    printArr(a1, 8, "Array 1");
    printArr(a2, 8, "Array 2");
    omp_set_num_threads( 8 );
    #pragma omp parallel private(i)
    {
        i = omp_get_thread_num();
        elem = a1[i];
        if (elem < a2[0]) {
            rank = 0;
        } else if(elem > a2[7]) {
            rank = 8;
        } else {
            int l = 0;
            int r = 7;
            while (l <= r) {
                int m = (l + r)/2;
                if (elem < a2[m]) {
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            }
            rank = l;
        }
        result[rank+i] = elem;
    }
    printArr(result, 16, "Pass 1");
    #pragma omp parallel private(i)
    {
        i = omp_get_thread_num();
        elem = a2[i];
        if (elem < a1[0]) {
            rank = 0;
        } else if(elem > a1[7]) {
            rank = 8;
        } else {
            int l = 0;
            int r = 7;
            while (l <= r) {
                int m = (l + r)/2;
                if (elem < a1[m]) {
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            }
            rank = l;
        }
        result[rank+i] = elem;
    }
    printArr(result, 16, "Pass 2");
    printf("\n");
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
            if (j%2 == 0) { //is l
                C[k][j] = B[k][j] + (j/2-1 >= 0 ? C[k-1][j/2-1] : 0);
            } else { //is r
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
    

    int r1[] = {1, 2, 3, 4, 5, 13, 15, 17};
    int r2[] = {6, 7, 8, 11, 12, 14, 16, 18};
    int r3[] = {1, 2, 4, 7, 12, 13, 15, 18};
    int r4[] = {3, 5, 6, 10, 14, 16, 17, 20};
    int result[16];
    int result2[16];
    mergeSort(r1, r2, result);
    
    mergeSort(r3, r4, result2);
}