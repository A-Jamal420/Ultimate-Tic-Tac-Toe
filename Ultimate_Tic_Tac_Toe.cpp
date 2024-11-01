#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

// ANSI color codes
string RED = "\033[31m";
string GREEN = "\033[32m";
string CYAN = "\033[36m";
string RESET = "\033[0m";
string YELLOW = "\033[93m";
string dimYELLOW = "\033[33m";
string MAGENTA = "\033[95m";

void JomeG() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

class SmallBoard {
public:
    SmallBoard() : grid(3, vector<char>(3, ' ')), winner(' ') {}

    void makeMove(int row, int col, char player) {
        if (grid[row][col] == ' ') {
            grid[row][col] = player;
            checkWinner();
        }
    }

    char getWinner() const {
        if (winner != ' ') return winner;
        return isFull() ? 'D' : ' ';
    }

    bool isFull() const {
        for (auto& row : grid) {
            for (char cell : row) {
                if (cell == ' ') return false;
            }
        }
        return true;
    }

    const vector<vector<char>>& getGrid() const {
        return grid;
    }

    char getCell(int row, int col) { // New getCell method
        if (row >= 0 && row < 3 && col >= 0 && col < 3) return grid[row][col];
        return ' '; // Return a space for invalid indices
    }

private:
    vector<vector<char>> grid;
    char winner;

    void checkWinner() {
        // Check rows and columns
        for (int i = 0; i < 3; i++) {
            if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0] != ' ')
                winner = grid[i][0];
            if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[0][i] != ' ')
                winner = grid[0][i];
        }
        // Check diagonals
        if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != ' ')
            winner = grid[0][0];
        if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[0][2] != ' ')
            winner = grid[0][2];

        if (winner != ' ') {
            for (auto& row : grid) {
                for (auto& cell : row) cell = winner;
            }
        }
    }
};

class UltimateTicTacToe {
private:
    vector<vector<SmallBoard>> largeBoard;
    char currentPlayer = 'X';
    int moveCount = 0;
    int nextSmallRow = -1;
    int nextSmallCol = -1;

public:
    UltimateTicTacToe() : largeBoard(3, vector<SmallBoard>(3)) {}

    void playGame() {
        
        while (moveCount < 81) {
            display();
            int smallRow, smallCol, row, col;

            // Determine where the next player should play
            if (nextSmallRow != -1 && nextSmallCol != -1) 
                cout << CYAN << "Player " << RESET << MAGENTA << currentPlayer << RESET << CYAN << ", your next move is restricted to small board ("
                    << nextSmallRow << ", " << nextSmallCol << ").\n" << RESET;

            while (true) {
                // Check if the next small board is full or finished
                //if (nextSmallRow != -1 && nextSmallCol != -1 &&
                //    (largeBoard[nextSmallRow][nextSmallCol].isFull() ||
                //        largeBoard[nextSmallRow][nextSmallCol].getWinner() != ' ')) {
                //    cout << CYAN << "The small board (" << nextSmallRow << ", " << nextSmallCol
                //        << ") is full or won. You can play in any of the following available boards:\n" << RESET;

                //    vector<pair<int, int>> availablePositions;
                //    for (int i = 0; i < 3; i++) {
                //        for (int j = 0; j < 3; j++) {
                //            if (!largeBoard[i][j].isFull() && largeBoard[i][j].getWinner() == ' ') {
                //                availablePositions.emplace_back(i, j);
                //            }
                //        }
                //    }

                //    // Display the available positions
                //    if (availablePositions.empty()) {
                //        cout << "No available moves left! It's a draw!\n";
                //        return;
                //    }
                //    else {
                //        cout << "Available positions: ";
                //        for (const auto& pos : availablePositions) {
                //            cout << "(" << pos.first << ", " << pos.second << ") ";
                //        }
                //        cout << "\n";
                //    }
                //    nextSmallRow = -1; // Resetting next small row and col
                //    nextSmallCol = -1;
                //}

                cout << CYAN << "Enter your move (bigRow bigCol row col): " << RESET;
                try {
                    cin >> smallRow >> smallCol >> row >> col;
                    cout << endl;
                    // Check if input is valid
                    if (cin.fail()) throw runtime_error(RED + "Invalid input. Please enter integers." + RESET);

                    // Validate move
                    if (smallRow < 0 || smallRow > 2 || smallCol < 0 || smallCol > 2 ||
                        row < 0 || row > 2 || col < 0 || col > 2) {
                        cout << RED << "Invalid input! Indices must be between 0 and 2.\n" << RESET;
                        continue; // Prompt for a new move
                    }

                    // If the next small board is defined, check if the player is trying to play there
                    if (nextSmallRow != -1 && nextSmallCol != -1) {
                        if (smallRow != nextSmallRow || smallCol != nextSmallCol) {
                            cout << RED << "Invalid input! You must play in small board ("
                                << nextSmallRow << ", " << nextSmallCol << ").\n" << RESET;
                            continue; // Prompt for a new move
                        }
                    }

                    // Check if the small board is finished
                    if (largeBoard[smallRow][smallCol].isFull() ||
                        largeBoard[smallRow][smallCol].getWinner() != ' ') {
                        cout << RED << "Invalid input! The small board (" << smallRow << ", " << smallCol
                            << ") has already finished! Please play in another board.\n" << RESET;
                        continue; // Prompt for a new move
                    }

                    // Check if the cell is already occupied
                    if (largeBoard[smallRow][smallCol].getCell(row, col) != ' ') {
                        cout << RED << "Invalid input! There's already a mark in this position, play elsewhere!\n" << RESET;
                        continue; // Prompt for a new move
                    }

                    break; // Break the loop if input is valid

                }
                catch (runtime_error e) {
                    cin.clear(); // Clear the error state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the bad input
                    cout << e.what() << "\n"; // Display the error message
                }
            }

            // Make the move
            largeBoard[smallRow][smallCol].makeMove(row, col, currentPlayer);
            moveCount++;

            // Check if the small board is won
            char smallWinner = largeBoard[smallRow][smallCol].getWinner();
            if (smallWinner != ' ' && smallWinner != 'D') cout << GREEN << "Small board won by " << smallWinner << "!\n\n" << RESET;
            else if (smallWinner == 'D') cout << MAGENTA << "Small board (" << smallRow << ", " << smallCol << ") is a draw.\n\n" << RESET;

            // Check if the current player has won the large board
            checkLargeBoardWinner(smallRow, smallCol, currentPlayer);

            // Switch player
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';

            // Update the next small board based on the current player's move
            nextSmallRow = row;
            nextSmallCol = col;
        }

        cout << "Game over. It's a draw!\n";
    }

    void checkLargeBoardWinner(int smallRow, int smallCol, char player) {
        // Check if the large board has a winner based on the small board results
        vector<vector<char>> winningCombination = {
            {largeBoard[smallRow][0].getWinner(), largeBoard[smallRow][1].getWinner(), largeBoard[smallRow][2].getWinner()},
            {largeBoard[0][smallCol].getWinner(), largeBoard[1][smallCol].getWinner(), largeBoard[2][smallCol].getWinner()},
            {largeBoard[0][0].getWinner(), largeBoard[1][1].getWinner(), largeBoard[2][2].getWinner()},
            {largeBoard[0][2].getWinner(), largeBoard[1][1].getWinner(), largeBoard[2][0].getWinner()}
        };

        for (auto& line : winningCombination) {
            if (line[0] == player && line[1] == player && line[2] == player) {
                display();
                cout << GREEN << "Player " << player << " wins the game!\n" << RESET;
                exit(0); // Exit the game
            }
        }

        // Check if all smallboards are complete
        bool allComplete = true;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (largeBoard[i][j].getWinner() == ' ') { // ' ' indicates an incomplete board
                    allComplete = false;
                    break;
                }
            }
            if (!allComplete) break;
        }

        // If all sub-boards are complete and no winner, it's a draw
        if (allComplete) {
            display();
            cout << YELLOW << "It's a draw! No moves left and no winner.\n" << RESET;
            exit(0); // Exit the game
        }
    }

    void display() {
        cout << "====== Ultimate Tic Tac Toe ======\n\n";
        for (int smallRow = 0; smallRow < 3; smallRow++) {
            for (int row = 0; row < 3; row++) {
                for (int smallCol = 0; smallCol < 3; smallCol++) {
                    auto& smallGrid = largeBoard[smallRow][smallCol].getGrid();
                    cout << smallGrid[row][0] << " | " << smallGrid[row][1] << " | " << smallGrid[row][2];
                    if (smallCol < 2) cout << dimYELLOW << "  | " << RESET; // Space between small boards
                }
                cout << "\n";
                if (row < 2) {
                    for (int smallCol = 0; smallCol < 3; smallCol++) {
                        cout << "---------";
                        if (smallCol < 2) cout << dimYELLOW << "  | " << RESET; // Space between small boards
                    }
                    cout << "\n";
                }
            }
            if (smallRow < 2) {
                for (int smallCol = 0; smallCol < 3; smallCol++) {
                    cout << dimYELLOW << "=========" << RESET; // Larger grid line
                    if (smallCol < 2) cout << dimYELLOW << "  | " << RESET; // Space between small boards
                }
                cout << "\n";
            }
        }
        cout << "\n"; // Space after the entire grid

        // If the next small board is full or won, reset the restriction
        if (nextSmallRow != -1 && nextSmallCol != -1 && (largeBoard[nextSmallRow][nextSmallCol].isFull() ||
            largeBoard[nextSmallRow][nextSmallCol].getWinner() != ' ')) {
            cout << YELLOW << "Player " << currentPlayer << ", your next restricted board ("
                << nextSmallRow << ", " << nextSmallCol
                << ") is full or won. You can play in any available board!\n" << RESET;
            nextSmallRow = -1;
            nextSmallCol = -1;
        }
    }
};

int main() {
    JomeG();
    UltimateTicTacToe game;
    game.playGame();
    return 0;
}