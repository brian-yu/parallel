#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


void decode(char arr[][300]);  //MUST tell c the size of the second dimension
void printArr(char *arr[], int size);




typedef struct Node
{
	char symbol ;
	//
	long int frequency ;
	//
	struct Node* left ;
	struct Node* right ;
	//
} TreeNode ;

void recur(TreeNode* root, int depth, char codeword[50], char codewords[256][50])
{
    if(root->left == NULL && root->right == NULL) {
        codeword[depth] = '\0';
        sprintf(codewords[root->symbol], "%s", codeword);
    }
    else {
        if(root->left != NULL) {
            codeword[depth] = '0';
            recur(root->left, depth+1, codeword, codewords);
        }
        if(root->right != NULL) {
            codeword[depth] = '1';
            recur(root->right, depth+1, codeword, codewords);
        }
    }
}

int main(int argc, char *argv[])
{


    //FILE* fin = fopen( "encodeME.txt" , "r" );
    //FILE* fin = fopen( "mobydick.txt" , "r" );
    //FILE* fin = fopen( "LOSSLESS.txt" , "r" );
	FILE* fin = fopen( "encodeIN.txt" , "r" );

    char msg[1010101];
    long int numbytes;
    numbytes = fread( msg , 1 , 1000000 , fin );
    msg[numbytes] = '\0' ;

    long int i = 0;
    long int freq[256] = {0};
    while(i < numbytes) {
        int index = (int)msg[i];
        freq[index]++;
        i++;
    }

    // for (int j = 0; j < numbytes; j++) {
    //     printf("%d: %c\n", j, msg[j]);
    // }

    int n = 0;
    TreeNode* arr[256];
    for(int j = 0; j < 256; j++) {
        if(freq[j] != 0 && freq[j] != '\0') {
            //printf("%c: %d\n", (int)j, freq[j]);
            n++;
            TreeNode* t = NULL;
            t = (TreeNode*)malloc( sizeof(TreeNode) );
            t -> symbol = (char)j;
            t -> frequency = freq[j];
            t -> left = NULL;
            t -> right = NULL;
				arr[j] = t;

        }
    }
    //printf("%d\n", n);

	for(int j=0; j<256; j++) {
		if(arr[j] != NULL) {
		int index = j;
		for(int k=j; k<256; k++) {
			if(arr[k] != NULL) {
      	//printf("%d, %d", arr[index]->frequency, arr[k]->frequency);
			if(arr[index]->frequency > arr[k]->frequency) {
				index = k;
      	}
			}
		}
		TreeNode* temp = arr[j];
		arr[j] = arr[index];
		arr[index] = temp;
		}
	}

	TreeNode* array[n];
	int k = 0;
	for(int i = 0; i < 256; i++) {
    	if(arr[i] != NULL) {
			array[k] = arr[i];
			k++;
			//printf("%d %c: %li\n", (int)arr[i]->symbol, arr[i]->symbol, arr[i]->frequency);
   		}
	}
	//printf("NUMBYTES: %li\n", numbytes);

	for(i=0; i<k; i++) {

		long int min1int = 999999;
		TreeNode* min1 = NULL;
		long int min1index = 0;
		for(long int j=0; j<k; j++) {
			if(array[j] != NULL && array[j]->frequency < min1int) {
				min1 = array[j];
				min1index = j;
				min1int = array[j]->frequency;
			}
		}
		array[min1index] = NULL;
		//printf("1 %d %c: %li\n", (int)min1->symbol, min1->symbol, min1->frequency);

		if(min1->frequency == numbytes) {
			array[0] = min1;
			break;
		}

		long int min2int = 999999;
		long int min2index = 0;
		TreeNode* min2 = NULL;
		for(long int l=0; l<k; l++) {
			if(array[l] != NULL && array[l]->frequency < min2int && array[l] != min1) {

				min2 = array[l];
				min2index = l;
				min2int = array[l]->frequency;
			}
		}
		array[min2index] = NULL;
		//printf("2 %d %c: %li\n", (int)min2->symbol, min2->symbol, min2->frequency);


		TreeNode* n = NULL;
		n = (TreeNode*)malloc(sizeof(TreeNode));
		n -> symbol = '*';
		n -> frequency = min1->frequency + min2->frequency;
		if(min1 != NULL)
			n -> left = min1;
		if(min2 != NULL)
			n -> right = min2;

		long int index = 0;
		for(long int m=0; m<k; m++) {
			if(array[m] == NULL) {
				index = m;
			}
		}

		array[index] = n;

	}
	//printf("-------------------------------------------\n");
	TreeNode* root = array[0];
	//printf("%c: %li\n", root->symbol, root->frequency);


	//preorderPrint(root);

	int depth;
	char codeword[50];
	char codewords[256][50];

    recur(root, 0, codeword, codewords);

    //FILE *fout = fopen("schema.txt", "w");
    FILE *fout = fopen("encodeOUT1.txt", "w");
	

    for(int i = 0; i < 256; i++) {
        if((char)i != '\0' && codewords[i][0] != '\0') {
            if((char)i == '\n')
                //printf("%s", "\\n");
                fprintf(fout, "%s", "\\n");
            else
                //printf("%c", (char)i);
                fprintf(fout, "%c", (char)i);
            int j = 0;
            for(int j = 0; j < 50; j++) {
                if(codewords[i][j] != '\0')
                    //printf("%c", codewords[i][j]);
                    fprintf(fout, "%c", codewords[i][j]);
            }
            //printf("\n");
            fprintf(fout, "\n");
        }
    }
    //printf("======================================\n");

    //FILE *fout2 = fopen("encoded.txt", "w");
    FILE *fout2 = fopen("encodeOUT2.txt", "w");

    i = 0;
	int j = 0;
	//int freq[256] = {0};
    while(msg[i] != '\0') {
        //printf("%c: ", msg[i]);
        int index = (int)msg[i];

        //printf("%s", codewords[index]);
        fprintf(fout2, "%s", codewords[index]);

        for(int k = 0; k < 50; k++) {
			if(codewords[index][k] != '\0') {
				j++;
			}
		}

		//freq[i]++;
        //printf("\n");
        // for(int j = 0; j < 50; j++) {
        //     if(codewords[index][j] != '\0')
        //
        // }
        i++;
    }
    //printf("\n");

	printf("Compression ratio: %f\n", ((float)numbytes*8-j)/((float)numbytes*8));

	float shannon = 0;
	for(int l = 0; l < 256; l++) {
        if(freq[l] != 0) {
            shannon += (freq[l] * -1 * log2(freq[l]/(float)numbytes));
        }
    }
	printf("Shannon number: %f\n\n", shannon);

    return 0;
}
