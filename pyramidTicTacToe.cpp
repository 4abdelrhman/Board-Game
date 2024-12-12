#include<iostream>
#include<string>
#include<fstream>
#include<unordered_set>
#include<ctime>
#include<cstdlib>
#include "3x3X_O.h"
#include "BoardGame_Classes.h"
using namespace std;

template <typename T>
class PyramidBoard : public Board<T> {
public:
    PyramidBoard() {
        this->rows = 3;
        this->columns = 5;
        this->n_moves = 0;

        this->board = new T*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new T[2 * i + 1];
            for (int j = 0; j < 2 * i + 1; ++j) {
                this->board[i][j] = '#';
            }
        }
    }

    ~PyramidBoard() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

    bool update_board(int x, int y, T symbol) override {
        if (x >= 0 && x < this->rows && y >= 0 && y < (2 * x + 1) && this->board[x][y] == '#') {
            this->board[x][y] = symbol;
            this->n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override {
        for (int i = 0; i < this->rows; ++i) {
            for (int space = 0; space < this->rows - i - 1; ++space) {
                cout << "  ";
            }
            for (int j = 0; j < 2 * i + 1; ++j) {
                cout << this->board[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool is_win() override {
        char symbol = (this->n_moves % 2 == 0) ? 'O' : 'X';

        // Horizontal Check
        for (int i = 0; i < this->rows; ++i) {
            int count = 0;
            for (int j = 0; j < 2 * i + 1; ++j) {
                if (this->board[i][j] == symbol)
                    count++;
                else
                    count = 0;

                if (count == 3) return true;
            }
        }

        // Vertical Check
        for (int col = 0; col < this->columns; ++col) {
            int count = 0;
            for (int row = 0; row < this->rows; ++row) {
                if (col < 2 * row + 1 && this->board[row][col] == symbol)
                    count++;
                else
                    count = 0;

                if (count == 3) return true;
            }
        }

        // Diagonal Check (Top to bottom-right)
        for (int start_row = 0; start_row < this->rows; ++start_row) {
            for (int start_col = 0; start_col < 2 * start_row + 1; ++start_col) {
                int count = 0;
                for (int row = start_row, col = start_col; 
                    row < this->rows && col < 2 * row + 1; 
                    ++row, ++col) {
                    if (this->board[0][0] == symbol && this->board[1][2] == symbol && this->board[2][4] == symbol )
                        count++;
                    else
                        count = 0;

                    if (count == 3) return true;
                }
            }
        }

        // Diagonal Check (Top to bottom-left)
        for (int start_row = 0; start_row < this->rows; ++start_row) {
            for (int start_col = 0; start_col < 2 * start_row + 1; ++start_col) {
                int count = 0;
                for (int row = start_row, col = start_col; 
                    row < this->rows && col >= 0; 
                    ++row, --col) {
                    if (this->board[row][col] == symbol)
                        count++;
                    else
                        count = 0;

                    if (count == 3) return true;
                }
            }
        }

        return false;
    }

    bool is_draw() override {
        return this->n_moves == 9 && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

};


template <typename T>
class pyramidGame : public GameManager<T> {
public:
    pyramidGame(Board<T>* board, Player<T>* playerPtr[2])
        : GameManager<T>(board, playerPtr) {}
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
class computerPlayer : public RandomPlayer<T>{
public:
    computerPlayer(T symbol) : RandomPlayer<T>(symbol){
        srand(static_cast<unsigned>(time(0)));
    }
    void getmove(int& x , int& y) override{
        x = rand() % 3;
        y = rand() % (2 * x + 1);
    }
};



int main() {
    int mode;
    string player1, player2;
    cout << "1-Human vs Human\n";
    cout << "2-Human vs Computer" << endl;
    cout << "Choose a mode: ";
    cin >> mode;
    Player<char>* players[2];
    if(mode == 1){
        cout << "Enter Player 1's name: ";
        cin >> player1;
        cout << "Enter Player 2's name: ";
        cin >> player2;

        Player<char>* players[2] = {
            new HumanPlayer<char>(player1, 'X'),
            new HumanPlayer<char>(player2, 'O')
        };

        PyramidBoard<char>* board = new PyramidBoard<char>();
        pyramidGame<char> game(board, players);
        game.run();
        delete board;
        delete players[0];
        delete players[1];
    }else if(mode == 2){
        cout << "Enter player's 1 name: ";
        cin >> player1;
        players[0] = new HumanPlayer<char>(player1 , 'X');
        players[1] = new computerPlayer<char>('O');
        PyramidBoard<char>* board = new PyramidBoard<char>();
        pyramidGame<char> game(board, players);
        game.run();
        delete board;
    }else{
        cout << "Invalide option";
    }
    return 0;
}