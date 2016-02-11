#ifndef BASE_H
#define BASE_H

//pure virtual class to construct the tree with all virtual functions
//for run time decisions
class Base
{
    public:
        virtual int execute() = 0;
        virtual void clean() = 0;

        virtual ~Base() {};
};
#endif
