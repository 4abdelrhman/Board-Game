#ifndef _FOUR_IN_A_ROW_H
#define _FOUR_IN_A_ROW_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

template <typename T>
class four_in_row_board : public Board<T> {
public:
    four_in_row_board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class four_in_row_player : public Player<T> {
public:
    four_in_row_player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class four_in_row_random_player : public RandomPlayer<T> {
public:
    four_in_row_random_player(T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
four_in_row_board<T>::four_in_row_board() {
    this->rows = 6;
    this->columns = 7;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool four_in_row_board<T>::update_board(int x, int y, T symbol) {
    if (y >= 0 && y < this->columns && this->board[0][y] == 0) {
        for (int i = this->rows - 1; i >= 0; --i) {
            if (this->board[i][y] == 0) {
                this->board[i][y] = symbol;
                this->n_moves++;
                return true;
            }
        }
    }
    return false;
}

template <typename T>
void four_in_row_board<T>::display_board() {
    cout << "  0  1  2  3  4  5  6"<<endl;
    for (int i = 0; i < this->rows; i++) {
        cout << "| ";
        for (int j = 0; j < this->columns; j++) {
            cout << (this->board[i][j] == 0 ? '.' : this->board[i][j]) << " |";
        }
        cout << "\n" << string(this->columns * 4 + 1, '-') << endl;
    }
    cout << endl;

}

template <typename T>
bool four_in_row_board<T>::is_win() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j <= this->columns - 4; ++j) {
            T symbol = this->board[i][j];
            if (symbol != 0 && symbol == this->board[i][j + 1] && symbol == this->board[i][j + 2] && symbol == this->board[i][j + 3]) {
                return true;
            }
        }
    }

    for (int i = 0; i <= this->rows - 4; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            T symbol = this->board[i][j];
            if (symbol != 0 && symbol == this->board[i + 1][j] && symbol == this->board[i + 2][j] && symbol == this->board[i + 3][j]) {
                return true;
            }
        }
    }

    for (int i = 0; i <= this->rows - 4; ++i) {
        for (int j = 0; j <= this->columns - 4; ++j) {
            T symbol = this->board[i][j];
            if (symbol != 0 && symbol == this->board[i + 1][j + 1] && symbol == this->board[i + 2][j + 2] && symbol == this->board[i + 3][j + 3]) {
                return true;
            }
        }
    }

    for (int i = 3; i < this->rows; ++i) {
        for (int j = 0; j <= this->columns - 4; ++j) {
            T symbol = this->board[i][j];
            if (symbol != 0 && symbol == this->board[i - 1][j + 1] && symbol == this->board[i - 2][j + 2] && symbol == this->board[i - 3][j + 3]) {
                return true;
            }
        }
    }

    return false;
}

template <typename T>
bool four_in_row_board<T>::is_draw() {
    return (this->n_moves == this->rows * this->columns) && !is_win();
}

template <typename T>
bool four_in_row_board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
four_in_row_player<T>::four_in_row_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void four_in_row_player<T>::getmove(int& x, int& y) {
    cout << "\nEnter your move (column index 0 to 6): ";
    while (true) {
        string input;
        cin >> input;
        bool is_valid = true;

        for (char c : input) {
            if (!isdigit(c)) {
                is_valid = false;
                break;
            }
        }

        if (is_valid) {
            y = stoi(input);
            if (y >= 0 && y <= 6) {
                break;
            }
        }
        cout << endl;
        cout << "Invalid. Enter integer number between 0 and 6: ";
        cin.clear();
    }

    x = -1;
}


template <typename T>
four_in_row_random_player<T>::four_in_row_random_player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void four_in_row_random_player<T>::getmove(int& x, int& y) {
    y = rand() % this->dimension;
    x = -1;
}

#endif
