#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stdio.h>
#include <vector>

#define N 9
#define Nsqrt 3

using namespace std;

void writeSolved(string name, int grid[N][N]) {
    ofstream solved;
    solved.open("solvedSudokus/" + name + "Solved");
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

bool checkBoard(int grid[N][N], int row, int col, int k) {
    for (int i = 0; i < N; i++) {
        if (grid[i][col] == k || grid[row][i] == k || grid[Nsqrt * (int)(row / Nsqrt) + (int)(i / Nsqrt)][Nsqrt * (int)(col / Nsqrt) + i % Nsqrt] == k) {
            return false;
        }
    }
    return true;
}

bool solveSudoku(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0) {
                for (int k = 1; k <= N; k++) {
                    if (checkBoard(grid, i, j, k) == true) {
                        grid[i][j] = k;
                        if (solveSudoku(grid) == true) {
                            return true;
                        }
                        else {
                            grid[i][j] = 0;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void openAndSolve(string name) {
    int grid[N][N] = { {}, {}, {}, {}, {}, {}, {}, {}, {} };

    string line;
    ifstream sudoku("sudokus/" + name);
    if (sudoku.is_open()) {
        int counter = 0;
        while (getline(sudoku, line, ';')) {
            if (counter % N == 0 && counter != 0) {
                grid[(int)counter / N][counter % N] = line[1] - 48;
            }
            else {
                grid[(int)counter / N][counter % N] = line[0] - 48;
            }
            counter++;
            if (counter+1 / N == N) {
                break;
            }
        }
        sudoku.close();
    }
    else cout << "Unable to open file";

    if (solveSudoku(grid) == true) {
        writeSolved(name, grid);
    }
    return;
}

int main() {
    system("dir /b /s /a-d *.sudoku > sudokus/files.sudok");
    std::ifstream file("sudokus/files.sudok");
    std::string str;
    vector<string> files;
    int counter = 0;
    if (file.is_open()) {
        while (std::getline(file, str)) {
            files.push_back(str.substr(str.find_last_of('\\') + 1, str.size()));
            counter++;
        }
    }
    for (int i = 0; i < counter; i++) {
        openAndSolve(files[i]);
    }

    return 0;
}