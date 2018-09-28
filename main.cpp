#include <iostream>
#include <string>
#include "AlphaBeta.h"


using namespace std;
// /*
int main()
{
    Board Game;
    AI computerPlayer;
    int opponent = X_VAL;
    int computer;
    if(opponent == X_VAL) computer = O_VAL;
    else computer = X_VAL;
    computerPlayer.initialize(computer);
    int currentPlayer = computer, x, y;
    while(Game.getNumberOfPieces() < 9)
    {
        bool changeTurn = true;
        if(currentPlayer == opponent)
        {
            cout << "Where do you want to place you piece?" << endl;
            cout << "Enter X: ";
            cin >> x;
            cout << "Enter Y: ";
            cin >> y;
            if(Game.getVal(x,y)!=0 || x > 2 || x < 0 || y >2 || y<0)
            {
                cout << endl<< "Please, enter valid place" << endl << endl;
                changeTurn = false;
            }
            else
            {
                Game.setVal(x, y, currentPlayer);
                Game.printBoard();
                if(Game.checkVictory()>0)
                {
                    cout << Game.getPlayer(currentPlayer) << " Won" << endl;
                    break;
                }
            }
        }
        else
        {
            computerPlayer.performMove(Game);
            Game.printBoard();
            if(Game.checkVictory()>0)
            {
                cout << Game.getPlayer(currentPlayer) << " Won" << endl;
                break;
            }
        }
        if(changeTurn)
        {
            if(currentPlayer == opponent) currentPlayer = computer;
            else currentPlayer = opponent;
        }
    }
    
    if(Game.checkVictory()<=0)
        cout << "Game Tied." << endl;
    return 0;
}
