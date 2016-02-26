#include "Base.h"

class Parentheses : public Base
{
    public:
    Parentheses(Base* c) {Child = c;};

    int execute()
    {
        return Child->execute();
    }

    private:
        Base* Child;

};
