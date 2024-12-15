//
// Created by Yousef Esmail on 12/12/2024.
//

#ifndef MAIN_MENUE_BORDGAME_MISERE_TIC_TAC_TOE_H
#define MAIN_MENUE_BORDGAME_MISERE_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "iomanip"
using namespace std;
class misere_TicTacToe : public Board<char> {
public:
    misere_TicTacToe() {
        rows = 3;
        columns = 3;
        n_moves = 0;
        board = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new char[columns];
            fill(board[i], board[i] + columns, '_');
        }
    }

    bool update_board(int x, int y, char symbol) override {
        if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != '_') {
            return false;
        }
        board[x][y] = symbol;
        n_moves++;
        return true;
    }
    void display_board() override {
        for (int i = 0; i < this->rows; i++) {
            cout << "\n| ";
            for (int j = 0; j < this->columns; j++) {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " |";
            }
            cout << "\n---------------------------";
        }
        cout << endl;
    }

    bool is_win() override {
        return  check_winner('X')  || check_winner('O')  ;


    }

    bool is_draw() override {
        return n_moves == rows * columns && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

private:
    bool check_winner(char symbol) {
        int countX = count_three_in_a_row('X');
        int countO = count_three_in_a_row('O');
        if (countX > 0 ) {
            cout << "Player O wins!\n";
            n_moves ++ ;
            return true ;

        } else if (countO > 0) {
            cout << "Player X wins!\n";
            n_moves ++ ;
            return true ;

        } else
            return false ;
    }
    int count_three_in_a_row(char symbol) {
        int count = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns - 2; ++j) {
                if (board[i][j] == symbol && board[i][j + 1] == symbol && board[i][j + 2] == symbol) {
                    count++;
                }
            }
        }
        for (int i = 0; i < rows - 2; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (board[i][j] == symbol && board[i + 1][j] == symbol && board[i + 2][j] == symbol) {
                    count++;
                }
            }
        }
        for (int i = 0; i < rows - 2; ++i) {
            for (int j = 0; j < columns - 2; ++j) {
                if (board[i][j] == symbol && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == symbol) {
                    count++;
                }
            }
        }
        for (int i = 0; i < rows - 2; ++i) {
            for (int j = 2; j < columns; ++j) {
                if (board[i][j] == symbol && board[i + 1][j - 1] == symbol && board[i + 2][j - 2] == symbol) {
                    count++;
                }
            }
        }
        return count;
    }
};

class misere_TicTacToePlayer : public Player<char> {
public:
    misere_TicTacToePlayer(string name, char symbol) : Player(name, symbol) {}

    void getmove(int& x, int& y) override {
        cout <<  "Player (" << symbol << "), enter your move (row and column): ";
        cin >> x >> y;
    }
};

class misere_TicTacToeRandomPlayer : public RandomPlayer<char> {
public:
    misere_TicTacToeRandomPlayer(string name, char symbol) : RandomPlayer<char>(symbol) {
        this->name = name ;
        srand(time(nullptr));
    }
    void getmove(int& x, int& y) override {
        x = rand() % 5;
        y = rand() % 5;
    }
};



#endif //MAIN_MENUE_BORDGAME_MISERE_TIC_TAC_TOE_H
