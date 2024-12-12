#include "BoardGame_Classes.h"
#include <vector>
#include "3x3X_O.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>

using namespace std;

template <typename T>
class X_O_9x9_Board : public Board<T> {
private:
    vector<pair<int, int>> completedGrids;
    X_O_Board<char>* innerBoard;
    int activeGridX;
    int activeGridY;

public:
    static int gridState;
    static int nextX;
    static int nextY;

    X_O_9x9_Board() {
        activeGridX = -1;
        activeGridY = -1;
        this->rows = 9;
        this->columns = 9;
        this->n_moves = 0;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char[this->columns];
            fill(this->board[i], this->board[i] + this->columns, '#');
        }
        innerBoard = new X_O_Board<char>();
    }

    ~X_O_9x9_Board() {
        for (int i = 0; i < this->rows; i++) {
            delete[] this->board[i];
        }
        delete[] this->board;
        delete innerBoard;
    }

    bool update_board(int gridX, int gridY, T symbol) {
        int filledCells = 0;

        if (gridX == -1 && gridY == -1) {
            // Random grid selection logic
            if (gridState == 0) {
                gridX = rand() % 3;
                gridY = rand() % 3;
                for (const auto& grid : completedGrids) {
                    if (grid.first == gridX && grid.second == gridY) {
                        gridState = 0;
                        return false;
                    }
                }
            } else {
                gridX = nextX;
                gridY = nextY;
                for (const auto& grid : completedGrids) {
                    if (grid.first == gridX && grid.second == gridY) {
                        gridState = 0;
                        return false;
                    }
                }
            }

            activeGridX = gridX;
            activeGridY = gridY;
            int startX = gridX * 3;
            int startY = gridY * 3;

            for (int i = startX; i < startX + 3; i++) {
                for (int j = startY; j < startY + 3; j++) {
                    if (this->board[i][j] == 'X' || this->board[i][j] == 'O') {
                        filledCells++;
                    }
                }
            }

            if (filledCells < 9) {
                int subX, subY;
                do {
                    subX = rand() % 3;
                    subY = rand() % 3;
                } while (this->board[startX + subX][startY + subY] != '#');

                this->board[startX + subX][startY + subY] = toupper(symbol);
                this->n_moves++;

                nextX = subX;
                nextY = subY;
                gridState = 1;
                return true;
            }
            return false;
        } else {
            for (const auto& grid : completedGrids) {
                if (grid.first == gridX && grid.second == gridY) {
                    return false;
                }
            }

            if (gridX < 0 || gridX > 2 || gridY < 0 || gridY > 2) {
                return false;
            }

            activeGridX = gridX;
            activeGridY = gridY;

            int startX = gridX * 3;
            int startY = gridY * 3;

            for (int i = startX; i < startX + 3; i++) {
                for (int j = startY; j < startY + 3; j++) {
                    if (this->board[i][j] == 'X' || this->board[i][j] == 'O') {
                        filledCells++;
                    }
                }
            }

            if (filledCells < 9) {
                int subX, subY;
                cout << "Enter your move (x y) [0-2]: ";
                cin >> subX >> subY;

                while (subX < 0 || subX > 2 || subY < 0 || subY > 2 || this->board[startX + subX][startY + subY] != '#') {
                    cout << "Invalid move. Enter again (x y): ";
                    cin >> subX >> subY;
                }

                this->board[startX + subX][startY + subY] = toupper(symbol);
                this->n_moves++;

                nextX = subX;
                nextY = subY;
                gridState = 1;
                return true;
            }
            return false;
        }
    }


    void display_board() {
        cout << "Board Layout:\n";
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << (this->board[i][j] == 0 ? '.' : this->board[i][j]) << ' ';
                if ((j + 1) % 3 == 0 && j < 8) cout << "|| ";
            }
            cout << '\n';
            if ((i + 1) % 3 == 0 && i < 8) cout << "===============================\n";
        }
    }

    bool is_win() {
        if (activeGridX != -1 && activeGridY != -1) {
            vector<vector<char>> grid(3, vector<char>(3));

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    grid[i][j] = this->board[activeGridX * 3 + i][activeGridY * 3 + j];
                }
            }

            for (int i = 0; i < 3; i++) {
                if ((grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0] != '#') ||
                    (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[0][i] != '#')) {
                    innerBoard->update_board(activeGridX, activeGridY, grid[i][0]);
                    completedGrids.emplace_back(activeGridX, activeGridY);
                    return true;
                }
            }

            if ((grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != '#') ||
                (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[0][2] != '#')) {
                innerBoard->update_board(activeGridX, activeGridY, grid[1][1]);
                completedGrids.emplace_back(activeGridX, activeGridY);
                return true;
            }
        }

        return innerBoard->is_win();
    }

    bool is_draw() {
        return this->n_moves == this->rows * this->columns;
    }

    bool game_is_over() {
        return is_win() || is_draw();
    }
};

// Static member definitions
template <typename T>
int X_O_9x9_Board<T>::gridState = 0;

template <typename T>
int X_O_9x9_Board<T>::nextX = 0;

template <typename T>
int X_O_9x9_Board<T>::nextY = 0;

template<typename T>
class UltimateGame : public GameManager<T> {
public:
    UltimateGame(Board<T>* board, Player<T>* PlayerPtr[2]) :
    GameManager<T>(board, PlayerPtr) {}
};

template <typename T>
class HumanPlayer : public Player<T> {
public:
    HumanPlayer(string n, T symbol) : Player<T>(n, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->name << " (" << this->symbol << "), enter your move (eg 0 0): ";
        cin >> x >> y;
    }
};

template<typename T>
class computerPlayer : public RandomPlayer<T> {
public:
    computerPlayer(T symbol) : RandomPlayer<T>(symbol) {
        srand(static_cast<unsigned>(time(0)));
    }
    void getmove(int& x, int& y) override {
        x = -1 ;
        y = -1 ;
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));
    cout << "Welcome to Ultimate Tic-Tac-Toe!" << endl;
    int mode;
    cout << "1 - Human vs Human\n";
    cout << "2 - Human vs Computer\n";
    cout << "Choose a mode: ";
    cin >> mode;

    Player<char>* players[2];
    string player1, player2;

    if (mode == 1) {
        cout << "Enter Player 1's name: ";
        cin >> player1;
        cout << "Enter Player 2's name: ";
        cin >> player2;

        players[0] = new HumanPlayer<char>(player1, 'X');
        players[1] = new HumanPlayer<char>(player2, 'O');
    } else if (mode == 2) {
        cout << "Enter Player 1's name: ";
        cin >> player1;

        players[0] = new HumanPlayer<char>(player1, 'X');
        players[1] = new computerPlayer<char>('O');
    } else {
        cout << "Invalid mode selected. Exiting..." << endl;
        return 1;
    }

    X_O_9x9_Board<char>* board = new X_O_9x9_Board<char>();

    UltimateGame<char> game(board, players);

    game.run();

    delete board;
    delete players[0];
    delete players[1];

    return 0;
}
