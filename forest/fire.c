#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


double myrand()
{
   return ( rand() % 100 ) / 100.0 ;
}

void printArr(int row, int col, char arr[][col]) {

	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			printf("%c ", arr[i][j]);
		}
		printf("%d\n",i);
	}

}

typedef struct Node
{
	int row;
	int col;
	struct Node* next;

} ListNode ;

int main(int argc, const char* argv[])
{
	int rseed;
	rseed = time( NULL ) ;
	rseed = 12121212;
	srand( rseed );
	system( "clear" );

	float prb;
	if(argc > 1) {
		prb = atof(argv[1]);
	} else {
		printf("No probability inputted!\n");
		exit(0);
	}
	printf("%f\n", prb);

	int n = 30;

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

	system("clear");
	printArr(n, n, forest);
	sleep(1);


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
	//steps++;
	system("clear");
	printArr(n, n, forest);
    printf("Fire started.\n");
	sleep(1);



    while (start != NULL) {

        ListNode* current = start;
        ListNode* newstart = NULL;
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

                if(newstart == NULL) {
                    newstart = l;
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

                if(newstart == NULL) {
                    newstart = l;
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

                if(newstart == NULL) {
                    newstart = l;
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

                if(newstart == NULL) {
                    newstart = l;
                }

            }

            current = current->next;
        }

        start = newstart;

        steps++;
        system("clear");
        printArr(n, n, forest);
        if(steps > 1)
            printf("%d steps\n", steps);
        else
            printf("%d step\n", steps);
        sleep(1);
    }
	return 0;
}
