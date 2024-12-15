class TicTacToe5x5 : public Board<char> {
public:
    TicTacToe5x5() {
        rows = 5;
        columns = 5;
        n_moves = 0;

        board = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new char[columns];
            fill(board[i], board[i] + columns, '_');
        }
    }

    ~TicTacToe5x5() {
        for (int i = 0; i < rows; ++i) {
            delete[] board[i];
        }
        delete[] board;
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
        for (int i = 0; i < rows; i++) {
            cout << "\n| ";
            for (int j = 0; j < columns; j++) {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << board[i][j] << " |";
            }
            cout << "\n----------------------------------------------------";
        }
        cout << endl;
    }

    bool is_win() override {
        return n_moves >= 24;
    }

    bool is_draw() override {
        if (n_moves >= 24) {
            int countX = count_three_in_a_row('X');
            int countO = count_three_in_a_row('O');
            return countX == countO;
        }
        return false;
    }

    bool game_is_over() override {
        return is_win();
    }

    void display_final_result() {
        int countX = count_three_in_a_row('X');
        int countO = count_three_in_a_row('O');

        cout << "Game Over! Final Scores:\n";
        cout << "Player X: " << countX << " sequences\n";
        cout << "Player O: " << countO << " sequences\n";

        if (countX > countO) {
            cout << "Player X wins!\n";
        } else if (countO > countX) {
            cout << "Player O wins!\n";
        } else {
            cout << "It's a tie!\n";
        }
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

class TicTacToePlayer : public Player<char> {
public:
    TicTacToePlayer(string name, char symbol) : Player<char>(name, symbol) {}

    void getmove(int& x, int& y) override {
        cout << name << " (" << symbol << "), enter your move (row and column): ";
        cin >> x >> y;
    }
};

class TicTacToeRandomPlayer : public RandomPlayer<char> {
public:
    TicTacToeRandomPlayer(char symbol) : RandomPlayer<char>(symbol) {
        srand(time(nullptr));
    }

    void getmove(int& x, int& y) override {
        x = rand() % 5;
        y = rand() % 5;
    }
};
