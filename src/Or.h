#include "Operator.h"

class Or: public Operator
{
    Or() {};

    Or(Base* left, Base* right)
    {
        leftChild = left;
        rightChild = right;
    }

    int execute(){

    }
};
