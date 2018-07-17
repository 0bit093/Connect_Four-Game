#include<iostream>

#include "MinmaxAB.h"
#include "ConnectFourBoard.h"
#include "TreeNodes.h"
using namespace std;

minmaxA::minmaxA(){
    eval_choice = ' ';
}

/* this function is implemented from the algorithm given
   in Rich & Knight  text book.
   this function is used to find the node which is more probable to win
   in the future if the player plays the move returned by this function.

   in this function there are 2 cases 1st being base case which is executed
   when the depth cut-off that is reached, 2nd being recursive case that
   iterates through the loop for all the 7 children and recursively calls
   itself again and again until the base case condition evaluates to be true

   More complete description of how this function works is explained in project report
*/
int minmaxA::minmaxAB(tree *tob,int depth,int use_threshold,int pass_threshold,char player){

    int value;
    int new_value;
    char new_player;

    //gets executed if my eval function is selected by user
    if(eval_choice == 'M' || eval_choice == 'm'){
        if(tob->deep_enough(depth)){
            value = tob->evaluation_m();
            if(player == 'O')
                value = -value;
                tob->set_heuristic_value(value);
            return value;
        }
    }

    //gets executed if santosh's eval fn is chosen
    else if(eval_choice == 'S' || eval_choice == 's'){
        if(tob->deep_enough(depth)){
            value = tob->evaluation_s();
            if(player == 'O')
                value = -value;
                tob->set_heuristic_value(value);
            return value;
        }
    }

    //gets executed if harsha's eval fn is used
    else{
        if(tob->deep_enough(depth)){
            value = tob->evaluation_h();
            if(player == 'O')
                value = -value;
                tob->set_heuristic_value(value);
            return value;
        }
    }



    int value1=0;
    for(int i=0;i<7;i++){
        //checks the board player of the tob node and not the tob->children[] nodes
        if(player == 'X')
            new_player = 'O';
        if(player == 'O')
            new_player = 'X';

        value1 = minmaxAB(tob->children[i],depth+1,-pass_threshold,-use_threshold,new_player);
        new_value = -value1;

        if(new_value > pass_threshold){
            //holds the optimal nodes board config tree ob
             tob->set_heuristic_value(i);
             pass_threshold = new_value;
        }

        if(pass_threshold >= use_threshold){
            value1 = pass_threshold;
            return value1;
        }
    }
        value1 = pass_threshold;
        return value1;
}


