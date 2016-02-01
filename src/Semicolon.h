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
        leftChild->execute();
        rightChild->execute();
    }    
};
