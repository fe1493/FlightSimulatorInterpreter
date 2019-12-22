

#include <iostream>
#include <chrono>
#include <thread>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include "Command.h"

// Print Command
int PrintCommand ::execute(string *str, unordered_map<string, Command *> input,
                           unordered_map<string, Command *> output)
{
    cout << str << endl;
    return 1;
}

// *** SleepCommand execute ***
int SleepCommand::execute(string *str, unordered_map<string, Command *> input,
                          unordered_map<string, Command *> output)
{
    this_thread::sleep_for(timeSpan);
    return 1;
}

// *** OpenServerCommand execute ***

 int OpenServerCommand::execute(string *str, unordered_map<string, Command *> input,
         unordered_map<string, Command *> output)

    {
        int socketfd = socket(AF_INET, SOCK_STREAM, 0);
        if (socketfd == -1) {
            //error
            std::cerr << "Could not create a socket"<<std::endl;
            return -1;
        }
        sockaddr_in address; //in means IP4
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
//        address.sin_port = htons(str + 1);
        int jump = 2;
        return jump;
    }

// *** ConnectCommand execute ***
int ConnectCommand::execute(string *str, unordered_map<string, Command *> input,
                            unordered_map<string, Command *> output)
    {
        int jump = 3;
        return jump;

    }

// *** DefineVarCommand execute ***
int DefineVarCommand ::execute(string *str, unordered_map<string, Command *> input,
                               unordered_map<string, Command *> output)
{
    int jump = 5;
    const char *rightArrow = "\x04->";
    const char *leftArrow = "\x04<-";
    const char *symbol = reinterpret_cast<const char *>(str + 2);
    //put into symbol table that updates the simulator
    if (strcmp(symbol, rightArrow) == 0)
    {
        //working with output symbol table



    }
    //
    //put into symbol table that gets updates from the simulator
    if (strcmp(symbol, leftArrow) == 0)
    {
        //unordered_map<string, Command*> firstMap()
        int temp = 0;


    }
    //assign the simname of the variable
    this->simName = str + 4;
    //return how much we need to jump
    return jump;
}




// *** Var execute ***
int Var ::execute(string *str, unordered_map<string, Command *> input,unordered_map<string, Command *> output)
{
    Command* var = new Var();

}


