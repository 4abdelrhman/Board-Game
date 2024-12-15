#ifndef _SUS_GAME_H
#define _SUS_GAME_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

template <typename T>
class S_U_S_board : public Board<T> {
public:
    S_U_S_board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

private:
    bool check_SUS_sequence(int x, int y, T symbol);
};

template <typename T>
class S_U_S_Player : public Player<T> {
public:
    S_U_S_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class S_U_S_Random_Player : public RandomPlayer<T> {
public:
    S_U_S_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
S_U_S_board<T>::S_U_S_board() {
    this->rows = this->columns = 3;
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
bool S_U_S_board<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void S_U_S_board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

template <typename T>
bool S_U_S_board<T>::check_SUS_sequence(int x, int y, T symbol) {
    static const int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
    for (auto& dir : directions) {
        int dx = dir[0], dy = dir[1];
        if (x - dx >= 0 && y - dy >= 0 && x + dx < this->rows && y + dy < this->columns) {
            if (this->board[x - dx][y - dy] == 'S' &&
                this->board[x][y] == 'U' &&
                this->board[x + dx][y + dy] == 'S') {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
bool S_U_S_board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == 'U' && check_SUS_sequence(i, j, 'U')) {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
bool S_U_S_board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool S_U_S_board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
S_U_S_Player<T>::S_U_S_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void S_U_S_Player<T>::getmove(int& x, int& y)
{
    string X,Y;
    while (true)
    {
        cout << "Enter the value of x and y (0 to 2) separate by space: " << endl;
        cin >> X >> Y;

        stringstream ss1(X);
        stringstream ss2(Y);
        if ((ss1 >> x && ss1.eof()) && (ss2 >> y && ss2.eof()) && (x != -1 && y != -1) )
        {
            break;
        }

        else
        {
            cout << "Invalid. (x,y) accept only integers value ! " << endl;
            cout << endl;
        }

    }

}



template <typename T>
S_U_S_Random_Player<T>::S_U_S_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void S_U_S_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif
