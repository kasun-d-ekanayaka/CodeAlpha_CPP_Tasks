// CodeAlpha Task 3: Sudoku Solver (backtracking)
#include <iostream>
#include <string>
using namespace std;

const int N = 9;
int grid[N][N];

void printGrid() {
    for (int r = 0; r < N; r++) {
        if (r % 3 == 0 && r != 0) cout << "------+-------+------\n";
        for (int c = 0; c < N; c++) {
            if (c % 3 == 0 && c != 0) cout << "| ";
            cout << (grid[r][c] == 0 ? "." : to_string(grid[r][c])) << " ";
        }
        cout << "\n";
    }
}

// Check row, column and 3x3 box rules
bool isSafe(int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num) return false;
        if (grid[i][col] == num) return false;
    }
    int boxR = row - row % 3, boxC = col - col % 3;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (grid[boxR + r][boxC + c] == num) return false;
    return true;
}

bool findEmpty(int &row, int &col) {
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == 0) return true;
    return false;
}

bool solve() {
    int row, col;
    if (!findEmpty(row, col)) return true;  // no empty cell: solved
    for (int num = 1; num <= 9; num++) {
        if (isSafe(row, col, num)) {
            grid[row][col] = num;
            if (solve()) return true;
            grid[row][col] = 0;             // backtrack
        }
    }
    return false;
}

// Make sure the starting puzzle has no conflicts
bool initialGridValid() {
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            if (grid[r][c] != 0) {
                int v = grid[r][c];
                grid[r][c] = 0;
                bool ok = isSafe(r, c, v);
                grid[r][c] = v;
                if (!ok) return false;
            }
    return true;
}

int main() {
    cout << "===== SUDOKU SOLVER =====\n";
    cout << "Enter the puzzle: 9 rows, 9 characters each.\n";
    cout << "Use digits 1-9 for given numbers and 0 or . for empty cells.\n\n";

    for (int r = 0; r < N; r++) {
        string line;
        while (true) {
            cout << "Row " << r + 1 << ": ";
            cin >> line;
            bool ok = line.size() == 9;
            for (char ch : line)
                if (!(ch == '.' || (ch >= '0' && ch <= '9'))) ok = false;
            if (ok) break;
            cout << "  Enter exactly 9 characters (digits, 0 or .).\n";
        }
        for (int c = 0; c < N; c++)
            grid[r][c] = (line[c] == '.') ? 0 : line[c] - '0';
    }

    cout << "\nYour puzzle:\n";
    printGrid();

    if (!initialGridValid()) {
        cout << "\nInvalid puzzle: it breaks the Sudoku rules.\n";
        return 1;
    }
    if (solve()) {
        cout << "\nSolved:\n";
        printGrid();
    } else {
        cout << "\nNo solution exists for this puzzle.\n";
    }
    return 0;
}

/* Sample input to test:
530070000
600195000
098000060
800060003
400803001
700020006
060000280
000419005
000080079
*/
