#include <stdio.h>
#include <math.h>

int main( int argc, const char* argv[])
{
    FILE* fin = fopen( "decodeME.txt" , "r" );
    char msg[10101];
    //char *chars = " \',-.ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //printf("%c",chars[1]);
    int numbytes;
    numbytes = fread( msg , 1 , 10000 , fin );

    //printf("\nNumber of bits: %f\n", bits);

    msg[numbytes] = '\0' ; // null character
    //printf( "%c\n" , msg[0] );
    //printf( "%d\n" , numbytes ) ;
    //printf( "\n" ) ;

    char tree[10000];
    //tree[0] = '\0';
    //printf("tree[1] = %c\n", tree[1]);

    int i = 0;
    int c = 0;
    while(c < 55) {
        char character = msg[i];
        i++;
        int index = 0;
        while(msg[i] == '0' || msg[i] == '1') {
            if(msg[i] == '0'){
                index = 2*index + 1;
                i++;
            }
            if(msg[i] == '1'){
                index = 2*index + 2;
                i++;
            }
        }
        tree[index] = character;
        c++;
    }
    int freq[256] = {0};

    char decoded[10000];
    int index = 0;
    int k = 0;
    int b = 0;
    while(msg[i] != '\0') {
        if(msg[i] == '0') {
            index = 2*index + 1;
            b++;
        }
        if(msg[i] == '1') {
            index = 2*index + 2;
            b++;
        }
        if(tree[index] != '\0') {
            decoded[k] = tree[index];
            int freqIndex = (int)tree[index];
            freq[freqIndex]++;
            index = 0;
            k++;
        }
        i++;
    }

    for(int j = 0; j<sizeof(decoded); j++) {
        printf("%c",decoded[j]);
    }
    printf("\n");

    float cBits = (k)*8; //or is it (k+1)*8

    printf("Compression ratio: %f\n\n", (cBits-b)/cBits);

    double shannon = 0;
    //double total = 0;
    // for(int m = 0; m < 100; m++) {
    //     total += freq[m];
    // }
    for(int l = 0; l < 256; l++) {
        if(freq[l] != 0) {
            shannon += (freq[l] * -1 * log2(freq[l]/(float)k));
        }
    }
    printf("%d\n", k);
    printf("Shannon number: %f\n\n", shannon);

    return 0 ;
}
