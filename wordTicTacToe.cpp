#include<iostream>
#include<string>
#include<fstream>
#include<unordered_set>
#include<ctime>
#include<cstdlib>
#include "3x3X_O.h"
#include "BoardGame_Classes.h"
using namespace std;


template<typename T>
class wordBoard : public Board<T>{
private:
    unordered_set<string>words;
public:
    wordBoard(){
        this->rows = 3;
        this->columns = 3;
        this->n_moves = 0;
        this->board = new T*[this->rows];
        
        for(int i = 0; i < this->rows; ++i){
            this->board[i] = new T[this->columns];
            for(int j = 0; j < this->columns; ++j){
                this->board[i][j] = '#';
            }
        }
        ifstream file("dic.txt");
        string word;
        while(file >> word){
            if(word.size() == 3){
                words.insert(word);
            }
        }
    }
    ~wordBoard(){
        for(int i = 0; i < this->rows; ++i){
            delete[] this->board[i];
        }
        delete[] this-> board;
    }
    bool update_board(int x, int y,T symbol ) override{
        if(x == -1 && y == -1){
            x = rand() % 3;
            y = rand() % 3;
            while(this->board[x][y] != '#'){
                x = rand() % 3;
                y = rand() % 3;
            }
            char letter = 'A' + (rand() % 26);
            letter = toupper(letter) ;
            cout << "Computer chooses position (" << x << ", " << y << ") with letter '" << letter << "'." << endl;
            letter = toupper(letter);
            this->board[x][y] = letter;
            this->n_moves++;
            return true;
        }
        if(x < 0 || x>=this->rows || y < 0 || y>=this->columns || this->board[x][y] != '#'){
            return false;
        }
        char letter;
        cout << "Enter a letter: ";
        cin >> letter;
        letter = toupper(letter);
        this->board[x][y] = letter;
        this->n_moves++;
        return true;
    }
    
    void display_board() override {
        for(int i = 0; i < this->rows; ++i){
            for(int j = 0; j < this->columns; ++j){
                cout << this->board[i][j] <<" ";
            }
            cout << endl;
        }
    }

    bool is_win() override{
        for(int i = 0; i < 3; ++i){
            string row = string(1 , this->board[i][0]) + string(1 , this->board[i][1]) + string(1,this->board[i][2]);
            if(words.find(row) != words.end()){
                return true;
            }
            string col = string(1,this->board[0][i]) + string(1,this->board[1][i]) + string(1,this->board[2][i]);
            if(words.find(col)!=words.end()){
                return true;
            }
        }  


        string diag1 = string(1,this->board[0][0]) + string(1,this->board[1][1]) + string(1, this->board[2][2]);
        if(words.find(diag1) != words.end()){
            return true;
        }
        string diag2 = string(1 , this->board[0][2]) + string(1 , this->board[1][1]) + string(1 , this->board[2][0]);
        if(words.find(diag2) != words.end()){
            return true;
        }

        return false;
    }


    bool is_draw() override{
        return this->n_moves == 9 && !is_win();
    }
    bool game_is_over() override {
        return is_draw() || is_win();
    }
};


template <typename T>
class wordGame: public GameManager<T> {
public:
    wordGame(Board<T>* board, Player<T>* playerPtr[2])
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

template <typename T>
class wordComp : public RandomPlayer<T>{
public:
    wordComp(T symbol) : RandomPlayer<T>(symbol){
        srand(static_cast<unsigned>(time(0)));
    }
    void getmove(int& x, int& y) override {
        x = -1;
        y = -1;
    }
};

int main(){
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

        players[0] = new HumanPlayer<char>(player1, 'X');
        players[1] = new HumanPlayer<char>(player2, 'O');

        wordBoard<char>* board = new wordBoard<char>();
        wordGame<char> game(board, players);
        game.run();

        delete board;
        delete players[0];
        delete players[1];
    }
    else if(mode == 2){
        cout << "Enter Player's 1 name: ";
        cin >> player1;
        
        players[0] = new HumanPlayer<char>(player1, 'X');
        
        players[1] = new wordComp<char>('O');
        
        wordBoard<char>* board = new wordBoard<char>();
        wordGame<char> game(board, players);
        game.run();

        delete board;
        delete players[0];
        delete players[1];
    }
    else{
        cout << "Invalid option!" << endl;
    }

    return 0;
}