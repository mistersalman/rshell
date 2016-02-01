#include "Base.h"
#include<string>
#include<iostream>
#include<stdlib.h>

using namespace std;

class Terminal
{
    public:
        void Run()
        {
            //code to run the terminal
            GetLogin();
            GetHostName();
            while(true){
                ReadInput();
                Execute();
            }
        }

        void Exit()
        {
            //deconstruct tree then exits
            exit(0);
        }
        Base* commandList;

    private:
        string login;
        string hostName;

        void GetLogin()
        {
            //gets user name for extra credit
        }

        void GetHostName()
        {
            //gets host name for extra credit
        }

        void ReadInput()
        {
            //reads user input
            string command;
            getline(cin, command);
            Decipher(command);
        }

        void Decipher(string c)
        {
            //use keystroke to separate keywords from input stored
        }

        void Execute()
        {
            //Read in element from vector (will need to parse them), execute
            // corresponding command, and delete vector entry
            commandList->execute();
        }
};
