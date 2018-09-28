#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Board.h"
using namespace std;

const int INFINITY = 11;

struct AIMove
{
    AIMove();
    AIMove(int);
    int x, y, score;
};
AIMove::AIMove(){};

AIMove::AIMove(int Score)
{
    score = Score;
}

class AI
{
public:
    void initialize(int player); // initialiazes AI player;
    void performMove(Board& aBoard); // Preforms best possible move
    AIMove getBestMove(Board& aBoard, int player, int alpha, int beta);         //returns best possible move in current state
private:
    int aiPlayer;      //index of AI player
    int humanPlayer;   //index of human player
    //AIMove getBestMove(Board& aBoard, int player);         //returns best possible move in current state
};

void AI::initialize(int player)
{
    aiPlayer = player;
    if(player == X_VAL)  humanPlayer = O_VAL;
    else humanPlayer = X_VAL;
}

void AI::performMove(Board& aBoard)
{
    AIMove bestMove = getBestMove(aBoard, aiPlayer,-INFINITY, INFINITY);
    aBoard.setVal(bestMove.x, bestMove.y, aiPlayer);
}

AIMove AI::getBestMove(Board& aBoard, int player, int alpha, int beta)
{
    int winner = aBoard.checkVictory();
    if(winner != 0)                                      //if the state is an end state
    {
        int winner = aBoard.checkVictory(); //
        if(winner==aiPlayer)                //
            return AIMove(10);                //
        else if (winner == humanPlayer)     //------------If the state is an end state assign score to that state(move)
            return AIMove(-10);               //
        else if (winner == -1)              //
            return AIMove(0);                 //
        
        /*
         int endScore;
         if(winner==aiPlayer)                               //aiPlayer can win only in aiPlayer's turn, so we are assured that its aiPlayer's turn, hence update beta of parent move.
         {
         endScore = 10;
         if(endScore < beta)   currentBeta = endScore;
         }
         else if (winner == humanPlayer)
         {
         if(endScore > alpha)   currentAlpha = endScore;
         endScore = -10;
         }
         else if (winner == -1)
         {
         endScore = 0;
         if(player == aiPlayer)
         {
         if(endScore < beta)   currentBeta = endScore;
         }
         else if(player == humanPlayer)
         {
         if(endScore > alpha)   currentAlpha = endScore;
         }
         }
         return AIMove(endScore);*/
    }
    
    //if the state is not an end
    if(player == aiPlayer)
    {
        AIMove bestMove(-INFINITY);
        int currentAlpha = alpha;
        int currentBeta = beta;
        for(int x=0; x<SIZE; x++)                                           //
        {                                                                   //---------choose an original move
            for(int y=0; y<SIZE; y++)                                         //
            {
                if(aBoard.getVal(x,y)==NO_VAL) //the box is empty               //
                {                                                               //
                    AIMove aMove;                                                 //
                    aMove.x = x;                                                  //
                    aMove.y = y;                                                  //
                    aBoard.setVal(x, y, player);
                    aMove.score = getBestMove(aBoard, humanPlayer, currentAlpha, currentBeta).score;         //
                    if(aMove.score > currentAlpha)
                    {
                        currentAlpha = aMove.score;
                    }
                    if(aMove.score > bestMove.score)
                        bestMove = aMove;
                    aBoard.setVal(x, y, NO_VAL);
                    if(currentAlpha >= currentBeta)
                    {
                        return AIMove(currentBeta);
                    }
                }
            }
        }
        return bestMove;
    }
    
    if(player == humanPlayer)
    {
        AIMove bestMove(INFINITY);
        int currentAlpha = alpha;
        int currentBeta = beta;
        for(int x=0; x<SIZE; x++)                                           //
        {                                                                   //---------choose an original move
            for(int y=0; y<SIZE; y++)                                         //
            {
                if(aBoard.getVal(x,y)==NO_VAL) //the box is empty               //
                {                                                               //
                    AIMove aMove;                                                 //
                    aMove.x = x;                                                  //
                    aMove.y = y;                                                  //
                    aBoard.setVal(x, y, player);
                    aMove.score = getBestMove(aBoard, aiPlayer, currentAlpha, currentBeta).score;         //
                    if(aMove.score < currentBeta)
                    {
                        currentBeta = aMove.score;
                    }
                    if(aMove.score < bestMove.score)
                        bestMove = aMove;
                    aBoard.setVal(x, y, NO_VAL);
                    if(currentAlpha >= currentBeta)
                    {
                        return AIMove(currentAlpha);
                    }
                }
            }
        }
        return bestMove;
    }
}


