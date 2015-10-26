#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>



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

int main(int argc, const char* argv[])
{

    FILE *fout = fopen("data1.txt", "a");
	int rseed;
	rseed = time( NULL ) ;
	//rseed = 12121212;
	//srand( rseed );
    srand(0);

	//float prb = 0.001;
    float prb = 0.0001;
    float increment = 0.001;
    if(argv[1] != NULL) {
        prb = atof(argv[1]);
        increment = atof(argv[1]);
    }

    //fprintf(fout, "0 0\n");

	int n = 30;
    int t = 1000;

    float maxavg = 0;
    float maxprb = 0;

    while(prb < .75) {
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

        ListNode* start = NULL;
        ListNode* prev = NULL;
        for(int i=0; i<n; i++) {
            if(forest[i][0] == 'X') {
                if(prev != NULL) {
                    ListNode* l = NULL;
                    l = (ListNode*)malloc( sizeof(ListNode));
                    l->row = i;
                    l->col = 0;
                    prev->next = l;
                    prev = l;
                    forest[i][0] = '*';
                    //free(l);
                } else {
                    prev = (ListNode*)malloc(sizeof(ListNode));
                    prev->row = i;
                    prev->col = 0;
                    prev->next = NULL;
                    forest[i][0] = '*';
                    start = prev;
                }
		    }
	    }

        while (start != NULL) {

            ListNode* current = start;
            start = NULL;
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
                        ListNode* temp = prev;
                        prev = l;
                        free(temp);
                    } else {
                        prev->next = l;
                        prev = l;
                    }

                    if(start == NULL) {
                        ListNode* temp = start;
                        start = l;
                        free(temp);
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
                        ListNode* temp = prev;
                        prev = l;
                        free(temp);
                    } else {
                        prev->next = l;
                        prev = l;
                    }

                    if(start == NULL) {
                        ListNode* temp = start;
                        start = l;
                        free(temp);
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
                        ListNode* temp = prev;
                        prev = l;
                        free(temp);
                    } else {
                        prev->next = l;
                        prev = l;
                    }

                    if(start == NULL) {
                        ListNode* temp = start;
                        start = l;
                        free(temp);
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
                        ListNode* temp = prev;
                        prev = l;
                        free(temp);
                    } else {
                        prev->next = l;
                        prev = l;
                    }

                    if(start == NULL) {
                        ListNode* temp = start;
                        start = l;
                        free(temp);
                    }

                }

                current = current->next;

            }

            steps++;

        }

        prbtotal += steps;

        }
        float avg = prbtotal/t;

        if(avg > maxavg){
            maxavg = avg;
            maxprb = prb;
        }

        fprintf(fout, "%f %f\n", prb, avg/n);
        printf("%f %f\n", prb, avg/n);
        prb += increment;

    }

    //fprintf(fout, "%d %d\n", 1, n/n);

    printf("Max occurs at (%f, %f)\n", maxprb, maxavg/n);

	return 0;
}
