#include "LargeBoard.h"
#include "Point.h"

#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main() {
    LargeBoard board = LargeBoard(); // this is the ultimate tic-tac-toe board
    bool first = true; // this is to check if it's the first iteration of the sfml while loop
    char player = 'O'; // this is the current player

    // setting up sfml variables
    RenderWindow window(VideoMode(900,900), "Ultimate Tic-Tac-Toe");
    Event event;
    
    // importing and validating the textures for the sfml game piece sprites
    Texture xTexture;
    if (!xTexture.loadFromFile("data/Butter.png")) {
        cerr << "Could not load image" << endl;
        return -2;
    }
    Texture oTexture;
    if (!oTexture.loadFromFile("data/Blueberry.png")) {
        cerr << "Could not load image" << endl;
        return -2;
    }
    Texture xWinTexture;
    if (!xWinTexture.loadFromFile("data/Butter-win.png")) {
        cerr << "Could not load image" << endl;
        return -2;
    }
    Texture oWinTexture;
    if (!oWinTexture.loadFromFile("data/Blueberry-win.png")) {
        cerr << "Could not load image" << endl;
        return -2;
    }
    Texture boardTexture;
    if (!boardTexture.loadFromFile("data/Waffle.png")) {
        cerr << "Could not load image" << endl;
        return -2;
    }
    Texture startTexture;
    if (!startTexture.loadFromFile("data/Start.png")) {
        cerr << "Could not load image" << endl;
        return -2;
    }
    Texture endXWinTexture;
    if (!endXWinTexture.loadFromFile("data/End-butter-win.png")) {
        cerr << "Could not load image" << endl;
        return -2;
    }
    Texture endOWinTexture;
    if (!endOWinTexture.loadFromFile("data/End-blueberry-win.png")) {
        cerr << "Could not load image" << endl;
        return -2;
    }
    Texture endTieTexture;
    if (!endTieTexture.loadFromFile("data/End-tie.png")) {
        cerr << "Could not load image" << endl;
        return -2;
    } else {
        cout << "Tie Loaded" << endl;
    }

    // sfml while loop
    while (window.isOpen()) {
        window.clear(Color::White); // clears the window

        // drawing the board
        Sprite boardSprite;
        boardSprite.setTexture(boardTexture);
        boardSprite.setPosition(0,0);
        boardSprite.setScale(0.5, 0.5);
        window.draw(boardSprite);

        // drawing the game pieces (x's and o's)
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    for (int l = 0; l < 3; l++) {
                        char current = board.getSquare(i, j, k, l); // the current square we're analyzing
                        Sprite currentSprite;

                        // determines the sprite type by the character in the square
                        // capital letters correspond to the normal game pieces
                        // lowercase letters correspond to the game pieces that won a small board
                        if (current == 'O') {
                            currentSprite.setTexture(oTexture);
                        } else if (current == 'X') {
                            currentSprite.setTexture(xTexture);
                        } else if (current == 'o') {
                            currentSprite.setTexture(oWinTexture);
                        } else if (current == 'x') {
                            currentSprite.setTexture(xWinTexture);
                        }
                        
                        currentSprite.setScale(0.5,0.5); // downsizing the scale of each texture to 1/10
                        currentSprite.setPosition(i*300 + k*100 - 10*(i-2) - 5*(k-1), j*300 + l*100 - 10*(j-2) - 5*(l-1));            
                        window.draw(currentSprite);
                    }
                }
            }
        }

        Point smallBoardPos = board.getSmallBoardPos(); // this finds what small board the player must play in
        // if the small board position is valid, then draw a green box around the appropriate small board
        if (!board.won() && (smallBoardPos.row > -1 || smallBoardPos.row < 3 || smallBoardPos.col > -1 || smallBoardPos.col < 3 || !board.getSmallBoardWon(smallBoardPos.row, smallBoardPos.col))) {
            RectangleShape currentSmallBoard;
            currentSmallBoard.setSize(Vector2f(280, 280));
            currentSmallBoard.setOutlineColor(Color(101, 41, 8));
            currentSmallBoard.setOutlineThickness(8);
            currentSmallBoard.setFillColor(Color(0, 0, 0, 0));
            currentSmallBoard.setPosition(smallBoardPos.row*300 - 10*(smallBoardPos.row-2), smallBoardPos.col*300 - 10*(smallBoardPos.col-2));
            window.draw(currentSmallBoard);
        }

        if (first) {
            Sprite startScreen;
            startScreen.setTexture(startTexture);
            window.draw(startScreen);
        } else if (board.won()) {
            RectangleShape endBackground;
            endBackground.setSize(Vector2f(900, 900));
            endBackground.setFillColor(Color(0, 0, 0, 127.5));
            window.draw(endBackground);

            Sprite endScreen;
            if (board.winner() == 'D') {
                endScreen.setTexture(endTieTexture);
            } else if (board.winner() == 'X') {
                endScreen.setTexture(endXWinTexture);
            } else {
                endScreen.setTexture(endOWinTexture);
            }
            endScreen.setPosition(150, 300);
            window.draw(endScreen);
        }

        window.display(); // displaying the window
        
        // allows the window to close via clicking the x, pressing Escape, or pressing Q
        while( window.pollEvent(event) ) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::MouseButtonPressed: // adding a game piece when the mouse is clicked
                    {
                        Point mouseCoord{Mouse::getPosition(window).x, Mouse::getPosition(window).y};
                        if (!first && !board.won()) {
                            Point SBCoord = board.getCoordinatesOfSmallBoard(mouseCoord.row, mouseCoord.col);
                            Point pieceCoord = board.getCoordinatesOfPiece(mouseCoord.row, mouseCoord.col, SBCoord.row, SBCoord.col);
                            if (!board.won() && board.updateBoard(SBCoord.row, SBCoord.col, pieceCoord.row, pieceCoord.col, player)) {
                                if (player == 'O') {
                                    player = 'X';
                                    cout << endl << "Player 2's Turn (Butter)" << endl;
                                } else {
                                    player = 'O';
                                    cout << endl << "Player 1's Turn (Blueberry)" << endl;
                                }
                            }
                        } else if (first) {
                            if (mouseCoord.row >= 375 && mouseCoord.row <= 525 && mouseCoord.col >= 475 && mouseCoord.col <= 525) {
                                first = false;
                                cout << "Player 1's Turn (Blueberry)" << endl;
                            }
                        } else if (board.won()) {
                            if (mouseCoord.row >= 362 && mouseCoord.row <= 538 && mouseCoord.col >= 489 && mouseCoord.col <= 564) {
                                board = LargeBoard();
                                player = 'O';
                            }
                        }
                    }
                    break;
                case Event::KeyPressed:
                    if (event.key.code == Keyboard::Escape || event.key.code == Keyboard::Q) {
                        window.close();
                    }
                    break;
                default:
                    break;
            }
        }
    }

    return 0;
}