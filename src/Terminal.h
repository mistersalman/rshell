#include "Base.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

class Terminal
{
    public:
        Terminal() {commandList = 0;}

        void Run()
        {
            //code to run the terminal
            GetLogin(login);
            GetHostName(hostName);
            bool run = true;
            while(run){
                cout << '[' << login << "@" << hostName << ']' << '$' << ' ';
                ReadInput();
                Execute();
            }
        }

        void Exit()
        {
            //de-construct tree then exits
            exit(0);
        }
        Base* commandList;

    private:
        char login[256];
        char hostName[256];

        void GetLogin(char* Login)
        {
            //gets user name for extra credit
            getlogin_r(Login, 256);
            return;
        }

        void GetHostName(char* name)
        {
            //gets host name for extra credit
            gethostname(name, 256);
            return;
        }

        void ReadInput()
        {
            //reads user input
            string command;
            getline(cin, command);
            if(command.find("#") != string::npos)
            {
                command = command.substr(0, command.find("#"));
            }
            Decipher(command);
        }

        void Decipher(string c)
        {
            //use keystroke to separate keywords from input stored
            Base* tmp;
            Base* tmp2;
            string cmd = c;
            cout << "start loop" << endl;
            for (unsigned i = 0; i < cmd.size() - 1; ++i)
            {
                if (cmd.at(i) == '&' && cmd.at(i+1) == '&')
                {

                }
                else if (cmd.at(i) == '|' && cmd.at(i+1) == '|')
                {

                }
                else if (cmd.at(i) == ';')
                {

                }
            }
            cout << "end loop" << endl;
            tmp = new Operand(cmd);
            if (commandList == 0)
            {
                commandList = tmp;
            }
            
        }

        void Execute()
        {
            //Read in element from vector (will need to parse them), execute
            // corresponding command, and delete vector entry
            if (this->commandList != 0)
            {
                this->commandList->execute();
            }
        }
};
