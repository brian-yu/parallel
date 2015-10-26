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

	int firec = 0;
	ListNode* fire[n*n+n];
	int steps = 0;
	int index = 0;
	for(int i=0; i<n; i++) {
		if(forest[i][0] == 'X') {
		ListNode* l = NULL;
		l = (ListNode*)malloc( sizeof(ListNode));
		l->row = i;
		l->col = 0;
		fire[i] = l;
		forest[i][0] = '*';
		index++;
		firec++;
		}
	}
	steps++;
	system("clear");
	printArr(n, n, forest);
	sleep(1);

	ListNode* burnt[n*n+n];

	int burntc = 0;
	int size = n;
	while(firec > 0) {
		int count = 0;
		ListNode* newfire[n*n];
		int newfirec = 0;

		for(int i=0; i<firec; i++) {
			//printf("%d test\n", i);
			if(fire[i] != NULL && fire[i]->row >= 0 && fire[i]->row < n && fire[i]->col >= 0 && fire[i]->col < n) {
				count++;
				ListNode* f = fire[i];
				int r = f->row;
				int c = f->col;
				//printf("x:%d, y:%d\n", r, c);

				//Add array bounds checking LATER
				if(forest[r+1][c] == 'X') {
					forest[r+1][c] = '*';

					ListNode* right = NULL;
					right = (ListNode*)malloc(sizeof(ListNode));
					right->row = r+1;
					right->col = c;
					newfire[index] = right;
					newfirec++;
					index++;
				}
				if(forest[r-1][c] == 'X') {

					forest[r-1][c] = '*';

					ListNode* left = NULL;
					left = (ListNode*)malloc(sizeof(ListNode));
					left->row = r-1;
					left->col = c;
					newfire[index] = left;
					newfirec++;
					index++;
				}
				if(forest[r][c+1] == 'X') {

					forest[r][c+1] = '*';

					ListNode* up = NULL;
					up = (ListNode*)malloc(sizeof(ListNode));
					up->row = r;
					up->col = c+1;
					newfire[index] = up;
					newfirec++;
					index++;
				}
				if(forest[r][c-1] == 'X') {

					forest[r][c-1] = '*';

					ListNode* down = NULL;
					down = (ListNode*)malloc(sizeof(ListNode));
					down->row = r;
					down->col = c-1;
					newfire[index] = down;
					newfirec++;
					index++;
				}

			}
		}
		for(int j=0; j<burntc; j++) {
			if(burnt[j] != NULL) {
				ListNode* f = burnt[j];
				forest[f->col][f->row] = '-';
			}
		}





		//size = c;
		size--;
		//burnt = fire;
		memcpy(burnt, fire, sizeof(fire));
		burntc = firec;
		//fire = newfire;
		memcpy(fire, newfire, sizeof(newfire));
		firec = newfirec;

		steps++;
		system("clear");
		printArr(n, n, forest);
		sleep(1);
	}
	return 0;
}
