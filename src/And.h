#include "Operator.h"

class And: public Operator
{
    int execute(){
        int check = leftChild->execute();
        if(check == 1)
        {
            return rightChild->execute();
        }
        return 0;
    }

    And() {};

    And(Base* left, Base* right)
    {
        leftChild = left;
        rightChild = right;
    }
};
