#include "SmallBoard.h"
#include <iostream>
using namespace std;

SmallBoard::SmallBoard() {
    mWinPlayer = '-';
    _board = new char*[3];
    for (int i = 0; i < 3; i++) {
        _board[i] = new char[3];
        for (int j = 0; j < 3; j++) {
            _board[i][j] = '-';
        }
    }
    mNumSpacesLeft = 9;
}

void SmallBoard::checkBoardWon(const int ROW, const int COL, const char PLAYER) {
    if (!won()) {
        if (_board[ROW][0] == PLAYER && _board[ROW][1] == PLAYER && _board[ROW][2] == PLAYER) {
            mWinPlayer = PLAYER;
            _board[ROW][0] = tolower(PLAYER);
            _board[ROW][1] = tolower(PLAYER);
            _board[ROW][2] = tolower(PLAYER);
        } else if (_board[0][COL] == PLAYER && _board[1][COL] == PLAYER && _board[2][COL] == PLAYER) {
            mWinPlayer = PLAYER;
            _board[0][COL] = tolower(PLAYER);
            _board[1][COL] = tolower(PLAYER);
            _board[2][COL] = tolower(PLAYER);
        } else if (_board[1][1] == PLAYER) {
            if (_board[0][0] == PLAYER && _board[2][2] == PLAYER) {
                mWinPlayer = PLAYER;
                _board[1][1] = tolower(PLAYER);
                _board[0][0] = tolower(PLAYER);
                _board[2][2] = tolower(PLAYER);
            } else if (_board[0][2] == PLAYER && _board[2][0] == PLAYER) {
                mWinPlayer = PLAYER;
                _board[1][1] = tolower(PLAYER);
                _board[0][2] = tolower(PLAYER);
                _board[2][0] = tolower(PLAYER);
            }
        }
    }
}

bool SmallBoard::updateBoard(const int ROW, const int COL, const char PLAYER) {
    if (ROW > 2 || ROW < 0 || COL > 2 || COL < 0 || !(PLAYER == 'O' || PLAYER == 'X')) {
        cout << "Invalid move!" << endl;
        return false;
    } else if (_board[ROW][COL] != '-') {
        cout << "Invalid move!" << endl;
        return false;
    }

    _board[ROW][COL] = PLAYER;
    mNumSpacesLeft--;
    checkBoardWon(ROW, COL, PLAYER);
    if (mNumSpacesLeft == 0 && !won()) {
        mWinPlayer = 'D';
    }

    return true;
}

char SmallBoard::getSquare(const int ROW, const int COL) const {
    return _board[ROW][COL];
}