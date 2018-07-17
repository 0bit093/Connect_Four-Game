#ifndef ALPHABETA_H_INCLUDED
#define ALPHABETA_H_INCLUDED

#include <iostream>
#include "TreeNodes.h"
using namespace std;

class alphabeta{

public:

    //member variables
     char eval_choice;

    //Member functions of alphabeta class
    alphabeta();
    int alpha_beta(tree*, int, char, int, int);


};
#endif // ALPHABETA_H_INCLUDED
