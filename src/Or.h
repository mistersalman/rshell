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
        int check = leftChild->execute();
        if(check == 0)
        {
            return rightChild->execute();
        }
        return 1;
    }
};
