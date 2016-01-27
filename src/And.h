#include "Operator.h"

class And: public Operator
{
    int execute(){

    }

    And() {};

    And(Base* left, Base* right)
    {
        leftChild = left;
        rightChild = right;
    }
};
