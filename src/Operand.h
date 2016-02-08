#include "Base.h"
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <iostream>

using namespace std;

class Operand: public Base
{
    private:
    string data;

    public:

    Operand() {}

    Operand(string d)
    {
        data = d;
    }

    int execute()
    {
        char *dat = new char[data.length() + 1];
        strcpy(dat, data.c_str());
        vector<char *> refs;
        char * pch;
        pch = strtok(dat, "/ ");
        while(pch != NULL)
        {
            cout << "loop check" << endl;
            refs.push_back(pch);
            pch = NULL;
            pch = strtok(dat, "/ ");
        }
        cout << "end while loop 1" << endl;

        int j = -1;
        for(int i = 0; i < refs.size(); i++)
        {
            if(refs.at(i) == "Exit" || refs.at(i) == "exit")
            {
                j = i;
            }
        }
        if(j == -1)
        {
            j = refs.size();
        }

        char *args[j];

        for(int l = 0; l < j; l++)
        {
            args[l] = refs.at(l);
        }
        
        if(execvp(args[0], args) == -1)
        {
            return 1;
        }

        if(j < refs.size())
        {
            return -1;
        }
        return 0;
    }
};
