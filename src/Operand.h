#include "Base.h"
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

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
        if (data == "exit" || data == "Exit")
        {
            return -1;
        }
        char *dat = new char[data.length() + 1];
        strcpy(dat, data.c_str());
        vector<char *> refs;
        char * pch;
        pch = strtok(dat, "/");
        
        refs.push_back("/bin/bash");
        refs.push_back("-c");

        while(pch != NULL)
        {
            refs.push_back(pch);
            pch = NULL;
            pch = strtok(NULL, "/");
        }
        refs.push_back(NULL);

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
        
        pid_t pid = fork();
        int status;

        if(pid  < 0)
        {
            printf("Serious error.\n");
        }

        else if(pid != 0)
        {
            wait(NULL);
        }

        else if(pid == 0)
        {
            if(execvp(args[0], args) < 0)
            {
                printf("Error, execution failed\n");
                return 1;
            }
            return 0;
        }


       /* if(execvp(args[0], args) == -1)
        {
            return 1;
        }*/

        if(j < refs.size())
        {
            return -1;
        }
        return 0;
    }
};
