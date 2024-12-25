#include "Board.h"

ABoard::ABoard() {
    mWinPlayer = '-';
    mNumSpacesLeft = 0;
}

ABoard::~ABoard() { }

bool ABoard::won() const {
    if (mWinPlayer != '-') { // '-' means that the winner hasn't been determined yet
        return true;
    } else {
        return false;
    }
}

char ABoard::winner() const {
    return mWinPlayer; // return the winning player
}