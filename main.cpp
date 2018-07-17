#include <iostream>
#include <ctime>

#include "MinmaxAB.h"
#include "TreeNodes.h"
#include "ConnectFourBoard.h"
#include "AlphaBeta.h"
using namespace std;

/*variable that can be accessed by files
  TreeNodes.h and .cpp, and main function
*/
int num_nodes_generated, num_nodes_expanded,game_path_length,start_time,stop_time;

/*made as a global variable since it must be accessible to
  Minmax() fn and also AlphaBeta() fn
*/
char evalfn_choiceX,evalfn_choiceO;


/* for calling minmaxAB function
   creates a tree object,board object and minmaxab object
   using a while loop keeps calling the minmaxAB function
   repeatedly until the condition checkPlayerWon evaluates
   to true. */
void MinMax(){

   int moves_made = 0;
   tic *board_ob = new tic;

   cout<<endl;
   cout<<"initial board state before starting game with(Initial Node config/Root Node) "<<moves_made<<" moves made"<<endl;
   cout<<"---------------------------------------------------------"<<endl;

   board_ob->display_board(board_ob);
   board_ob->player = 'X';

   start_time = clock();
    while(!board_ob->checkPlayerWon()){

        tree *head = new tree;
        *(head->ob) = *board_ob;

        if(head->ob->isBoardEmpty()){

            int random_col_index = head->ob->makeFirstMove();
            head->ob->board[0][random_col_index] = 'X';
            head->ob->player = 'X';
            moves_made++;
            game_path_length++;
            cout<<"After 1st move board state(Max's move/Root Node):"<<endl;
            head->ob->display_board(head->ob);
        }

        minmaxA min_ob;
        //assigns the users choice of evaluation function chosen
        min_ob.eval_choice = evalfn_choiceX;
        int x = min_ob.minmaxAB(head,0,1000,-1000,head->ob->player);
        moves_made++;
        game_path_length++;

        //to get the optimal node - Move Gen function
        head->move_gen(board_ob,moves_made);
    }
    stop_time = clock();
}

/* for calling minmaxAB function
   creates a tree object,board object and alphabeta object
   using a while loop keeps calling the alphabeta function
   repeatedly until the condition checkPlayerWon evaluates
   to true. */
void AlphaBeta(){

   int moves_made = 0;

   tic *board_ob = new tic;

   cout<<endl;
   cout<<"initial board state before starting game with(Initial Node config/Root Node) "<<moves_made<<" moves made"<<endl;
   cout<<"---------------------------------------------------------"<<endl;

   board_ob->display_board(board_ob);
   board_ob->player = 'X';

   start_time = clock();
   while(!board_ob->checkPlayerWon()){

        tree *head = new tree;
        *(head->ob) = *board_ob;

        if(head->ob->isBoardEmpty()){

            int random_col_index = head->ob->makeFirstMove();
            head->ob->board[0][random_col_index] = 'X';
            head->ob->player = 'X';
            moves_made++;
            game_path_length++;
            cout<<"After 1st move board state(Max's move/Root Node):"<<endl;
            head->ob->display_board(head->ob);
        }

        alphabeta ab_ob;
        //assigns the users choice of evaluation function chosen
        ab_ob.eval_choice = evalfn_choiceO;
        int x = ab_ob.alpha_beta(head,0,head->ob->player,1000,-1000);
        moves_made++;
        game_path_length++;

        //to get the optimal node - Move Gen function
        head->move_gen(board_ob,moves_made);
   }
   stop_time = clock();
}

int main()
{
    int algo_choiceX,algo_choiceO;
    cout<<"Select which Algorithm X has to play with ?"<<endl;
    cout<<endl;
    cout<<"  1 - MinmaxAB"<<endl;
    cout<<"  2 - AlphaBeta"<<endl;
    cout<<endl;
    cin>>algo_choiceX;
    cout<<endl;

    cout<<"Select which Algorithm O has to play with ?"<<endl;
    cout<<endl;
    cout<<"  1 - MinmaxAB"<<endl;
    cout<<"  2 - AlphaBeta"<<endl;
    cout<<endl;
    cin>>algo_choiceO;
    cout<<endl;

    cout<<"Choose the val function for player X "<<endl;
    cout<<"  M/m - Madhusudhan's eval function"<<endl;
    cout<<"  H/h - Harsha's eval function"<<endl;
    cout<<"  S/s - Santosh's eval function"<<endl;
    cout<<endl;
    cin>>evalfn_choiceX;
    cout<<endl;

    cout<<"Choose the val function for player O "<<endl;
    cout<<"  M/m - Madhusudhan's eval function"<<endl;
    cout<<"  H/h - Harsha's eval function"<<endl;
    cout<<"  S/s - Santosh's eval function"<<endl;
    cout<<endl;
    cin>>evalfn_choiceO;
    cout<<endl;


   int moves_made = 0;
   tic *board_ob = new tic;

   cout<<endl;
   cout<<"initial board state before starting game with(Initial Node config/Root Node) "<<moves_made<<" moves made"<<endl;
   cout<<"---------------------------------------------------------"<<endl;

   board_ob->display_board(board_ob);
   board_ob->player = 'X';

   start_time = clock();
    while(!board_ob->checkPlayerWon()){

        tree *head = new tree;
        *(head->ob) = *board_ob;

        if(head->ob->isBoardEmpty()){

            int random_col_index = head->ob->makeFirstMove();
            head->ob->board[0][random_col_index] = 'X';
            head->ob->player = 'X';
            moves_made++;
            game_path_length++;
            cout<<"After 1st move board state(Max's move/Root Node):"<<endl;
            head->ob->display_board(head->ob);
        }

        minmaxA min_ob;
        alphabeta ab_ob;


        //assigns the users choice of evaluation function chosen


        if(head->ob->player == 'X' && algo_choiceX == 1){
        min_ob.eval_choice = evalfn_choiceX;
        int x = min_ob.minmaxAB(head,0,1000,-1000,head->ob->player);
        moves_made++;
        game_path_length++;

        //to get the optimal node - Move Gen function
        //head->move_gen(board_ob,moves_made);
        }



        if(head->ob->player == 'O' && algo_choiceX == 1){
         min_ob.eval_choice = evalfn_choiceX;
        int x = min_ob.minmaxAB(head,0,1000,-1000,head->ob->player);
        moves_made++;
        game_path_length++;

        //to get the optimal node - Move Gen function
        //head->move_gen(board_ob,moves_made);
        }




        if(head->ob->player == 'X' && algo_choiceX == 2){
         ab_ob.eval_choice = evalfn_choiceX;
        //assigns the users choice of evaluation function chosen
        int x = ab_ob.alpha_beta(head,0,head->ob->player,1000,-1000);
        moves_made++;
        game_path_length++;

        //to get the optimal node - Move Gen function
        //head->move_gen(board_ob,moves_made);
        }



        if(head->ob->player == 'O' && algo_choiceX == 2){

        ab_ob.eval_choice = evalfn_choiceX;
        //assigns the users choice of evaluation function chosen
        int x = ab_ob.alpha_beta(head,0,head->ob->player,1000,-1000);
        moves_made++;
        game_path_length++;

        //to get the optimal node - Move Gen function
        //head->move_gen(board_ob,moves_made);

        }
        head->move_gen(board_ob,moves_made);


    }
    stop_time = clock();


    return 0;
}

