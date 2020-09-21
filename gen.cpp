#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 16
#define Nsqrt 4
#define fillGrade 3

using namespace std;

bool checkBoard(int grid[N][N], int row, int col, int k) {
    for (int i = 0; i < N; i++) {
        if (grid[i][col] == k || grid[row][i] == k || grid[((int)floor(row / Nsqrt) * Nsqrt) + ((int)floor((i) / Nsqrt))][((int)floor(col / Nsqrt) * Nsqrt) + (i % Nsqrt)] == k) {
            return false;
        }
    }
    return true;
}

void writeSolved(string name, int grid[N][N]) {
    ofstream solved;
    solved.open("sudokus/" + name + ".sudoku");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            solved << grid[i][j] << ";";
            if (j == N - 1) {
                solved << "\n";
            }
        }
    }
    solved.close();
    return;
}

void createSudoku(string name) {

    // 16 - int grid[N][N] = {{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
    // 9 - int grid[N][N] = {{}, {}, {}, {}, {}, {}, {}, {}, {}};
    int grid[N][N] = {{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};

    srand (time(NULL));

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int should = (int)(rand() % fillGrade + 1);
            if(should == fillGrade) {
                int num = (int)(rand() % N + 1);
                if(checkBoard(grid, i, j, num)) {
                    grid[i][j] = num;
                }
            }
        }
    }

    writeSolved(name, grid);

}

int main(int argc, char *argv[]) {
    for(int i = 0; i < stoi(argv[1]); i++) {
        createSudoku(("s"+ to_string(i)));
    }
    return 0;
}