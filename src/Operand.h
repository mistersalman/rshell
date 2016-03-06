#include "Base.h"
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>

using namespace std;

class Operand: public Base
{
    private:
    string data; //instance field to hold command

    public:

    Operand() {} //default constructor

    Operand(string d)
    {
        data = d; //constructor with parameter passed it
    }

    void clean()
    {
        return;
    }

    int execute()
    {
        if (data == "")
        {
            return 1;
        }
        for (unsigned i = 0; i < data.length(); ++i)
        {
            if (data[0] == ' ')
            {
                data = data.substr(1, data.length()-1);
            }
            if (data[data.length()-1] == ' ')
            {
                data = data.substr(0, data.length()-1);
            }
        }
        if (data == "")
        {
            return 1;
        }
        string eXit = "exit";
        string Exit = "Exit";
        if (data == eXit || data == Exit)
        {
            return -1; //manually check for exit and actually exit
        }
        //if test is explicitly called, remove it and process data as follows
        if(data.substr(0, 4) == "test")
        {
            if(data.length() == 4 || data.length() == 5)
            {
                cout << "Nothing to test." << endl;
                return 1;
            }
            //check for flag and use as parameter if necessary
            data = data.substr(5, data.length() - 4);
            if(data.substr(0, 1) == "-")
            {
                return testCommand(data.substr(0, 2), data.substr(3, data.length() - 2));
            }
            else
            {
                return testCommand("emptyflag", data);
            }
        }
        //check if test is called using square brackets
        if(data.substr(0, 1) == "[" && data.substr(data.length() - 1, 1) == "]")
        {
            if(data.length() == 2 || data.length() == 3)
            {
                cout << "Nothing to test." << endl;
                return 1;
            }
            //check for flag and use as parameter if necessary
            data = data.substr(1, data.length() - 2);
            if(data.substr(0, 1) == "-")
            {
                return testCommand(data.substr(0, 2), data.substr(3, data.length() - 2));
            }
            else
            {
                return testCommand("emptyflag", data);
            }
        }

        char *dat = new char[data.length() + 1]; //create c-string with one 
        //extra space for NULL
        strcpy(dat, data.c_str());
        vector<char *> refs; //create vector with tokens from strtok
        char * pch;
        pch = strtok(dat, "/"); //initially used space as token, but found that 
        //we didn't need it
        string tmp = "/bin/bash";
        char* tmp2 = new char[tmp.length() + 1];
        strcpy(tmp2, tmp.c_str());
        refs.push_back(tmp2); //this just makes it run
        tmp = "-c";
        char* tmp3 = new char[tmp.length() +1];
        strcpy(tmp3, tmp.c_str());
        refs.push_back(tmp3); //same

        while(pch != NULL) //push back parts of command which have underwent 
        //strtok
        {
            refs.push_back(pch);
            pch = NULL;
            pch = strtok(NULL, "/");
        }
        refs.push_back(NULL); //null at end to terminate execvp call once needed

        int j = -1;
        if(j == -1) //if there is no exit present in the string, reside array
        {
            j = refs.size();
        }

        char** args = new char*[j]; //create array of char pointers with 
        //appropriate size

        for(int l = 0; l < j; l++) //copy over vector to char array
        {
            args[l] = refs.at(l);
        }
        
        pid_t pid = fork(); //process of calling fork and execvp begins here

        if(pid  < 0) //negative process IDs are errors - exit
        {
            perror("Serious Error.\n");
            exit(1);
        }

        else if(pid != 0)
        {
            int* status = new int;
            wait(status);
            if(*status != 0)
            {
                return 1;
            }
            else if (*status < 0)
            {
                perror("wait error\n");
            }
            else
            {
                return 0;
            }
        }

        else if(pid == 0) //execvp is called when the process ID is 0, if not, 
        //it waits until the process ID is zero
        {
            if(execvp(args[0], args) < 0)
            {
                perror("Error, Execution Failed\n"); //If execvp returns a 
                //negative number, print an error message and then exit
                exit(1);
            }
            delete[] args;
            delete pch;
            delete[] dat;
            delete[] tmp3;
            delete[] tmp2;
            refs.~vector();
            exit(0);
        }
        return 0;
    }
    
    int testCommand(string flag, string filepath)
    {
        //Use stat function as explained in tutorial
        struct stat sb;
        //Need to convert string to const char
        const char *path = filepath.c_str();
        if(flag == "noflag" || flag == "-e")
        {
            //if no flag is present or flag is -e, check only for existence
            if(stat(path, &sb) == 0)
            {
                cout << "(True)" << endl;
                return stat(path, &sb);
            }
        }
        else if(flag == "-d")
        {
            //if flag is -d, check for directory
            if(stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
            {
                cout << "(True)" << endl;
                return 0;
            }
        }
        else if(flag == "-f")
        {
            //if flag is -f, check for regular file
            if(stat(path, &sb) == 0 && S_ISREG(sb.st_mode))
            {
                cout << "(True)" << endl;
                return 0;
            }
        }
        cout << "(False)" << endl;
        return 1;
    }
};
