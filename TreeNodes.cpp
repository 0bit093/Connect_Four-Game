#include <cstdlib>
#include <ctime>

#include "TreeNodes.h"
using namespace std;

/* a constructor for the tree class that
   initializes all member variables of tree
   class
*/
tree::tree(){

    heuristic_value = -2000;
    num_children = 0;
    for(int i=0;i<7;i++){
        children[i] = NULL;
    }
    //creates pointer for new tic object
    ob = new tic();

}

/* this function creates nodes dynamically
   by using the new operator and assigns the
   address of the node returned by new
   operator to the pointer array that is
   member of each node(i.e tree object)
*/
void tree::create_node(char p){

    children[num_children++] = new tree();
}


/* sets the heuristic value using the
   variable value to nodes (i.e tree object)
*/
void tree::set_heuristic_value(int value){

    heuristic_value = value;
}

/* this function creates 7 nodes(i.e for child's)
   dynamically by using the create_node function
   above, assigns the player for each of those
   nodes and calls check_possible_moves function
   defined in the ConnectFourBoard.cpp file
   for all the possible moves that can be made by
   the player and assigns them
*/
void tree::add_all_children(){

    char p;
    int row,col;

    for(int i=0;i<7;i++){

        create_node('n');

        /*does the same task as above create_node('n');
        num_children++;
        this->children[i] = new tree();
        */

        *(children[i]->ob) = *(this->ob);


        /*checks parents node move i.e 'X'/'O' and makes
          child's move with the other character(Player)
          also sets the child's player to be that of
          the opposite of parent nodes player
        */

        if(this->ob->player == 'X'){
            p = 'O';
            this->children[i]->ob->player = p;
        }

        else if(ob->player == 'O'){
            p = 'X';
            this->children[i]->ob->player = p;
        }

        //if(ob->player == 'n')
        else{
            p = 'X';
            this->children[i]->ob->player = p;
        }
        /* keeps a count of the total number of
        nodes that is generated
        */
        num_nodes_generated++;
        children[i]->ob->checkPossibleMoves();
        row = children[i]->ob->moves[i].row_index;
        col = children[i]->ob->moves[i].col_index;
        children[i]->ob->board[row][col] = p;
    }
}

/* this function is used for a depth cut-off
   it has 3 cases where in 1st checks for
   whether heuristic value is set or not
   2nd checks whether a particular depth
   has been reached or not or if a player
   has won the game then return true
   3rd case being that both above cases
   failed that calls the above add_all_children
   function and return false once the control
   is returned back from the add_all_children
   function
*/
bool tree::deep_enough(int depth){

    if(heuristic_value!=-2000)
        return heuristic_value;

    else if(depth == 2 || ob->checkPlayerWon()){
            if(ob->checkPlayerWon()){
                /*so that the last terminal node is
                  also added to the tree i.e
                  board containing win configuration */
                this->add_all_children();
            }
            return true;
    }

    else{
        num_nodes_expanded++;
        this->add_all_children();
        return false;
    }
}

/* this is my (Madhusudhan) Evaluation function
   which is briefly described in my project report
   it creates a 2-d array same as connect-four board
   dimensions, assigns values to each cells of the
   board, depending on whether the player is Max/Min
   assigns values to them and returns the sum of
   initial_value and the value
*/

int tree::evaluation_m(){

        int evaluationTable[6][7] ={
                               {3, 4, 5, 7, 5, 4, 3},
                               {4, 6, 8, 10, 8, 6, 4},
                               {5, 8, 11, 13, 11, 8, 5},
                               {5, 8, 11, 13, 11, 8, 5},
                               {4, 6, 8, 10, 8, 6, 4},
                               {3, 4, 5, 7, 5, 4, 3}
                            };

        //since the sum of values of half board is 138.
        int initial_value = 138;
        int value = 0;

        if(ob->player == 'X'){
            //for lhs diagonal win
            for(int r=0;r<3;r++){
                for(int c=6;c>2;c--){
                    char c1 = ob->board[r][c];
                    char c2 = ob->board[r+1][c-1];
                    char c3 = ob->board[r+2][c-2];
                    char c4 = ob->board[r+3][c-3];
                    if((c1 == 'X' && c2 == 'X') || (c2 == 'X' && c3 == 'X') || (c3 == 'X' && c4 == ' ')){
                        value = 100;
                    }
                }
            }

            //for rhs diagonal win
            for(int r=0;r<3;r++){
                for(int c=0;c<4;c++){
                    char c1 = ob->board[r][c];
                    char c2 = ob->board[r+1][c+1];
                    char c3 = ob->board[r+2][c+2];
                    char c4 = ob->board[r+3][c+3];
                    if((c1 == 'X' && c2 == 'X') || (c2 == 'X' && c3 == 'X') || (c3 == 'X' && c4 == ' ')){
                        value = 100;
                    }
                }
            }

            for(int i = 0; i < 6; i++){
                for(int j = 0; j < 7; j++){
                    if (this->ob->board[i][j] == 'X')
                        value += evaluationTable[i][j];
                    else if (this->ob->board[i][j] == 'O')
                        value -= evaluationTable[i][j];
                }
            }
        }

        if(ob->player == 'O'){

            for(int r=0;r<3;r++){
                for(int c=6;c>2;c--){
                    char c1 = ob->board[r][c];
                    char c2 = ob->board[r+1][c-1];
                    char c3 = ob->board[r+2][c-2];
                    char c4 = ob->board[r+3][c-3];
                    if((c1 == 'O' && c2 == 'O') || (c2 == 'O' && c3 == 'O') || (c3 == 'O' && c4 == ' ')){
                        value = -100;
                    }
                }
            }

            //for rhs diagonal win
            for(int r=0;r<3;r++){
                for(int c=0;c<4;c++){
                    char c1 = ob->board[r][c];
                    char c2 = ob->board[r+1][c+1];
                    char c3 = ob->board[r+2][c+2];
                    char c4 = ob->board[r+3][c+3];
                    if((c1 == 'O' && c2 == 'O') || (c2 == 'O' && c3 == 'O') || (c3 == 'O' && c4 == ' ')){
                        value = -100;
                    }
                }
            }

            for(int i = 0; i < 6; i++){
                for(int j = 0; j < 7; j++){
                    if(this->ob->board[i][j] == 'X')
                        value += evaluationTable[i][j];
                    else if (this->ob->board[i][j] == 'O')
                        value -= evaluationTable[i][j];
                }
            }
        }
        return initial_value + value;
}

//santosh's eval fn
int tree::evaluation_s(){
    int value = 0;
//2 check
    if(ob->player == 'X'){
        for(int i=0;i<6;i++){
            for(int j=0;j<4;j++){
                //for continuous row
                //first checking whether not everything is empty
                if(ob->board[i][j]!= ' ' || ob->board[i][j+1]!= ' ' || ob->board[i][j+2]!= ' ' || ob->board[i][j+3]!= ' '){
                    if((ob->board[i][j] == ob->board[i][j+1]) && (ob->board[i][j+2]==' ')){
                        value = 100;
                    }
                }
            }
        }

        for(int i=0;i<3;i++){
            for(int j=0;j<7;j++){
                //for continuous col
                //first checking whether not everything is empty
                if(ob->board[i][j]!= ' ' || ob->board[i][j+1]!= ' ' || ob->board[i][j+2]!= ' ' || ob->board[i][j+3]!= ' '){
                     if((ob->board[i][j] == ob->board[i+1][j]) && (ob->board[i+2][j]==' ')){
                          value = 100;
                     }
                }
            }
        }

    }

    else if(ob->player == 'O'){
            for(int i=0;i<6;i++){
                for(int j=0;j<4;j++){
                    //for continuous row
                    //first checking whether not everything is empty
                    if(ob->board[i][j]!= ' ' || ob->board[i][j+1]!= ' ' || ob->board[i][j+2]!= ' ' || ob->board[i][j+3]!= ' '){
                         if((ob->board[i][j] == ob->board[i][j+1]) && (ob->board[i][j+2]==' ')){
                              value = -100;
                         }
                    }


                }
            }
        for(int i=0;i<3;i++){
            for(int j=0;j<7;j++){
                //for continuous col
                //first checking whether not everything is empty
                if(ob->board[i][j]!= ' ' || ob->board[i][j+1]!= ' ' || ob->board[i][j+2]!= ' ' || ob->board[i][j+3]!= ' '){
                     if((ob->board[i][j] == ob->board[i+1][j]) && (ob->board[i+2][j]==' ')){
                          value = -100;
                     }
                }
            }
        }

    }

    return value;
}

//harsha's eval fn
int tree::evaluation_h(){
    int value = 0;
//2 check
    if(ob->player == 'X'){
        for(int i=0;i<6;i++){
            for(int j=0;j<4;j++){
                //for continuous row
                //first checking whether not everything is empty
                if(ob->board[i][j]!= ' ' || ob->board[i][j+1]!= ' ' || ob->board[i][j+2]!= ' ' || ob->board[i][j+3]!= ' '){
                    if((ob->board[i][j] == ob->board[i][j+1]) && (ob->board[i][j+2]==' ')){
                        value = 100;
                    }
                }
            }
        }

        for(int i=0;i<3;i++){
            for(int j=0;j<7;j++){
                //for continuous col
                //first checking whether not everything is empty
                if(ob->board[i][j]!= ' ' || ob->board[i][j+1]!= ' ' || ob->board[i][j+2]!= ' ' || ob->board[i][j+3]!= ' '){
                     if((ob->board[i][j] == ob->board[i+1][j]) && (ob->board[i+2][j]==' ')){
                          value = 100;
                     }
                }
            }
        }


//3 check
//for continuous row
        for(int i=0;i<6;i++){
            for(int j=0;j<4;j++){

                     if(ob->board[i][j]!= ' ' || ob->board[i][j+1]!= ' ' || ob->board[i][j+2]!= ' ' || ob->board[i][j+3]!= ' '){

                    if((ob->board[i][j] == ob->board[i][j+1] == ob->board[i][j+2] && ob->board[i][j] == 'X') && (ob->board[i][j+3]==' ') || (ob->board[i][j+1] == ob->board[i][j+2] == ob->board[i][j+3] && ob->board[i][j] == 'X') && (ob->board[i][j+4]!= ' ')){
                        value = 100;
                    }
                }
            }
        }


    //3 check
    //for continuous col

        for(int i=0;i<3;i++){

            for(int j=0;j<7;j++){

                if(ob->board[i][j]!= ' ' || ob->board[i][j+1]!= ' ' || ob->board[i][j+2]!= ' ' || ob->board[i][j+3]!= ' '){

                     if((ob->board[i][j] == ob->board[i+1][j] == ob->board[i+2][j] && (ob->board[i][j] == 'X') && (ob->board[i+3][j] == ' ') || ob->board[i+1][j] == ob->board[i+2][j] == ob->board[i+3][j]) && (ob->board[i][j] == 'X') && (ob->board[i+4][j] == ' ')){
                          value = 100;
                     }
                }
            }
        }
    }

    else if(ob->player == 'O'){
            for(int i=0;i<6;i++){
                for(int j=0;j<4;j++){
                    //for continuous row
                    //first checking whether not everything is empty
                    if(ob->board[i][j]!= ' ' || ob->board[i][j+1]!= ' ' || ob->board[i][j+2]!= ' ' || ob->board[i][j+3]!= ' '){
                         if((ob->board[i][j] == ob->board[i][j+1]) && (ob->board[i][j+2]==' ')){
                              value = -100;
                         }
                    }


                }
            }
        for(int i=0;i<3;i++){
            for(int j=0;j<7;j++){
                //for continuous col
                //first checking whether not everything is empty
                if(ob->board[i][j]!= ' ' || ob->board[i][j+1]!= ' ' || ob->board[i][j+2]!= ' ' || ob->board[i][j+3]!= ' '){
                     if((ob->board[i][j] == ob->board[i+1][j]) && (ob->board[i+2][j]==' ')){
                          value = -100;
                     }
                }
            }
        }

//3 check
//for continuous row
        for(int i=0;i<6;i++){
            for(int j=0;j<4;j++){

                     if(ob->board[i][j]!= ' ' || ob->board[i][j+1]!= ' ' || ob->board[i][j+2]!= ' ' || ob->board[i][j+3]!= ' '){

                    if((ob->board[i][j] == ob->board[i][j+1] == ob->board[i][j+2] && ob->board[i][j] == 'O') && (ob->board[i][j+3]==' ') || (ob->board[i][j+1] == ob->board[i][j+2] == ob->board[i][j+3] && ob->board[i][j] == 'O') && (ob->board[i][j+4]!= ' ')){
                        value = -100;
                    }
                     }
            }
        }


    //3 check
    //for continuous col

        for(int i=0;i<3;i++){
            for(int j=0;j<7;j++){

                if(ob->board[i][j]!= ' ' || ob->board[i][j+1]!= ' ' || ob->board[i][j+2]!= ' ' || ob->board[i][j+3]!= ' '){

                     if((ob->board[i][j] == ob->board[i+1][j] == ob->board[i+2][j]) && (ob->board[i][j] == 'O') && (ob->board[i+3][j] == ' ') || ob->board[i+1][j] == ob->board[i+2][j] == ob->board[i+3][j] && (ob->board[i][j] == 'O') && (ob->board[i+4][j] == ' ')){
                          value = -100;
                     }
                }
            }
        }
    }

    return value;
}

/* this function copies one nodes board configuration
    to the other nodes board it the board's configuration
    that needs to be copied as a reference parameter
    passed to the function and copies all the contents of the
    rhs board object to the lhs board ob
*/
void tree::copy_board_status(tic &tc){

    for(int i=0;i<ob->row_size;i++){
        for(int j=0;j<ob->col_size;j++){
            this->ob->board[i][j] = tc.board[i][j];
        }
    }

    for(int i=0;i<7;i++){
        this->ob->moves[i].col_index = tc.moves[i].col_index;
        this->ob->moves[i].row_index = tc.moves[i].row_index;
    }
}

/* this function return a particular child node
   which has the same heuristic value as that of
   its parent node i.e it return the optimal child
   node's index (i.e 'i' in our case) that is
   most probable to win in the future
*/
int tree::getOptimalNode(){

    for(int i=0;i<7;i++){
        if(children[i]->heuristic_value == this->heuristic_value && this->heuristic_value != -2000)
            return i;
    }
    return -1;
}

/* this function checks whether the terminal node has been reached
   and calls display_contents function
*/
void tree::helper(){

    char c1,c2,c3,c4;

    for(int r=0;r<3;r++){
        for(int c=6;c>2;c--){
            c1 = ob->board[r][c];
            c2 = ob->board[r+1][c-1];
            c3 = ob->board[r+2][c-2];
            c4 = ob->board[r+3][c-3];
            //board[r][c]==board[r+1][c-1]==board[r+2][c-2]==board[r+3][c-3]
            if((c1 == c2 && c2 == c3 && c4 == ' ' && c1 == this->ob->player && this->ob->board[r+2][c-3]!= ' ')){
                //cout<<"RHS matched"<<endl;
                this->ob->board[r+3][c-3] = this->ob->player;
                display_contents();
                exit(0);
            }
        }
    }

    //looking form left end of array lhs-diagonal
    for(int r=0;r<3;r++){
        for(int c=0;c<4;c++){
            c1 = ob->board[r][c];
            c2 = ob->board[r+1][c+1];
            c3 = ob->board[r+2][c+2];
            c4 = ob->board[r+3][c+3];
            //board[r][c]==board[r+1][c+1]==board[r+2][c+2]==board[r+3][c+3]
            if((c1 == c2 && c2 == c3 && c4 == ' ' && c1 == this->ob->player && this->ob->board[r+2][c-3]!= ' ')){
                //cout<<"LHS matched"<<endl;
                this->ob->board[r+3][c+3] = this->ob->player;
                display_contents();
                exit(0);
            }
        }
    }
}

/* this function calls the above getOptimalNode function
   stores the child's index and copies this child node's
   board configuration to other created board by using
   overloaded = operator to copy or else when a terminal node
   i.e a win state is reached it calls the helper function
*/
void tree::move_gen(tic *board_ob,int moves_made){
    int child_number = this->getOptimalNode();

    if(child_number != -1){
        //since child number can be 0 - 6 so counter=-1
        *(board_ob) = *(this->children[child_number]->ob);
        if(moves_made == 2 || moves_made == 6 || moves_made == 10 || moves_made == 15){
            cout<<"Board state after "<<moves_made<<" moves:"<<endl;
            board_ob->display_board(board_ob);
        }
    }

    else if(child_number == -1)
        this->helper();
}


/* this function is used for displaying the
   results of the connect-four game
*/
void tree::display_contents(){

   int stop_time = clock();
   int total_time = (stop_time - start_time);
   double memory_used = 0.0;

   cout<<this->ob->player<<" Won!"<<endl;
   cout<<endl;
   cout<<"Terminal(win) state of the board:"<<endl;
   ob->display_board(ob);
   cout<<endl;
   cout<<"Number of nodes generated: "<<num_nodes_generated<<endl;
   // +1 is for the root node since it is also expanded from the empty board
   cout<<"Number of nodes expanded: "<< num_nodes_expanded + 1 <<endl;
   cout<<"Total length of game path: "<<game_path_length<<endl;
   cout<<"Memory size used by 1 node is: 268 bytes"<<endl;
   cout<<"Total size of memory used by program: "<<(268*num_nodes_generated)<<" bytes"<<endl;
   cout<<"Total execution Time: "<<(total_time) / double(CLOCKS_PER_SEC)<<"'s"<<endl;

}


