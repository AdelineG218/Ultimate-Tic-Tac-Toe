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
    } else {
        int SBWon = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (_board[i][j].won()) SBWon++;
            }
        }
        if (SBWon == 9) mWinPlayer = 'D';
    }
}

void LargeBoard::updateSmallBoardPos(const int S_ROW, const int S_COL) {
    _currentBoard.row = S_ROW;
    _currentBoard.col = S_COL;
    return;
}

bool LargeBoard::updateBoard(const int S_ROW, const int S_COL, const int ROW, const int COL, const char PLAYER) {
    if ((_currentBoard.row == -1 || _board[_currentBoard.row][_currentBoard.col].won()) && !_board[S_ROW][S_COL].won()) {
        updateSmallBoardPos(S_ROW, S_COL);
    } else if (!_board[_currentBoard.row][_currentBoard.col].won() && (S_ROW != _currentBoard.row || S_COL != _currentBoard.col)) {
        cout << "Invalid move!" << endl;
        return false;
    } else if (_board[_currentBoard.row][_currentBoard.col].won() && _board[S_ROW][S_COL].won()) {
        _currentBoard.row = -1;
        _currentBoard.col = -1;
        cout << "Invalid move!" << endl;
        return false;
    }
    
    if (_board[_currentBoard.row][_currentBoard.col].updateBoard(ROW, COL, PLAYER)) {
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

Point LargeBoard::getCoordinatesOfPiece(const int X, const int Y, const int S_ROW, const int S_COL) const {
    Point coord = Point();
    int x = X-300*S_ROW;
    int y = Y-300*S_COL;

    if (x < 100) {
        coord.row = 0;
    } else if (x < 200) {
        coord.row = 1;
    } else {
        coord.row = 2;
    }

    if (y < 100) {
        coord.col = 0;
    } else if (y < 200) {
        coord.col = 1;
    } else {
        coord.col = 2;
    }
    return coord;
}

Point LargeBoard::getCoordinatesOfSmallBoard(const int X, const int Y) const {
    Point coord = Point();
    if (X < 300) {
        coord.row = 0;
    } else if (X < 600) {
        coord.row = 1;
    } else {
        coord.row = 2;
    }

    if (Y < 300) {
        coord.col = 0;
    } else if (Y < 600) {
        coord.col = 1;
    } else {
        coord.col = 2;
    }
    return coord;
}