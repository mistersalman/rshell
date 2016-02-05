#include "Base.h"
#include <string>

using namespace std;

class Operand: public Base
{
    char* data[256];

    Operand() {}

    Operand(string d)
    {

    }

    int execute()
    {
        if(data == "Exit" || data == "exit")
        {
            return -1;
        }


    }
};
