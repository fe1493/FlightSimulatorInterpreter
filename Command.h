//
// Created by yonatan on 15/12/2019.
//

#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H

#include <string>
#include <unordered_map>
#include <chrono>
#include <mutex>


using namespace std;

// Command Interface
class Command {
public:
    virtual int execute(string* str, unordered_map<string, Command*>* input,
            unordered_map<string, Command*>* output) = 0;
    //
};


// *** PrintCommand Class ***
class PrintCommand : public Command{
public:
    virtual int execute(string* str, unordered_map<string, Command*>* input,
            unordered_map<string, Command*>* output);
};

// *** SleepCommand Class ***
class SleepCommand : public Command{
public:
    // every 1000 ms is 1 second
    chrono::milliseconds timeSpan;
    //
    virtual int execute(string* str, unordered_map<string, Command*>* input,
            unordered_map<string, Command*>* output);

};
// *** OpenServerCommand Class ***
class OpenServerCommand : public Command{
public:
    virtual int execute(string* str, unordered_map<string, Command*>* input,
            unordered_map<string, Command*>* output);
    static int openServer(string *str, bool* isConnect);
};



// *** ConnectCommand Class ***
class ConnectCommand : public Command{
public:
    virtual int execute(string* str, unordered_map<string, Command*>* input,
            unordered_map<string, Command*>* output);
    static int connectClient(string *str);
};
// *** DefineVarCommand Class ***
class DefineVarCommand : public Command
{
public:
    string* varName;
    string *simName;
    double value;

    virtual int execute(string *str, unordered_map<string, Command *> *input, unordered_map<string, Command *> *output);
};
// *** Var Class ***
class Var : public Command
{
public:
    string *simName;
    double value;
    Var(string * sn, double val)
    {
        this->simName = sn;
        this->value = val;
    }
    virtual int execute(string* str, unordered_map<string, Command*> *input, unordered_map<string, Command*> *output);

};



#endif //EX3_COMMAND_H
