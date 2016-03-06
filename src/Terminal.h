#include "Base.h"
#include "Parentheses.h"
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
            //sets up prompt
            GetLogin(login);
            GetHostName(hostName);
            //set up infinite loop
            bool run = true;
            while(run){
                //output prompt then gather input to run
                cout << '[' << login << "@" << hostName << ']' << '$' << ' ';
                ReadInput();
                Execute();
            }
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
            //reads user input and calls Decipher to make command tree
            string command;
            getline(cin, command);
            if(command.find("#") != string::npos)
            {
                command = command.substr(0, command.find("#"));
            }
            if (command != "")
            {
                Decipher(command);
            }
        }

        void extendTree(Base* tmp, string sep, Base* &addTo)
        {
            Base* tmp2;
            if (sep == "and")
            {
                tmp2 = new And(addTo, tmp);
                addTo = tmp2;
            }
            else if (sep == "or")
            {
                tmp2 = new  Or(addTo, tmp);
                addTo = tmp2;
            }
            else if (sep == "semicolon")
            {
                tmp2 = new Semicolon(addTo, tmp);
                addTo = tmp2;
            }
        }

        Base* parenthesesFound(string cmd)
        {
            string sep = "";
            bool detected = false;
            string op;
            Base* tmp;
            Base* tmp2;
            Base* parenthesesTree = 0;
            for (unsigned i = 0; i < cmd.size(); ++i)
            {
                if (cmd.at(i) == '(')
                {
                    unsigned count = 1;
                    for(unsigned j = i + 1; count != 0 && j < cmd.size(); ++ j)
                    {
                        if (cmd.at(j) == '(')
                        {
                            count++;
                        }
                        else if (cmd.at(j) == ')')
                        {
                            count--;
                        }
                        if (count == 0)
                        {
                            Base* tmp3;
                            string str_tmp = cmd.substr(i+1, j-i-1);
                            tmp3 = parenthesesFound(str_tmp);
                            cmd = cmd.substr(j+1, cmd.size()-1);
                            i = 0;
                            if (parenthesesTree == 0)
                            {
                                parenthesesTree = tmp3;
                            }
                            else
                            {
                                extendTree(tmp3, sep, parenthesesTree);
                            }
                            if (cmd.size() > 1)
                            {
                                for (unsigned k = 0; cmd.size() + 1 > k; ++k)
                                {
                                    if (cmd.at(k) == '&' && cmd.at(k+1) == '&')
                                    {
                                       sep = "and";
                                       detected = true;
                                    }
                                    else if ((cmd.at(k) == '|') && (cmd.at(k+1) == '|'))
                                    {
                                        sep = "or";
                                        detected = true;
                                    }
                                    if (detected)
                                    {
                                        if (cmd.size() > k+2)
                                        {
                                            cmd = cmd.substr(k+2, cmd.size());
                                        }
                                        else
                                        {
                                            cmd = " ";
                                        }
                                        k = 0;
                                    }
                                    if (cmd.at(k) == ';')
                                    {
                                        sep = "semicolon";
                                        cmd = cmd.substr(k+1, cmd.size()-1);
                                        detected = true;
                                    }
                                    if (detected) break; 
                                }
                                detected = false;
                            }
 
                        }
                    }
                }
                //run parsing for && || and ; but creating a
                //Parentheses Class and adding it to tree;
                if (cmd.size() <= 1) break;
                if (cmd.at(i) == '&' && cmd.at(i+1) == '&')
                {
                    detected = true;
                    //empty list check to create first node
                    if (parenthesesTree == 0)
                    {
                        op = cmd.substr(0, i);
                        parenthesesTree = new Operand(op);
                        sep = "and";
                    }
                    //creates operator based on what was last seen and
                    //updates what operator was last seen while creating
                    //the operator
                    else
                    {
                        op = cmd.substr(0, i);
                        tmp = new Operand(op);
                        extendTree(tmp, sep, parenthesesTree);
                        sep = "and";
                    }
                }
                //all parts same as and parse
                else if (cmd.at(i) == '|' && cmd.at(i+1) == '|')
                {
                    detected = true;
                    if (parenthesesTree == 0)
                    {
                        op = cmd.substr(0, i);
                        parenthesesTree = new Operand(op);
                        sep = "or";
                    }
                    else
                    {
                        op = cmd.substr(0, i);
                        tmp = new Operand(op);
                        extendTree(tmp, sep, parenthesesTree);
                        sep = "or";
                    }

                }
                //all parts same as and parse
                else if (cmd.at(i) == ';')
                {
                    if (parenthesesTree == 0)
                    {
                        op = cmd.substr(0, i);
                        cmd = cmd.substr(i+1, cmd.size()-1);
                        i = 0;
                        parenthesesTree = new Operand(op);
                        sep = "semicolon";
                    }
                    else
                    {
                        op = cmd.substr(0, i);
                        cmd = cmd.substr(i+1, cmd.size());
                        i = 0;
                        tmp = new Operand(op);
                        extendTree(tmp, sep, parenthesesTree);
                        sep = "semicolon";
                    }

                }
                if (detected)
                {
                    if (cmd.size() > i+2)
                    {
                        detected = false;
                        cmd = cmd.substr(i+2, cmd.size());
                    }
                    else
                    {
                        cmd = " ";
                    }
                    i = 0;
                }
            }

            if (parenthesesTree == 0)
            {
                parenthesesTree= new Operand(cmd);
            }
            //creates operator if node already exists
            else
            {
                tmp = new Operand(cmd);
                if (sep == "and")
                {
                    tmp2 = new And(parenthesesTree, tmp);
                    parenthesesTree= tmp2;
                }
                else if (sep == "or")
                {
                    tmp2 = new  Or(parenthesesTree, tmp);
                    parenthesesTree= tmp2;
                }
                else if (sep == "semicolon")
                {
                    tmp2 = new Semicolon(parenthesesTree, tmp);
                    parenthesesTree= tmp2;
                }
            }
 
//            parenthesesTree = new Parentheses(parenthesesTree);
            return parenthesesTree;
        }

        void Decipher(string c)
        {
            //use keystroke to separate keywords from input stored
            Base* tmp;
            Base* tmp2;
            string cmd = c;
            string op;
            string sep;
            bool detected = false;
            //goes through the command input looking through all chars and 
            //finding parsing strings such as && then parses the string
            //creating a command
            for (unsigned i = 0; i < cmd.size()-1; ++i)
            {
                if (cmd.at(i) == '(')
                {
                    unsigned count = 1;
                    for(unsigned j = i + 1; count != 0; ++j)
                    {
                        if (cmd.at(j) == '(')
                        {
                            count++;
                        }
                        else if (cmd.at(j) == ')')
                        {
                            count--;
                        }
                        if (count == 0)
                        {
                            string str_tmp = cmd.substr(i+1, j-i-1);
                            tmp = parenthesesFound(str_tmp);
                            cmd = cmd.substr(j+1, cmd.size()-1);
                            i = 0;
                            if (commandList == 0)
                            {
                                commandList = tmp;
                            }
                            else
                            {
                                extendTree(tmp, sep, commandList);
                            }
                            if (cmd.size() > 1)
                            {
                                for (unsigned k = 0; cmd.size() + 1 > k; ++k)
                                {
                                    if (cmd.at(k) == '&' && cmd.at(k+1) == '&')
                                    {
                                       sep = "and";
                                       detected = true;
                                    }
                                    else if ((cmd.at(k) == '|') && (cmd.at(k+1) == '|'))
                                    {
                                        sep = "or";
                                        detected = true;
                                    }
                                    if (detected)
                                    {
                                        if (cmd.size() > k+2)
                                        {
                                            cmd = cmd.substr(k+2, cmd.size());
                                        }
                                        else
                                        {
                                            cmd = " ";
                                        }
                                        k = 0;
                                    }
                                    if (cmd.at(k) == ';')
                                    {
                                        sep = "semicolon";
                                        cmd = cmd.substr(k+1, cmd.size()-1);
                                        detected = true;
                                    }
                                    if (detected) break; 
                                }
                                detected = false;
                            }
                        }
                        else if (j + 1 == cmd.size())
                        {
                            cmd = "";
                            cout << "Syntax Error" << endl;
                            return;
                        }
                    }
                }
                if (cmd.size() <= 1) break;
                if (cmd.at(i) == '&' && cmd.at(i+1) == '&')
                {
                    detected = true;
                    //empty list check to create first node
                    if (commandList == 0)
                    {
                        op = cmd.substr(0, i);
                        commandList = new Operand(op);
                        sep = "and";
                    }
                    //creates operator based on what was last seen and
                    //updates what operator was last seen while creating
                    //the operator
                    else
                    {
                        op = cmd.substr(0, i);
                        tmp = new Operand(op);
                        extendTree(tmp, sep, commandList);
                        sep = "and";
                    }
                }
                //all parts same as and parse
                else if (cmd.at(i) == '|' && cmd.at(i+1) == '|')
                {
                    detected = true;
                    if (commandList == 0)
                    {
                        op = cmd.substr(0, i);
                        commandList = new Operand(op);
                        sep = "or";
                    }
                    else
                    {
                        op = cmd.substr(0, i);
                        tmp = new Operand(op);
                        extendTree(tmp, sep, commandList);
                        sep = "or";
                    }

                }
                //all parts same as and parse
                else if (cmd.at(i) == ';')
                {
                    if (commandList == 0)
                    {
                        op = cmd.substr(0, i);
                        cmd = cmd.substr(i+1, cmd.size()-1);
                        i = 0;
                        commandList = new Operand(op);
                        sep = "semicolon";
                    }
                    else
                    {
                        op = cmd.substr(0, i);
                        cmd = cmd.substr(i+1, cmd.size());
                        i = 0;
                        tmp = new Operand(op);
                        extendTree(tmp, sep, commandList);
                        sep = "semicolon";
                    }

                }
                if (detected)
                {
                    if (cmd.size() > i+2)
                    {
                        detected = false;
                        cmd = cmd.substr(i+2, cmd.size());
                    }
                    else
                    {
                        cmd = " ";
                    }
                    i = 0;
                }
            }
            //creates inital node if none were created
            if (commandList == 0)
            {
                commandList = new Operand(cmd);
            }
            //creates operator if node already exists
            else
            {
                tmp = new Operand(cmd);
                if (sep == "and")
                {
                    tmp2 = new And(commandList, tmp);
                    commandList = tmp2;
                }
                else if (sep == "or")
                {
                    tmp2 = new  Or(commandList, tmp);
                    commandList = tmp2;
                }
                else if (sep == "semicolon")
                {
                    tmp2 = new Semicolon(commandList, tmp);
                    commandList = tmp2;
                }
            }
        }

        void Execute()
        {
            //Read in element from vector (will need to parse them), execute
            // corresponding command, and delete vector entry
            if (this->commandList != 0)
            {
                if (this->commandList->execute() == -1)
                {
                    //commandList->clean();
                    delete commandList;
                    exit(0);
                }
               // commandList->clean();
                delete commandList;
            }
            //make null pointer after delete to ensure seg fault on bad access
            commandList = 0;
        }
};
