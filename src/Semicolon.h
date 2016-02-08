#include "Operator.h"

class Semicolon: public Operator
{
    Semicolon() {}

    Semicolon(Base* left, Base* right)
    {
        leftChild = left;
        rightChild = right;
    }

    int execute()
    {
        int check = leftChild->execute();
        if(check == -1)
        {
            //return -1 if left child calls exit and returns -1
            return -1;
        }
        else
        {
            //return whatever right child returns if left child does not call exit
            return rightChild->execute();
        }
    }    
};
