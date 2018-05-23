//
// Created by amir on 07/11/17.
//

#include <iostream>

#include "../include/Board.h"
#include "../include/ConsolePrinter.h"

using namespace std;

void ConsolePrinter::printBoard(Board * board) const{
    const int size = board->getSize();
    cout << "  ";
    for(int i = 1;i <= size;i++) {
        cout << "| " << i << " ";
    }
    cout << "|" << endl;

    cout << string(size*4 + 3, '-') << endl;

    for(int x = 0;x < size;x++) {
        int row = x + 1;
        cout << row;
        for(int y = 0;y < size;y++) {
            cout << " | " << (char)board->getValue(x, y);
        }
        cout << " |" << endl;
        //Prints the line below
        cout << string(size*4 + 3, '-') << endl;
    }
}

void ConsolePrinter::cantMove() const {
    cout << "No possible moves. Play passes back to the other player. "
            "Press any key and enter to continue" << endl;
}
void ConsolePrinter::massage(const string &s) const {
    cout << s;
}
void ConsolePrinter::noMoreMoves() const {
    cout << "Neither players can move!!!" << endl;
}
void ConsolePrinter::yourTurn(const Value &token) const {
    cout << endl;
    cout << (char)token << ": It's your move" << endl;
}
void ConsolePrinter::availableMoves(set<Coordinate> legalMoves) const {
    cout << "Your possible moves:" << endl;

    std::set<Coordinate>::iterator it;
    for (it=legalMoves.begin(); it!=legalMoves.end();) {
        cout << "(" << (*it).getRow() + 1 << "," << (*it).getCol() + 1 << ")";
        // put ','
        if ((++it) != legalMoves.end()) {
            cout << ",";
        }
    }
      //  std::cout << ' ' << *it;
    std::cout << '\n';

}
//a

void ConsolePrinter::winner(const Value &p1, const Value &p2, const int &score1,
                            const int &score2) const{
    cout << "Score: " << endl;
    cout << (char)p1 << ": " << score1 << ", " << (char)p2 << ": " << score2 << endl;
    if (score1 == score2) {
        cout << "Tie!" << endl;
    } else {
        if (score1 > score2) {
            cout << "The winner is: " << (char)p1 << endl;
        } else {
            cout << "The winner is: " << (char)p2 << endl;
        }
    }
}
void ConsolePrinter::playingMove(Value sign, Coordinate c) {
    if(c.getRow() >= 0) {
        cout << (char)sign << " Played: (" << c.getRow() + 1
             << "," << c.getCol() + 1 << ")\n" << endl;
    } else {
        if (c.getRow() == -2) {
            cout << (char)sign << " wasn't able to move\n";
        }
    }
}

bool ConsolePrinter::getInput(int &a) {
    cin >> a;
    //cin.clear(); // clears error flags
    cin.ignore(10, '\n');
    if (!cin) {
        cin.clear(); // clears error flags
        cin.ignore(9999, '\n');
        return false;
    }
    return true;
}
void ConsolePrinter::getInput(string &str) {
//    cin >> str;
    getline(cin, str);
}

string ConsolePrinter::scanString(int i) {
    string str;
    if (i) {
      cin.ignore();
    }
    getline(cin, str);
    return str;

}