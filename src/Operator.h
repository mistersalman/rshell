#ifndef OPERATOR_H
#define OPERATOR_H

#include "Base.h"

class Operator: public Base
{
    protected:
    Base* leftChild;
    Base* rightChild;
    virtual int execute() = 0;

    public:
    void clean()
    {
        leftChild->clean();
        rightChild->clean();
        delete leftChild;
        delete rightChild;
    }

    ~Operator()
    {
        delete rightChild;
        delete leftChild;
    }
};
#endif
