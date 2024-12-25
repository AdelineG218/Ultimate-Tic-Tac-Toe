#ifndef ABOARD_H
#define ABOARD_H
class ABoard {
    public:
        ABoard();
        virtual ~ABoard();
        bool won() const;
        char winner() const;
        virtual void checkBoardWon(const int ROW, const int COL, const char PLAYER) = 0;
        virtual bool updateBoard(const int ROW, const int COL, const char PLAYER) = 0;
    protected:
        char mWinPlayer;
        int mNumSpacesLeft;
};
#endif