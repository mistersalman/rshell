#ifndef OPERATOR_H
#define OPERATOR_H

#include "Base.h"

class Operator: public Base
{
    public:
    Base* leftChild;
    Base* rightChild;
    virtual int execute() = 0;

    public:
    //function to clean the tree deleting children
    void clean()
    {
        leftChild->clean();
        rightChild->clean();
        delete leftChild;
        delete rightChild;
    }

    //deconstructor removing children
    ~Operator()
    {
        delete rightChild;
        delete leftChild;
    }
};
#endif
