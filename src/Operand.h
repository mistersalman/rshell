#include "Base.h"
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

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
        pch = strtok(dat, "/");
        
        refs.push_back("/bin/bash");
        refs.push_back("-c");

        while(pch != NULL)
        {
            refs.push_back(pch);
            pch = NULL;
            pch = strtok(NULL, "/");
        }

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
        
        pid_t pid;
        int status;

        if((pid = fork()) < 0)
        {
            printf("Serious Error.\n");
            exit(1);
        }

        else if(pid == 0)
        {
            if(execvp(args[0], args) < 0)
            {
                perror("Error, Execution Failed\n");
                exit(1);
            }
        }

        else
        {
            while(wait(&status) !=pid);
        }
        
        if(status != 0)
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
