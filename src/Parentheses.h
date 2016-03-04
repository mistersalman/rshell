#include "Base.h"

#ifndef PARENTHESES_H
#define PARENTHESES_H

class Parentheses : public Base
{
    public:
    Parentheses(Base* c) {Child = c;};

    int execute()
    {
        return Child->execute();
    }

    ~Parentheses() {delete Child;};

    void clean() {delete Child;};

    private:
        Base* Child;

};

#endif
