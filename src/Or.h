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
        if(check == 1)
        {
            //returns whatever right child returns
            return rightChild->execute();
        }
        else if(check == -1)
        {
            //returns -1 because left child called exit
            return -1;
        }
        //returns 0 because left child succeeded
        return 0;
    }
};
