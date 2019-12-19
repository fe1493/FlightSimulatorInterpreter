
//
// Created by yonatan on 15/12/2019.
//

#include <iostream>
#include <chrono>
#include <thread>
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
    virtual int execute()
    {
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
//      if (str + 2 == '->')
        this->simName = str +  4;
        return jump;
    }
};