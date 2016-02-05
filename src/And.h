#include "Operator.h"

class And: public Operator
{
    And() {};

    And(Base* left, Base* right)
    {
        leftChild = left;
        rightChild = right;
    }

    int execute(){
        int check = leftChild->execute();
        if(check == 0)
        {
            //return whatever right child returns if left child successfully calls
            return rightChild->execute();
        }
        else if(check == -1)
        {
            //return -1 if left child calls exit
            return -1;
        }
        //return 1 if left child calls zero; the only reason left child would call zero is if the operation fails
        return 1;
    }
};
