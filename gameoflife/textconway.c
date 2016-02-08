#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define R	40
#define C   40

int neighborCount(int pos, int grid[R*C]) {
    int neighbors[8] = {C, C+1, C-1, 1, -1, -C, -C-1, -C+1};
    int count = 0;
    for (int i=0; i < 8; i++) {
        int nPos = pos + neighbors[i];
        int nRow = nPos / C;
        int nCol = nPos % C;
        int row = pos / C;
        int col = pos % C;
        if (nPos >= 0 && nPos < R*C && abs(row-nRow) <= 1 && abs(col-nCol) <= 1 && nPos != pos) {
            if(grid[nPos] == 1) {
                count++;
            }
        }
    }
    return count;
}

void displayGrid(int grid[R*C]) {
    for (int i=0; i<R*C; i++) {
        if (i%R == 0) {
            printf("\n");
        }
        if (grid[i] == 1) {
            printf("\u2588");
        } else {
            printf("\u2591");
        }
    }
    printf("\n");
}

int liveCount(int grid[R*C]) {
    int count = 0;
    for (int i=0; i<R*C; i++) {
        if (grid[i] ==  1) {
            count++;
        }
    }
    return count;
}

int main(int argc, char * argv[]) {
    int grid[R*C] = { 0 };
    grid[1] = 1;
    grid[R+2] = 1;
    grid[2*R] = 1;
    grid[2*R+1] = 1;
    grid[2*R+2] = 1;
    
    int pos[] = {25, C+25, C+23};
    
    int iter = 1;
    
    system("clear");
    displayGrid(grid);
    usleep(100000);
    system("clear");
    while (liveCount(grid)) {
        
        int newGrid[R*C] = { 0 };
        
        for (int i=0; i<R*C; i++) {
            int nCount = neighborCount(i, grid);
            if (grid[i] == 1) {
                //printf("%d\n", nCount);
                if (nCount < 2) {
                    newGrid[i] = 0;
                } else if (nCount < 4) {
                    newGrid[i] = 1;
                } else {
                    newGrid[i] = 0;
                }
            } else if (nCount == 3) {
                newGrid[i] = 1;
            }
        }
        
        for (int i=0; i<R*C; i++) {
            grid[i] = newGrid[i];
        }
        if (iter%18 == 0) {
            grid[1] = 1;
            grid[R+2] = 1;
            grid[2*R] = 1;
            grid[2*R+1] = 1;
            grid[2*R+2] = 1;
        }
        displayGrid(newGrid);
        usleep(50000);
        system("clear");
        iter++;
    }
    
    
    
    return 0;
}