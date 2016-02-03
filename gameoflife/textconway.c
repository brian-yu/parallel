#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define R	80
#define C	80

int pause = 0;
int grid[R*C] = { 0 };

grid[1] = 1;
grid[R+2] = 1;
grid[2*R] = 1;
grid[2*R+1] = 1;
grid[2*R+2] = 1;


int neighbors[8] = {C, C+1, C-1, 1, -1, -C, -C-1, -C+1};

int neighborCount(int pos) {
    int count = 0;
    for (int i=0; i < 8; i++) {
        int nPos = pos + neighbors[i];
        int nRow = nPos / C;
        int nCol = nPos % C;
        int row = pos / C;
        int col = pos % C;
        if (nPos >= 0 && nPos <= R*C && abs(row-nRow) == 1 && abs(col-nCol) == 1) {
            if(grid[nPos] == 1) {
                count++;
            }
        }
    }
    return count;
}

void displayGrid() {
    for (int i=0; i<R*C; i++) {
        if (i%R == 0) {
            printf("\n");
        }
        if (grid[i] == 1) {
            printf("X");
        } else {
            printf(".");
        }
    }
}

int main(int argc, char * argv[]) {
    system("clear");
    
    displayGrid();
    while (1) {
        for (int i=0; i<R*C; i++) {
            int nCount = neighborCount(i);
            if (grid[i] == 1) {
                if (nCount < 2) {
                    grid[i] = 0;
                } else if (nCount < 4) {
                    grid[i] = 1;
                } else {
                    grid[i] = 0;
                }
            } else if (nCount == 3) {
                grid[i] = 1;
            }
        }
        displayGrid();
        sleep(0.5);
        system("clear");
    }
    
    
    
    return 0;
}