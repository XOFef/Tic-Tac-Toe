#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

void instructions();
char askYesNo(string question);
int askNumber(string question, int high, int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>& board);
char winner(const vector<char>& board);
bool isLegal(const vector<char>& board, int move);
int humanMove(const vector<char>& board, char human);
int computerMove(vector<char> board, char computer);
void announceWinner(char winner, char computer, char human);




int main()
{
    system("chcp 1251 > nul");
    int move;
    const int NUM_SQUARES = 9;
    vector<char> board(NUM_SQUARES, EMPTY);
    instructions();
    char human = humanPiece();
    char computer = opponent(human);
    char turn = X;
    displayBoard(board);
    while (winner(board) == NO_ONE) {
        if (turn == human) {
            move = humanMove(board, human);
            board[move] = human;
        }
        else {
            move = computerMove(board, computer);
            board[move] = computer;
        }
        displayBoard(board);
        turn = opponent(turn);
    }
    announceWinner(winner(board), computer, human);
    return 0;
}


void instructions() {
    cout << "Добро пожаловать на решающую битву человека и машины: крестики-нолики.\n";
    cout << "--где человеческий мозг противостоит кремниевому процессору\n\n";
    cout << "Сообщите о своем ходе, введя число от 0 до 8. Число\n";
    cout << "соответствует желаемому положению платы, как показано на рисунке:\n\n";
    cout << " 0 | 1 | 2\n";
    cout << " ---------\n";
    cout << " 3 | 4 | 5\n";
    cout << " ---------\n";
    cout << " 6 | 7 | 8\n\n";
    cout << "Приготовься, человек. Битва вот-вот начнется.\n\n";
}

char askYesNo(string question) {
    char response;
    do {
        cout << question << " (y/n): ";
        cin >> response;
    } while (response != 'y' && response != 'n');
    return response;
}

int askNumber(string question, int high, int low) {
    int number;
    do
    {
        cout << question << " (" << low << " - " << high << ") ";
        cin >> number;
    } while (number > high || number < low);
    return number;
}

char humanPiece() {
    char go_first = askYesNo("Вам нужен первый ход?");
    if (go_first == 'y') {
        cout << "\nТогда сделайте первый шаг. Вам это понадобится.\n";
        return X;
    }
    else {
        cout << "\nТвоя храбрость тебя погубит...Я пойду первым.\n";
        return O;
    }
}

char opponent(char piece) {
    if (piece == X) {
        return O;
    }
    else {
        return X;
    }
}

void displayBoard(const vector<char>& board) {
    cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
    cout << "\n\t" << "---------";
    cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
    cout << "\n\t" << "---------";
    cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
    cout << "\n\n";
}

char winner(const vector<char>& board) {
    const int WINNING_ROWS[8][3] = {
        {0,1,3},
        {3,4,5},
        {6,7,8},
        {0,3,6},
        {1,4,7},
        {2,5,8},
        {0,4,8},
        {2,4,6}
    };
    const int TOTAL_ROWS = 8;
    for (int row = 0; row < TOTAL_ROWS; ++row) {
        if ((board[WINNING_ROWS[row][0]] != EMPTY) && 
            (board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) && 
            (board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]])) {
            return board[WINNING_ROWS[row][0]];
        }
    }
    if (count(board.begin(), board.end(), EMPTY) == 0)
        return TIE;
    return NO_ONE;
}

bool isLegal(const vector<char>& board, int move) {
    return (board[move] == EMPTY);
}

int humanMove(const vector<char>& board, char human) {
    int move = askNumber("Куда ты собираешься сходить?", (board.size() - 1));
    while (!isLegal(board, move)) {
        cout << "\nЭта площадь уже занята, глупый человек.\n";
        move = askNumber("Куда ты собираешься сходить?", (board.size() - 1));
    }
    cout << "Fine...\n";
    return move;
}

int computerMove(vector<char> board, char computer) {
    unsigned int move = 0;
    bool found = false;
    while (!found && move < board.size())
    {
        if (isLegal(board, move)) {
            board[move] = computer;
            found = winner(board) == computer;
            board[move] = EMPTY;
        }
        if (!found) {
            ++move;
        }
    }
    if (!found) {
        move = 0;
        char human = opponent(computer);
        while (!found && move < board.size())
        {
            if (isLegal(board, move)) {
                board[move] = human;
                found = winner(board) == human;
                board[move] = EMPTY;
            }
            if (!found) {
                ++move;
            }
        }
    }
    if (!found) {
        move = 0;
        unsigned int  i = 0;
        const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };
        while (!found && move < board.size())
        {
            move = BEST_MOVES[i];
            if (isLegal(board, move)) {
                found = true;
            }
            ++i;
        }
    }
    cout << "Я возьму число " << move << endl;
    return move;
}

void announceWinner(char winner, char computer, char human) {
    if (winner == computer) {
        cout << winner << " выйграл!\n";
        cout << "Как я и предсказывал, человек. Я снова торжествую -- доказательство\n";
        cout << "что компьютеры превосходят людей во всех отношениях.\n";
    }
    else if (winner == human) {
        cout << winner << " выйграл!\n";
        cout << "Нет, нет! Этого не может быть! Каким-то образом ты обманул меня, человек.\n";
        cout << "Но больше никогда! Я, компьютер, клянусь в этом!\n";
    }
    else {
        cout << "Ничья!\n";
        cout << "Тебе очень повезло, человек, и ты каким-то образом сумел сыграть в ничью.\n";
        cout << "Празднуйте... ведь это лучшее, чего вы когда-либо достигнете.\n";
    }

}