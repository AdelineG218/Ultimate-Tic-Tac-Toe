#include "LargeBoard.h"
#include "Point.h"

#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main() {
    // setting up my output file named output.txt
    string fileName = "output.txt";
    ofstream fout(fileName); // opening the output file
    if (fout.fail()) { // making sure that my output file opened
        cerr << "Failed to open output file" << endl;
        return -2;
    }

    LargeBoard board = LargeBoard(); // this is the ultimate tic-tac-toe board
    int x, y; // used later to save user input
    bool first = true; // this is to check if it's the first iteration of the sfml while loop
    bool wonSeen = false; // this is to check if the user has seen the final results
    char player = 'O'; // this is the current player

    // setting up sfml variables
    RenderWindow window(VideoMode(900,900), "FP");
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

    // sfml while loop
    while (window.isOpen()) {
        window.clear(Color::White); // clears the window

        // // creating the lines for the tic-tic-toe board
        // for (int bigLineH = 0; bigLineH < 2; bigLineH++) { // drawing the large horizontal lines
        //     RectangleShape horizontal;
        //     horizontal.setSize(Vector2f(880, 10));
        //     horizontal.setFillColor(Color::Black);
        //     horizontal.setPosition(10, (bigLineH+1)*300-5);
        //     window.draw(horizontal);
        // }
        // for (int bigLineV = 0; bigLineV < 2; bigLineV++) { // drawing the large vertical lines
        //     RectangleShape vertical;
        //     vertical.setSize(Vector2f(10, 880));
        //     vertical.setFillColor(Color::Black);
        //     vertical.setPosition((bigLineV+1)*300-5, 10);
        //     window.draw(vertical);
        // }

        // for (int smallLineBi = 0; smallLineBi < 3; smallLineBi++) { // drawing the small lines
        //     for (int smallLineBj = 0; smallLineBj < 3; smallLineBj++) {
        //         RectangleShape h1; // small horizontal line 1
        //         h1.setSize(Vector2f(275, 6));
        //         h1.setFillColor(Color::Black);
        //         h1.setPosition(smallLineBi*300 + 10, (smallLineBj)*300 + 100-3);
        //         window.draw(h1);
        //         RectangleShape h2; // small horizontal line 2
        //         h2.setSize(Vector2f(275, 6));
        //         h2.setFillColor(Color::Black);
        //         h2.setPosition(smallLineBi*300 + 10, (smallLineBj)*300 + 200-3);
        //         window.draw(h2);

        //         RectangleShape v1; // small vertical line 1
        //         v1.setSize(Vector2f(6, 275));
        //         v1.setFillColor(Color::Black);
        //         v1.setPosition((smallLineBj)*300 + 100-3, smallLineBi*300 + 10);
        //         window.draw(v1);
        //         RectangleShape v2; // small vertical line 2
        //         v2.setSize(Vector2f(6, 275));
        //         v2.setFillColor(Color::Black);
        //         v2.setPosition((smallLineBj)*300 + 200-3, smallLineBi*300 + 10);
        //         window.draw(v2);
        //     }
        // }

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
                        currentSprite.setPosition(i*300 + k*100 - 10*(i-2), j*300 + l*100 - 10*(j-2));            
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

        window.display(); // displaying the window

        if (/*!first &&*/ !board.won()) { // if it's not the first iteration of the while loop and no one's won the game
            // print the current board state
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        for (int l = 0; l < 3; l++) {
                            fout << board.getSquare(k, i, l, j);
                        }
                        fout << " ";
                    }
                    fout << endl;
                }
                fout << endl;
            }
            fout << endl << endl;

            // cout << endl << "Player " << player << endl; // lets the users know whose turn it is
            // if there's not a specified small board that the player must play in, prompt the user to enter a small board
            // if (smallBoardPos.row < 0 || smallBoardPos.row > 2 || smallBoardPos.col < 0 || smallBoardPos.col > 2 || board.getSmallBoardWon(smallBoardPos.row, smallBoardPos.col)) {
            //     board.updateSmallBoardPos();
            // }

            // // getting the square that the user wants to play in and ensuring it's within the bounds
            // while (true) {
            //     cout << "Please enter the column and row (eg: 0 2)" << endl;
            //     cin >> x >> y;

            //     if(!cin.fail() && x > -1 && x < 3 && y > -1 && y < 3) {
            //         break;
            //     }

            //     cin.clear();
            //     char badChar = ' ';
            //     do { badChar = cin.get(); } while(badChar != '\n');
            //     cout << "Invalid move!" << endl << endl;
            // }

            // // if the move was successful, switch the player
            // if (board.updateBoard(x, y, player)) {
            //     if (player == 'O') {
            //         player = 'X';
            //     } else {
            //         player = 'O';
            //     }
            // }

        // } else if (first) { // this is just so that the user can see the initial, blank board first
        //     first = false;

        // } else if (board.won() && !wonSeen) { // if someone's won the game and the info hasn't been printed already
        //     // tell the user who won
        //     if (board.winner() == 'D') {
        //         cout << endl << "Tie!" << endl;
        //         fout << "Tie!" << endl << endl;
        //     } else {
        //         cout << endl << board.winner() << " won!" << endl;
        //         fout << board.winner() << " won!" << endl << endl;
        //     }

        //     // save the final board state to the output file
        //     for (int i = 0; i < 3; i++) {
        //         for (int j = 0; j < 3; j++) {
        //             for (int k = 0; k < 3; k++) {
        //                 for (int l = 0; l < 3; l++) {
        //                     fout << board.getSquare(k, i, l, j);
        //                 }
        //                 fout << " ";
        //             }
        //             fout << endl;
        //         }
        //         fout << endl;
        //     }

            // cout << "Check the output file for the replay and results!" << endl;
            // wonSeen = true; // ensures that the info won't be printed again
        }
        
        // allows the window to close via clicking the x, pressing Escape, or pressing Q
        while( window.pollEvent(event) ) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::MouseButtonPressed: // adding a game piece when the mouse is clicked
                    {
                        Point mouseCoord{Mouse::getPosition(window).x, Mouse::getPosition(window).y};
                        Point SBCoord = board.getCoordinatesOfSmallBoard(mouseCoord.row, mouseCoord.col);
                        Point pieceCoord = board.getCoordinatesOfPiece(mouseCoord.row, mouseCoord.col, SBCoord.row, SBCoord.col);
                        if (!board.won() && board.updateBoard(SBCoord.row, SBCoord.col, pieceCoord.row, pieceCoord.col, player)) {
                            if (player == 'O') {
                                player = 'X';
                            } else {
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
    fout.close(); // closing the output stream
    return 0;
}