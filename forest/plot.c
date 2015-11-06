#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

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

int main(int argc, const char* argv[])
{

    double started = gettime() ;
    FILE *fout = fopen("data.txt", "w");
	int rseed;
	rseed = time( NULL ) ;
	//rseed = 12121212;
	srand( rseed );


    float prb = 0.01;
    float increment = 0.01;
    if(argv[1] != NULL) {
        prb = atof(argv[1]);
        increment = atof(argv[1]);
    }

	//printf("%f\n", prb);

    fprintf(fout, "0 0\n");

	int n = 30;
    int t = 1000;


    float maxavg = 0;
    float maxprb = 0;

    while(prb < 1) {
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
        //printf("%d", prbtotal);

    }
    float avg = prbtotal/t;

    if(avg > maxavg){
        maxavg = avg;
        maxprb = prb;
    }

    fprintf(fout, "%f %f\n", prb, avg/n);
    //printf("%f %f\n", prb, avg/n);
    prb += increment;

    }
    fprintf(fout, "%d %d\n", 1, n/n);

    double stopped = gettime() ;
    printf("Time: %0.16f seconds\n" , stopped - started ) ;
    //printf("Max occurs at (%f, %f)\n", maxprb, maxavg/n);

	return 0;
}
