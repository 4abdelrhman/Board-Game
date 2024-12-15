#ifndef _NUMERICAL_TIC_TAC_TOE_H
#define _NUMERICAL_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
#include <vector>
#include <unordered_set>
#include <iomanip>
using namespace std;

template <typename T>
class num_tic_tac_toe:public Board<T>
{
public:
    num_tic_tac_toe ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
private:
    unordered_set<int> Numbers;
    vector<int>NumbersOfPlayer_1 = {1, 3, 5, 7, 9};
    vector<int>NumbersOfPlayer_2 = {2, 4, 6, 8};
};

template <typename T>
class num_tic_tac_toe_player : public Player<T>
{
public:
    num_tic_tac_toe_player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class num_tic_tac_toe_RandomPlayer : public RandomPlayer<T>
{
public:
    num_tic_tac_toe_RandomPlayer(T symbol);
    void getmove(int &x, int &y) ;
};

template<class T>
num_tic_tac_toe<T>::num_tic_tac_toe()
{
   this->rows = 3;
    this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}
template <typename T>
bool num_tic_tac_toe<T>::update_board(int x, int y, T symbol)
{
    if(x == -1 && y == -1)
    {
        if(symbol == 'X')
        {
            while (true)
            {
                x = rand() % this->rows;
                y = rand() % this->columns;
               int rand_number = ((rand() % 5) * 2 + 1);
               if(Numbers.count(rand_number) == 0 && this->board[x][y] == 0)
               {
                    Numbers.insert(rand_number);
                    this->board[x][y] = rand_number + '0';
                    this->n_moves++;
                    return true;
               }
            }

        }
        else if (symbol == 'O')
        {
            while (true)
            {
                x = rand() % this->rows;
                y = rand() % this->columns;
               int rand_number = ((rand() % 5) * 2);
               if(Numbers.count(rand_number) == 0 && this->board[x][y] == 0 && rand_number != 0 )
               {
                    Numbers.insert(rand_number);
                    this->board[x][y] = rand_number + '0';
                    this->n_moves++;
                    return true;
               }
            }
        }
    }
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0 )
    {
        return false;
    }
    while (true)
    {
        cout << "Your Numbers are: " ;
        if (symbol == 'X')
        {
            for (const auto& n : NumbersOfPlayer_1)
            {
                cout << n << " ";
            }
            cout << endl;
        }
        if (symbol == 'O')
        {
            for (const auto& n : NumbersOfPlayer_2)
            {
                cout << n << " ";
            }
            cout << endl;
        }
        string number;
        int num;
        while (true)
        {

            cout << "Enter Number: " << endl;
            cin >> number;

            stringstream ss1(number);
            if ((ss1 >> num && ss1.eof())  )
            {
                break;
            }
            else
            {
                cout << "Oops! Enter only integer value" << endl;
            }
        }

        if (symbol == 'X')
        {
            if (num % 2 == 1 && num >= 1 && num <= 9 && Numbers.count(num) == 0)
            {
                this->board[x][y] = num + '0';
                Numbers.insert(num);
                NumbersOfPlayer_1.erase(remove(NumbersOfPlayer_1.begin(), NumbersOfPlayer_1.end(), num));
                this->n_moves++;
                return true;
            }
        }
        else if (symbol == 'O')
        {

            if (num % 2 == 0 && num > 0 && num <= 8 && Numbers.count(num) == 0)
            {
                this->board[x][y] = num + '0';
                Numbers.insert(num);
                NumbersOfPlayer_2.erase(remove(NumbersOfPlayer_2.begin(), NumbersOfPlayer_2.end(), num));
                this->n_moves++;
                return true;
            }
        }
        cout << "Invalid number. Please try again.\n";
    }


}
template <typename T>
void num_tic_tac_toe<T>::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++)
        {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}
template <typename T>
bool num_tic_tac_toe<T>::is_win()
{
    for (int i = 0; i < this->rows; i++)
    {
        if ((this->board[i][0] - '0') + (this->board[i][1] - '0') + (this->board[i][2] - '0') == 15)
        {
            return true;
        }
    }
    for (int j = 0; j < this->columns; j++)
    {
        if ((this->board[0][j] - '0') + (this->board[1][j] - '0') + (this->board[2][j] - '0') == 15)
        {
            return true;
        }
    }
    if ((this->board[0][0] - '0') + (this->board[1][1] - '0') + (this->board[2][2] - '0') == 15)
    {
        return true;
    }
    if ((this->board[2][0] - '0') + (this->board[1][1] - '0') + (this->board[0][2] - '0') == 15)
    {
        return true;
    }
    return false;
}

template <typename T>
bool num_tic_tac_toe<T>::is_draw()
{
    return (this->n_moves == this->rows * this->columns && !is_win());
}

template <typename T>
bool num_tic_tac_toe<T>::game_is_over()
{
    return is_win() || is_draw();
}
template <typename T>
num_tic_tac_toe_player<T>::num_tic_tac_toe_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void num_tic_tac_toe_player<T>::getmove(int& x, int& y)
{
    string inputX,inputY;
    while (true)
    {
        cout << "Enter the value of x and y (0 to 2) separate by space: " << endl;
        cin >> inputX >> inputY;

        stringstream ss1(inputX);
        stringstream ss2(inputY);
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
template<class T>
num_tic_tac_toe_RandomPlayer<T>::num_tic_tac_toe_RandomPlayer(T symbol) :RandomPlayer<T>(symbol)
{
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}
template <typename T>
void num_tic_tac_toe_RandomPlayer<T>::getmove(int& x, int& y)
{

    y = -1;
    x = -1;
}
#endif