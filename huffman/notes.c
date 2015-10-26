/*
decode:
1. ASCII message
  N = # of characters
    can count encoded bits (bits = characters * 8)
    or you can count characters that are being printed
2. calculation of compression ratio

  (N*8 - bits)/(N*8)

  Make sure it doesn't do integer division
3. Shannon number
*/

int freq[256] = {0}
char symbol = 'E';
int index = (int)symbol;
freq[index]++;

/*

gcc -lm _____.c
sum of all frequencies should be equal to 28 (which is total number of symbols)

Sum of all symbols(freq * log2(probability))

probability = freq of symbol / total number of characters
*/


/*
ENCODE
*/

char* message = "LOSSLESS";
/*
Symbol  freq
'L'       2
'O'       1
'S'       4
'E'       1
*/
TreeNode* array[256];
//The array contains TreeNodes of symbols and frequencies that have two null children
//We will collapse the array into a single Tree
//In a loop, find the two nodes in the array that have the smallest frequency
  //Add a new node to the end, whose symbol is irrelevant, that contains the sum of the two smallest frequencies
  //The children of this node are the two smallest nodes





/*
ENCODE PROBLEM

function definition:
    can define before main
    can define after main
        must add function prototype

can store in a 2D array
char codewords[256][300];

/*
#include <stdio.h>

void f(int);

int main()
{
    f(7);
    return 0
}

void f(int x)
{
    x;
}



Common Bugs in C


spritnf - print to a string
fprintf - print to a file

be aware of array bounds
*/

char *itoa(int x)
{
    char *retval = (char*)malloc(sizeof(char) * 100);
    sprintf(retval, x);
    return retval;
}

//buffer override in C ---- look into it

/* ENCODE STEPS
Step 1: Find frequency for each symbol
*/
int freq[256] = {0};
//count non-zero frequencies and store them in N
/*
Step 2: Make an array of TreeNode pointers
*/
TreeNode* arr[256];
/*
Step 3: Collapse array into a single binary tree

(Loop) find 2 minimum frequencies and then make a new node to collapse them
*/
/*
Step 4: Walk tree and then read out codewords
*/

int depth;
char codewords[256][50];
char codeword[50];
if(/*basecase*/) {
	codeword[depth] = '\0';
	sprintf(codewordS[symbol], "%s", codeword);
} else {
	_______'0'
	recur left
	_______'1'
	recur right
}
