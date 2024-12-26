#include "LargeBoard.h"
#include "SmallBoard.h"
#include "Point.h"
#include <iostream>
using namespace std;

LargeBoard::LargeBoard() {
    mWinPlayer = '-';
    _currentBoard = {-1, -1};
    _board = new SmallBoard*[3];
    for (int i = 0; i < 3; i++) {
        _board[i] = new SmallBoard[3];
        for (int j = 0; j < 3; j++) {
            _board[i][j] = SmallBoard();
        }
    }
    mNumSpacesLeft = 81;
}

void LargeBoard::checkBoardWon(const int ROW, const int COL, const char PLAYER) {
    if (_board[ROW][0].winner() == PLAYER && _board[ROW][1].winner() == PLAYER && _board[ROW][2].winner() == PLAYER) {
        mWinPlayer = PLAYER;

    } else if (_board[0][COL].winner() == PLAYER && _board[1][COL].winner() == PLAYER && _board[2][COL].winner() == PLAYER) {
        mWinPlayer = PLAYER;
    } else if (_board[1][1].winner() == PLAYER) {
        if (_board[0][0].winner() == PLAYER && _board[2][2].winner() == PLAYER) {
            mWinPlayer = PLAYER;
        } else if (_board[0][2].winner() == PLAYER && _board[2][0].winner() == PLAYER) {
            mWinPlayer = PLAYER;
        }
    }
}

void LargeBoard::updateSmallBoardPos() {
    while (true) {
        cout << "Please enter the column and row of a small board with a space between (eg: 0 2)" << endl;
        cin >> _currentBoard.row >>  _currentBoard.col;

        if(!cin.fail() && !(_currentBoard.row < 0 || _currentBoard.row > 2 || _currentBoard.col < 0 || _currentBoard.col > 2 || _board[_currentBoard.row][_currentBoard.col].won())) {
            break;
        }

        cin.clear();
        char badChar = ' ';
        do { badChar = cin.get(); } while(badChar != '\n');
        cout << "Invalid choice! Choose a different board." << endl << endl;
    }
    return;
}

bool LargeBoard::updateBoard(const int ROW, const int COL, const char PLAYER) {
    if (ROW > 2 || ROW < 0 || COL > 2 || COL < 0 || !(PLAYER == 'O' || PLAYER == 'X')) {
        cout << "Invalid move!" << endl << endl;
        return false;
    } 

    if (_currentBoard.row == -1 || _board[_currentBoard.row][_currentBoard.col].won()) {
        updateSmallBoardPos();
    }
    
    if (_board[_currentBoard.row][_currentBoard.col].updateBoard(ROW, COL, PLAYER)) {
        cout << "Updated board in LB updateBoard" << endl;
        mNumSpacesLeft--;
        checkBoardWon(_currentBoard.row, _currentBoard.col, PLAYER);
        if (_board[ROW][COL].won()) {
            _currentBoard.row = -1;
            _currentBoard.col = -1;
        } else {
            _currentBoard.row = ROW;
            _currentBoard.col = COL;
        }
        if (mNumSpacesLeft == 0) {
            mWinPlayer = 'D';
        }
        return true;
    } else {
        return false;
    }
}

char LargeBoard::getSquare(const int S_ROW, const int S_COL, const int ROW, const int COL) {
    return _board[S_ROW][S_COL].getSquare(ROW, COL);
}

Point LargeBoard::getSmallBoardPos() const {
    return _currentBoard;
}

bool LargeBoard::getSmallBoardWon(const int S_ROW, const int S_COL) const {
    return _board[S_ROW][S_COL].won();
}