#include <iostream>
#include <stdlib.h>

using namespace std;

const int NO_VAL = 0;
const int TIE_VAL = -1;
const int X_VAL = 1;
const int O_VAL = 2;
const int SIZE = 3;
const int HASH_SIZE = 17;

class Board{
public:
    Board();                               //Initializes board to empty state
    int getNumberOfPieces();              //Returns number of places currently occupied
    char getPlayer(int player);
    int getVal(int x, int y);             //Shows which player is in box (x,y) in current state
    void setVal(int x, int y, int player);  //Places a piece of current player in box(x,y)
    int setValAndCheck(int x, int y, int player);  //Returns if someone wins while making particular move
    int checkVictory();                   //Check whether any of 2 players has won or not. If yes, returns winner.
    int checkTie();                      //Check if the game is tied
    void printBoard();                    //Print current board state to screen
    int Hash[HASH_SIZE];
private:
    int boardState[SIZE][SIZE];          //Array to represent current board state
    int numberOfPieces;                  //Tracks number of pieces in a board at current
    
};


Board::Board()
{
    for(int x=0; x < SIZE; x++)
    {
        for(int y = 0; y<SIZE; y++)
        {
            boardState[x][y] = NO_VAL;       //initially all the boxes are empty.
        }
    }
    // Initiallizing Hash
    for(int i = 0; i< HASH_SIZE; i++)
    {
        Hash[i] = 0;
    }
    numberOfPieces = 0;
}

int Board::getVal(int x, int y)
{
    return boardState[x][y];
}

int Board::getNumberOfPieces()
{
    return numberOfPieces;
}

char Board::getPlayer(int player)
{
    if(player == X_VAL) return 'X';
    else if(player == O_VAL) return 'O';
    else return ' ';
}

void Board::setVal(int x, int y, int player)
{
    if(player!=0 && boardState[x][y]==0)                       //to avoid counter from increasing for setVal(x, y, 0) && to avoid counter from increasing when a piece is replaced.
        numberOfPieces += 1;
    if(player == 0 && boardState[x][y]!=0)             //if a piece is removed
        numberOfPieces -=1;
    
    int prevPlayer = boardState[x][y];                             //player in x,y before setting value
    if(prevPlayer!=0)
    {
        //decreasing values in hash when one piece is replaced
        Hash[(prevPlayer-1)*8+x] -= 1;
        Hash[(prevPlayer-1)*8+y+3] -= 1;
        if(x == y)
        {
            Hash[(prevPlayer-1)*8+6] -= 1;
        }
        if(x + y == 2)
        {
            Hash[(prevPlayer-1)*8+7] -= 1;
        }
        // Updating Hash[16]
        if(Hash[(prevPlayer-1)*8+x] == 2)       //Horizontal checking
        {
            if(Hash[16] == prevPlayer)
            {
                Hash[16] = 0;
            }
        }
        if(Hash[(prevPlayer-1)*8+3+y]==2)
        {
            if(Hash[16] == prevPlayer)
            {
                Hash[16] = 0;
            }
        }
        if(x == y && Hash[(prevPlayer-1)*8+6]==2)
        {
            if(Hash[16] == prevPlayer)
            {
                Hash[16] = 0;
            }
        }
        if(x + y == 2 && Hash[(prevPlayer-1)*8+7]==3)
        {
            if(Hash[16] == prevPlayer)
            {
                Hash[16] = 0;
            }
        }
    }
    boardState[x][y] = player;
    //Updating Hash when placing a new piece
    if(player != 0)
    {
        Hash[(player-1)*8+x] += 1;
        Hash[(player-1)*8+y+3] += 1;
        if(x == y)
        {
            Hash[(player-1)*8+6] += 1;
        }
        if(x + y == 2)
        {
            Hash[(player-1)*8+7] += 1;
        }
    }
    
    // changing value of numberOfPieces.
    if(player!=0 && boardState[x][y]==0)                       //to avoid counter from increasing for setVal(x, y, 0) && to avoid counter from increasing when a piece is replaced.
        numberOfPieces += 1;
    if(player == 0 && boardState[x][y]!=0)             //if a piece is removed
        numberOfPieces -=1;
    boardState[x][y] = player;
    
    
    //updating for victory variable
    if(player !=0)
    {
        if(Hash[(player-1)*8+x] == 3)       //Horizontal checking
        {
            if(Hash[16] == 0)
            {
                Hash[16] = player;
            }
        }
        if(Hash[(player-1)*8+3+y]==3)
        {
            if(Hash[16] == 0)
            {
                Hash[16] = player;
            }
        }
        if(x == y && Hash[(player-1)*8+6]==3)
        {
            if(Hash[16] == 0)
            {
                Hash[16] = player;
            }
        }
        if(x + y == 2 && Hash[(player-1)*8+7]==3)
        {
            if(Hash[16] == 0)
            {
                Hash[16] = player;
            }
        }
        //tie case
        if(numberOfPieces == 9)
        {
            if(Hash[16] == 0)
            {
                Hash[16] = -1;
            }
        }
    }
    else
        Hash[16] = 0;
}

int Board::setValAndCheck(int x, int y, int player)
{
    int prevPlayer = boardState[x][y];                             //player in x,y before setting value
    if(prevPlayer!=0)
    {
        //decreasing values in hash when one piece is replaced
        Hash[(prevPlayer-1)*8+x] -= 1;
        Hash[(prevPlayer-1)*8+y+3] -= 1;
        if(x == y)
        {
            Hash[(prevPlayer-1)*8+6] -= 1;
        }
        if(x + y == 2)
        {
            Hash[(prevPlayer-1)*8+7] -= 1;
        }
        // Updating Hash[16]
        if(Hash[(prevPlayer-1)*8+x] == 2)       //Horizontal checking
        {
            if(Hash[16] == prevPlayer)
            {
                Hash[16] = 0;
            }
        }
        if(Hash[(prevPlayer-1)*8+3+y]==2)
        {
            if(Hash[16] == prevPlayer)
            {
                Hash[16] = 0;
            }
        }
        if(x == y && Hash[(prevPlayer-1)*8+6]==2)
        {
            if(Hash[16] == prevPlayer)
            {
                Hash[16] = 0;
            }
        }
        if(x + y == 2 && Hash[(prevPlayer-1)*8+7]==3)
        {
            if(Hash[16] == prevPlayer)
            {
                Hash[16] = 0;
            }
        }
    }
    boardState[x][y] = player;
    //Updating Hash when placing a new piece
    if(player != 0)
    {
        Hash[(player-1)*8+x] += 1;
        Hash[(player-1)*8+y+3] += 1;
        if(x == y)
        {
            Hash[(player-1)*8+6] += 1;
        }
        if(x + y == 2)
        {
            Hash[(player-1)*8+7] += 1;
        }
    }
    
    // changing value of numberOfPieces.
    if(player!=0 && boardState[x][y]==0)                       //to avoid counter from increasing for setVal(x, y, 0) && to avoid counter from increasing when a piece is replaced.
        numberOfPieces += 1;
    if(player == 0 && boardState[x][y]!=0)             //if a piece is removed
        numberOfPieces -=1;
    boardState[x][y] = player;
    
    
    //Checking for victory
    if(player !=0)
    {
        if(Hash[(player-1)*8+x] == 3)       //Horizontal checking
        {
            if(Hash[16] == 0)
            {
                Hash[16] = player;
            }
            return Hash[16];
        }
        if(Hash[(player-1)*8+3+y]==3)
        {
            if(Hash[16] == 0)
            {
                Hash[16] = player;
            }
            return Hash[16];
        }
        if(x == y && Hash[(player-1)*8+6]==3)
        {
            if(Hash[16] == 0)
            {
                Hash[16] = player;
            }
            return Hash[16];
        }
        if(x + y == 2 && Hash[(player-1)*8+7]==3)
        {
            if(Hash[16] == 0)
            {
                Hash[16] = player;
            }
            return Hash[16];
        }
        //tie case
        if(numberOfPieces == 9)
        {
            if(Hash[16] == 0)
            {
                Hash[16] = -1;
            }
            return Hash[16];
        }
        return Hash[16];
    }
    Hash[16] = 0;
    return Hash[16];
    
}

int Board::checkVictory()
{
    /*
     for(int i = 0; i <HASH_SIZE; i++)
     {
     if(Hash[i] == 3)
     {
     return ((int)i/8)+1;
     }
     }
     if(numberOfPieces == 9)             //If the board is full and no player has won return tie value
     {
     return -1;
     }
     return 0;*/
    
    return Hash[16];
    
}

int Board::checkTie()
{
    if(numberOfPieces==9 && checkVictory()==0)
        return 1;
    return 0;
    
}

void Board::printBoard()
{
    system("cls");
    cout << "\n\n\tTic Tac Toe\n\n";
    cout << endl;
    
    cout << "     |     |     " << endl;
    cout << "  " << getPlayer(boardState[0][0]) << "  |  " << getPlayer(boardState[0][1]) << "  |  " <<getPlayer(boardState[0][2]) << endl;
    
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    
    cout << "  " << getPlayer(boardState[1][0]) << "  |  " << getPlayer(boardState[1][1]) << "  |  " <<getPlayer(boardState[1][2]) << endl;
    
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    
    cout << "  " << getPlayer(boardState[2][0]) << "  |  " << getPlayer(boardState[2][1]) << "  |  " << getPlayer(boardState[2][2]) << endl;
    
    cout << "     |     |     " << endl << endl;
}








