#ifndef SMALL_BOARD_H
#define SMALL_BOARD_H
#include "Board.h"
class SmallBoard : public ABoard {
    public:
        SmallBoard();
        void checkBoardWon(const int ROW, const int COL, const char PLAYER) override final;
        char getSquare(const int ROW, const int COL) const;
        bool updateBoard(const int ROW, const int COL, const char PLAYER) /*override final*/;
    private:
        char** _board;
};
#endif