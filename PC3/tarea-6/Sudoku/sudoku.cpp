#include <iostream>
#include <vector>

using namespace std;

int get_cell(int row, int col) {
    return (row / 3) * 3 + col / 3;
}

pair<int, int> next_empty_position(vector<vector<char>>& board, int row, int col) {
    while (row < 9) {
        if (board[row][col] == '.') {
            return {row, col};
        }
        col = (col + 1) % 9;
        row = row + (col == 0 ? 1 : 0);
    }
    return {9, 0}; // End of board
}

bool isValid(vector<vector<char>>& board, int row, int col, char num) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num || board[i][col] == num || board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == num) {
            return false;
        }
    }
    return true;
}

bool solve(vector<vector<char>>& board, int row, int col) {
    auto [r, c] = next_empty_position(board, row, col);

    if (r == 9) // End of board
        return true;

    for (char num = '1'; num <= '9'; num++) {
        if (isValid(board, r, c, num)) {
            board[r][c] = num;
            if (solve(board, r, c))
                return true;
            board[r][c] = '.'; // Reset if solution not found
        }
    }
    return false;
}

void solveSudoku(vector<vector<char>>& board) {
    solve(board, 0, 0);
}

void print_board(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << "\n";
    }
}

int main() {
    vector<vector<char>> board = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };

    cout << "Initial board:\n";
    print_board(board);

    solveSudoku(board);

    cout << "\nSolved board:\n";
    print_board(board);

    return 0;
}
