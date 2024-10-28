#include <iostream>
#include <vector>

using namespace std;

/*  

    Declaración de funciones

 */
pair<int, int> nextEmptyPosition(vector<vector<char>> &board, int row, int col);

bool isValid(vector<vector<char>> &board, int row, int col, char num);

bool solve(vector<vector<char>> &board, int row, int col);

void solveSudoku(vector<vector<char>> &board);

void printBoard(const vector<vector<char>> &board);

void sudokuPredeterminado();

void sudokuPersonalizado();

/*  
    
    Main

*/

int main() {
    cout << "SUDOKU\n";
    int choice;
    do {
        cout << "Elija una de las siguientes opciones:\n"
             << "1. Tablero Predeterminado\n"
             << "2. Tablero Personalizado\n"
             << "0. Salir\n\n";
        cin >> choice;

        switch (choice) {
            case 0:
                break;
            case 1:
                sudokuPredeterminado();
                break;
            case 2:
                sudokuPersonalizado();
                break;
            default:
                cout << "La opción elegida es inválida.\n";
                break;
        }

    } while (choice != 0);

    return 0;
}

/*


Funciones necesarias para el algoritmo


*/

pair<int, int> nextEmptyPosition(vector<vector<char>> &board, int row, int col) {
    while (row < 9) {
        if (board[row][col] == '.') {
            return make_pair(row, col);
        }
        col = (col + 1) % 9;
        row = row + (col == 0 ? 1 : 0);
    }
    return make_pair(9, 0);
}

bool isValid(vector<vector<char>> &board, int row, int col, char num) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num || board[i][col] == num ||
            board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == num) {
            return false;
        }
    }
    return true;
}

bool solve(vector<vector<char>> &board, int row, int col) {
    pair<int, int> pos = nextEmptyPosition(board, row, col);
    int r = pos.first;
    int c = pos.second;

    if (r == 9) return true;

    for (char num = '1'; num <= '9'; num++) {
        if (isValid(board, r, c, num)) {
            board[r][c] = num;
            if (solve(board, r, c)) return true;
            board[r][c] = '.';
        }
    }
    return false;
}

void solveSudoku(vector<vector<char>> &board) {
    solve(board, 0, 0);
}

void printBoard(const vector<vector<char>> &board) {
    for (int i = 0; i < 9; ++i) {
        if (i % 3 == 0 && i != 0) {
            cout << "-------+--------+-------\n";
        }
        for (int j = 0; j < 9; ++j) {
            if (j % 3 == 0 && j != 0) {
                cout << " | ";
            }
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n\n";
}

void sudokuPredeterminado() {
    vector<vector<char>> board = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                  {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                  {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                  {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                  {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                  {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                  {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                  {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                  {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    cout << "Tablero Inicial:\n";
    printBoard(board);

    solveSudoku(board);

    cout << "\nTablero Resuelto:\n";
    printBoard(board);
}

void sudokuPersonalizado() {
    vector<vector<char>> board(9, vector<char>(9, '.'));
    cout << "Ingrese el tablero de Sudoku fila por fila, usando '.' para las celdas vacías.\n";

    for (int i = 0; i < 9; i++) {
        cout << "Fila " << i + 1 << " (ingrese 9 caracteres separados por espacios): ";
        for (int j = 0; j < 9; j++) {
            cin >> board[i][j];
        }
    }

    cout << "\nTablero Ingresado:\n";
    printBoard(board);

    solveSudoku(board);

    cout << "\nTablero Resuelto:\n";
    printBoard(board);
}