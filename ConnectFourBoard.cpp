#include <iostream>
#include <ctime>
#include <cstdlib>

#include "ConnectFourBoard.h"
using namespace std;

/* a constructor that initializes all
   the member variables of this class
   creates a 2-d array dynamically for
   connect-four board using new operator
   then initializes all the cells to empty
   character
   creates dynamically a structure variable
   of type Move  and assigns its members
   row_inde and col_index to -1
   sets the player char variable to 'n'
*/
tic::tic(){

    row_size = 6;
    col_size = 7;

    board = new char* [row_size];
    for(int i=0;i<row_size;i++)
        board[i] = new char [col_size];

    for(int i=0;i<row_size;i++){
        for(int j=0;j<col_size;j++)
            board[i][j]=' ';
    }

    moves = new Move[7];
    for(int i=0;i<7;i++){
        moves[i].col_index = -1;
        moves[i].row_index = -1;
    }

    player = 'n';
}

/*a boolean function that returns false if the
  board is not empty else returns true
*/
bool tic::isBoardEmpty(){

    for(int i=0;i<row_size;i++){
        for(int j=0;j<col_size;j++){
            if(board[i][j]!=' ')
                return false;
        }
    }
    return true;
}

/* this function is used to
   make the first move by randomly
   choosing a column
*/
int tic::makeFirstMove(){

    int random_col;
    srand(time(NULL));
    random_col = rand()%7+1;
    if(random_col == 7)
        random_col=4;
    return random_col;
}

/*this is used to check all the possible moves
  that can be made by the player 1st case considered is
  checking for whether there are empty cells
  in 0th row,if present then stores that col location
  to col_index of the move's structure member variable
  2nd case considered is checking for all other empty cells
  and if empty, checking whether the below cell is empty
  or not if empty then not storing this location else storing this location
  in col_index and row_index of the structure move
*/
void tic::checkPossibleMoves(){

    int c=0;

    //checking whether empty place is there for the 0th row
    for(int col=0;col<col_size;col++){
        if(board[0][col]==' '){
            this->moves[c].row_index = 0;
            this->moves[c].col_index = col;
            c++;
        }
    }

    //checking for all other rows for empty places
    for(int row=1;row<row_size;row++){
        for(int col=0;col<col_size;col++){
            if(board[row][col]==' '){
                if(board[row-1][col]!=' '){
                    (moves+c)->col_index=col;
                    (moves+c)->row_index=row;
                     c++;
                }
            }
        }
    }
}

/* this is a boolean function that return true
   if a player has won else return false
   it considers 4 cases
     1st for continuous 4 in a row
     2nd for continuous 4 in vertical
     3rd for right diagonal win
     4th for left diagonal win
*/
bool tic::checkPlayerWon(){

    bool win=false;
    char c1,c2,c3,c4;

    //for checking row wins
    for(int r=0;r<row_size;r++){
        for(int c=0;c<4;c++){
            if(!win){
                c1 = board[r][c];
                c2 = board[r][c+1];
                c3 = board[r][c+2];
                c4 = board[r][c+3];
                //checking for board[r][c]==board[r][c+1]==board[r][c+2]==board[r][c+3]
                if(c1!=' '||c2!=' '||c3!=' '||c4!=' '){
                    if((c1 == c2)&& (c2 == c3) && (c3 == c4)){
                        win = true;
                        break;
                    }
                }
            }
        }
    }

    //for checking col wins
    if(!win){
        for(int r=0;r<3;r++){
            for(int c=0;c<col_size;c++){
                c1 = board[r][c];
                c2 = board[r+1][c];
                c3 = board[r+2][c];
                c4 = board[r+3][c];
                //checking for board[r][c]==board[r+1][c]==board[r+2][c]==board[r+3][c]
                if(c1!=' '||c2!=' '||c3!=' '||c4!=' '){
                    if((c1 == c2)&& (c2 == c3) && (c3 == c4)){
                        win = true;
                        break;
                    }
                }
            }
        }
    }

    //looking from right end of array rhs-diagonal
    if(!win){
        for(int r=0;r<3;r++){
            for(int c=6;c>2;c--){
                c1 = board[r][c];
                c2 = board[r+1][c-1];
                c3 = board[r+2][c-2];
                c4 = board[r+3][c-3];
                //checking for board[r][c]==board[r+1][c-1]==board[r+2][c-2]==board[r+3][c-3]
                if(c1!=' '||c2!=' '||c3!=' '||c4!=' '){
                    if((c1 == c2)&& (c2== c3) && (c3== c4)){
                        //cout<<"win"<<endl;
                        win=true;
                        break;
                    }
                }
            }
        }
    }
    //looking form left end of array lhs-diagonal
    if(!win){
        for(int r=0;r<3;r++){
            for(int c=0;c<4;c++){
                c1 = board[r][c];
                c2 = board[r+1][c+1];
                c3 = board[r+2][c+2];
                c4 = board[r+3][c+3];
                //checking for board[r][c]==board[r+1][c+1]==board[r+2][c+2]==board[r+3][c+3]
                if(c1!=' '||c2!=' '||c3!=' '||c4!=' '){
                    if((c1 == c2)&& (c2== c3) && (c3== c4)){
                        //cout<<"win"<<endl;
                        win=true;
                        break;
                    }
                }
            }
        }
    }
    return win;
}

/* overloading = operator to copy one
   board to another board object
*/
void tic::operator=(tic rhs){

    for(int i=0;i<row_size;i++){
        for(int j=0;j<col_size;j++){
            this->board[i][j] = rhs.board[i][j];
        }
    }

    for(int i=0;i<7;i++){
        this->moves[i].row_index = rhs.moves[i].row_index;
        this->moves[i].col_index = rhs.moves[i].col_index;
    }
    this->player = rhs.player;
}

/* this function is used for displaying
   board contents
*/
void tic::display_board(tic *x){
    cout<<endl;
    cout<<"C0 "<<" C1 "<<" C2 "<<" C3 "<<" C4 "<<" C5 "<<" C6"<<endl;
    for(int i=5;i>=0;i--){
        for(int j=0;j<7;j++){
            cout<<x->board[i][j]<<" | ";
        }
        cout<<endl;
        for(int k=0;k<7;k++)
            cout<<"----";
        cout<<endl;
    }
    cout<<endl;
}
