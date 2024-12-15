#include <iostream>
#include "FourInARow.h"
#include "BoardGame_Classes.h"
#include "NumericalTicTacToe.h"
#include "sus_game.h"
#include "5x5tictactoe.h"
#include "Misere Tic Tac Toe.h"
#include "pyramic tic-tac-toe.h"
#include "word tic-tac-toe.h"
#include "ultimateTicTacToe.h"
using namespace std;


void FourInRow (){
        int choice;
        Player<char>* players[2];
        four_in_row_board<char>* board = new four_in_row_board<char>();
        string player1Name, player2Name;

        cout << endl;
        cout << "<<<<<<<<<< Four-in-a-Row Game >>>>>>>>>\n";
        cout << endl;

        cout << "Enter Player 1 name (X): ";
        cin >> player1Name;
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        switch(choice) {
            case 1:
                players[0] = new four_in_row_player<char>(player1Name, 'X');
                break;
            case 2:
                players[0] = new four_in_row_random_player<char>('X');
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";

        }

        cout << "Enter Player 2 name (O): ";
        cin >> player2Name;
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;

        switch(choice) {
            case 1:
                players[1] = new four_in_row_player<char>(player2Name, 'O');
                break;
            case 2:
                players[1] = new four_in_row_random_player<char>('O');
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";

        }

        GameManager<char> game(board, players);
        game.run();

        delete board;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }
}
//////////////////////////////////////
void NumericalTicTacToe (){
    int choice;
    Player<char>* players[2];
    num_tic_tac_toe<char>* B = new num_tic_tac_toe<char>();
    string playerXName, player2Name;

    cout << endl;
    cout << "<<<<<<<<< Numerical_Tic_Tac_Toe Game >>>>>>>>>\n";
    cout << endl;
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new num_tic_tac_toe_player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new num_tic_tac_toe_RandomPlayer<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";

    }

    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new num_tic_tac_toe_player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new num_tic_tac_toe_RandomPlayer<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";

    }

    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

}
///////////////////////////////////////
void SUS (){
    int choice;
    Player<char>* players[2];
    S_U_S_board<char>* board = new S_U_S_board<char>();
    string player1Name, player2Name;

    cout << endl;
    cout << "<<<<<<<<< S-U-S Game >>>>>>>>>!\n";
    cout << endl;

    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new S_U_S_Player<char>(player1Name, 'S');
            break;
        case 2:
            players[0] = new S_U_S_Random_Player<char>('S');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
    }

    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new S_U_S_Player<char>(player2Name, 'U');
            break;
        case 2:
            players[1] = new S_U_S_Random_Player<char>('U');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
    }

    GameManager<char> gameManager(board, players);
    gameManager.run();

    delete board;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

}
/////////////////////////////////////////
void tictac5x5 () {
int choice;
    Player<char>* players[2];
    Board<char>* board = new TicTacToe5x5();
    string playerXName, playerOName;

    cout << "************************ Welcome to the 5x5 Tic Tac Toe Game! ************************ \n";

    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n1. Human\n2. Random Computer\n";
    while (true) {
        cin >> choice;
        if (choice < 1 || choice > 2) {
            cout << "Invalid input, please enter 1 or 2.\n";
            continue;
        } else {
            break;
        }
    }

    if (choice == 1) {
        players[0] = new TicTacToePlayer(playerXName, 'X');
    } else {
        players[0] = new TicTacToeRandomPlayer('X');
    }

    cout << "Enter Player O name: ";
    cin >> playerOName;
    cout << "Choose Player O type:\n1. Human\n2. Random Computer\n";
    while (true) {
        cin >> choice;
        if (choice < 1 || choice > 2) {
            cout << "Invalid input, please enter 1 or 2.\n";
            continue;
        } else {
            break;
        }
    }

    if (choice == 1) {
        players[1] = new TicTacToePlayer(playerOName, 'O');
    } else {
        players[1] = new TicTacToeRandomPlayer('O');
    }

    GameManager<char> game(board, players);
    game.run();
    dynamic_cast<TicTacToe5x5*>(board)->display_final_result();

    delete board;
    delete players[0];
    delete players[1];

}
////////////////////////////////////////////
void misereTicTacToe (){

        Player<char>* players[2];
        Board<char>* board = new misere_TicTacToe();
        string playerXName, playerOName;
        int cchoice ;
        cout << "************************ Welcome to the 3x3 Misere Tic Tac Toe Game! ************************ \n";
        cout << "Who do you want to play with? \n 1- With your friend \n 2- With computer " << endl ;
        while (true){
            cin >> cchoice ;
            if (cchoice < 1 || cchoice > 2 ){
                cout << "invalid input , please enter 1 or 2 " << endl ;
                continue;
            }
            else
                break;
        }

        if (cchoice == 1){
            cout << "Enter Player X name: "<< endl ;
            cin >> playerXName;
            cout << "Enter Player O name: "<< endl ;
            cin >> playerOName;

            players[0] =  static_cast<Player<char>*>(new misere_TicTacToePlayer(playerOName, 'X'));
            players[1] =  static_cast<Player<char>*>(new misere_TicTacToePlayer(playerXName, 'O'));

        }
        if (cchoice == 2 ){
            cout << "Enter the human Player name: "<< endl ;
            cin >> playerOName;

            players[0] =  static_cast<Player<char>*>(new misere_TicTacToePlayer("computer", 'X')) ;

            players[1] =  static_cast<Player<char>*>(new misere_TicTacToeRandomPlayer(playerOName , 'O'));
        }
        GameManager<char> game(board, players);
        game.run();
        delete board;
        delete players[0];
        delete players[1];

}
/////////////////////////////////
void Pyramic (){
    cout << " <<<<<<<<<<<<<< Pyramic Tic-Tac-Toe >>>>>>>>>>>>>>>> "<< endl ;
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
}
/////////////////////////////////
void Wordttt (){
    cout << "<<<<<<<<<<<<<<<< Word Tic-Tac-Toe >>>>>>>>>>>>>>>> "<< endl ;

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

        players[0] = new wordHumanPlayer<char>(player1, 'X');
        players[1] = new wordHumanPlayer<char>(player2, 'O');

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

        players[0] = new wordHumanPlayer<char>(player1, 'X');

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
}
////////////////////////////////////////////////////////////////
void Ultimate (){
    cout << "<<<<<<<<<<<<<< Ultimate Tic-Tac-Toe >>>>>>>>>>>>>>>> "<< endl ;

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

        players[0] = new UltimateHumanPlayer<char>(player1, 'X');
        players[1] = new UltimateHumanPlayer<char>(player2, 'O');
    } else if (mode == 2) {
        cout << "Enter Player 1's name: ";
        cin >> player1;

        players[0] = new UltimateHumanPlayer<char>(player1, 'X');
        players[1] = new ultimatecomputerPlayer<char>('O');
    } else {
        cout << "Invalid mode selected. Exiting..." << endl;

    }

    X_O_9x9_Board<char>* board = new X_O_9x9_Board<char>();

    UltimateGame<char> game(board, players);

    game.run();

    delete board;
    delete players[0];
    delete players[1];
}


int main() {

        int choice;

        do {

            cout << "==========================" << endl;
            cout << "         Main Menu        " << endl;
            cout << "==========================" << endl;
            cout << "1 - Pyramic Tic-Tac-Toe " << endl;
            cout << "2 - Four in a-row " << endl;
            cout << "3 - 5x5 Tic-Tac-Toe " << endl;
            cout << "4 - Word Tic-Tac-Toe " << endl;
            cout << "5 - Numerical Tic-Tac-Toe" << endl;
            cout << "6 - Misere Tic-Tac-Toe " << endl;
            cout << "8 - Ultimate Tic-Tac-Toe " << endl ;
            cout << "9 - S-U-S " << endl;
            cout << "10- exit " << endl ;
            cout << "==========================" << endl;
            cout << "Enter your choice: " << endl ;

            cin >> choice;

            switch (choice) {
                case 1:
                    Pyramic() ;
                    break;
                case 2:
                    FourInRow() ;
                    break;
                case 3:
                    tictac5x5() ;
                    break;
                case 4:
                    Wordttt() ;
                    break;
                case 5:
                    NumericalTicTacToe();
                    break;
                case 6:
                    misereTicTacToe();
                    break;
                case 8:
                    Ultimate() ;
                    break;
                case 9:
                    SUS() ;
                    break;
                case 10:
                    cout << "Exiting the program. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice! Please try again." << endl;
            }

            cout << endl;

        } while (choice != 10 );

        return 0;
    }


