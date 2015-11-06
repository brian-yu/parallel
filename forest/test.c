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


    for(int count = 0; count < 100000; count++) {

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

    if(steps > 1)
        printf("%d steps, %d\n", steps, count);
    else
        printf("%d step\n", steps);


    }
	return 0;
}
