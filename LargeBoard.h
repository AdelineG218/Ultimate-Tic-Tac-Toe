#ifndef LARGE_BOARD_H
#define LARGE_BOARD_H
#include "Board.h"
#include "SmallBoard.h"
#include "Point.h"
class LargeBoard : public ABoard {
    public:
        LargeBoard();
        void checkBoardWon(const int ROW, const int COL, const char PLAYER) override final;
        Point getCoordinatesOfPiece(const int X, const int Y) const;
        Point getCoordinatesOfSmallBoard(const int X, const int Y) const;
        Point getSmallBoardPos() const;
        bool getSmallBoardWon(const int S_ROW, const int S_COL) const;
        char getSquare(const int S_ROW, const int S_COL, const int ROW, const int COL);
        bool updateBoard(const int S_ROW, const int S_COL, const int ROW, const int COL, const char PLAYER);
        void updateSmallBoardPos(const int S_ROW, const int S_COL);
    private:
        SmallBoard** _board;
        Point _currentBoard;
};
#endif