#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Constants
const char PLAYER = 'X';
const char AI = 'O';
const char EMPTY = ' ';

// Function declarations
void printBoard(const vector<vector<char>>& board);
bool isMovesLeft(const vector<vector<char>>& board);
int evaluate(const vector<vector<char>>& board);
int minimax(vector<vector<char>>& board, bool isMax);
pair<int, int> findBestMove(vector<vector<char>>& board);
void playGame();

int main() {
    playGame();
    return 0;
}

// Function to print the board
void printBoard(const vector<vector<char>>& board) {
    cout << "  0   1   2\n";
    for (int i = 0; i < 3; ++i) {
        cout << i << " ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << " ---+---+---\n";
    }
    cout << endl;
}

// Check if moves are left on the board
bool isMovesLeft(const vector<vector<char>>& board) {
    for (const auto& row : board)
        for (char cell : row)
            if (cell == EMPTY)
                return true;
    return false;
}

// Evaluate the board for winning conditions
int evaluate(const vector<vector<char>>& board) {
    for (int row = 0; row < 3; ++row)
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == AI) return +10;
            if (board[row][0] == PLAYER) return -10;
        }

    for (int col = 0; col < 3; ++col)
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == AI) return +10;
            if (board[0][col] == PLAYER) return -10;
        }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == AI) return +10;
        if (board[0][0] == PLAYER) return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == AI) return +10;
        if (board[0][2] == PLAYER) return -10;
    }

    return 0;
}

// Minimax algorithm
int minimax(vector<vector<char>>& board, bool isMax) {
    int score = evaluate(board);
    if (score == 10) return score;
    if (score == -10) return score;
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    best = max(best, minimax(board, false));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;
                    best = min(best, minimax(board, true));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

// Find the best move for AI
pair<int, int> findBestMove(vector<vector<char>>& board) {
    int bestValue = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) {
                board[i][j] = AI;
                int moveValue = minimax(board, false);
                board[i][j] = EMPTY;

                if (moveValue > bestValue) {
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }
    return bestMove;
}

// Main game loop
void playGame() {
    vector<vector<char>> board(3, vector<char>(3, EMPTY));
    printBoard(board);

    while (true) {
        int x, y;
        cout << "Enter your move (row and column): ";
        cin >> x >> y;

        if (board[x][y] != EMPTY) {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        board[x][y] = PLAYER;
        printBoard(board);

        if (evaluate(board) == -10) {
            cout << "You win!\n";
            break;
        }

        if (!isMovesLeft(board)) {
            cout << "It's a draw!\n";
            break;
        }

        pair<int, int> bestMove = findBestMove(board);
        int aiX = bestMove.first;
        int aiY = bestMove.second;

        board[aiX][aiY] = AI;
        cout << "AI made its move:\n";
        printBoard(board);

        if (evaluate(board) == 10) {
            cout << "AI wins!\n";
            break;
        }

        if (!isMovesLeft(board)) {
            cout << "It's a draw!\n";
            break;
        }
    }
}
