

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
class PrintCommand : public Command{
public:
    string str;
    virtual int execute(){
        cout << str << endl;
    }
};

// Sleep Command
class SleepCommand : public Command{
public:
    // every 1000 ms is 1 second
    chrono::milliseconds timeSpan;
    //
    virtual int execute(){
        this_thread::sleep_for(timeSpan);
    }
};

class OpenServerCommand : public Command{
public:

    virtual int execute(string* str)
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
};


class ConnectCommand : public Command{
public:
    virtual int execute(string* str)
    {
        int jump = 2;
        return jump;

    }
};

class DefineVarCommand : public Command{
public:
    string varName;
    string* simName;
    double value;

//
//     DefineVarCommand (string n, string sim, double val)
//    {
//        this->varName = n;
//        this->simName = sim;
//        this->value = val;
//    }


    virtual int execute(string* str)
    {
        int jump = 5;
        const char *rightArrow =  "\x04->";
        const char* leftArrow =  "\x04<-";
        const char* symbol = reinterpret_cast<const char *>(str + 2);
        //put into symbol table that updates the simulator
        if (strcmp(symbol,rightArrow) == 0)
        {
            //need to create symbol table
            int temp = 1;
        }
        //put into symbol table that gets updates from the simulator
        if (strcmp(symbol,leftArrow) == 0)
        {
            int temp = 0;


        }
        this->simName = str +  4;
        return jump;
    }
};