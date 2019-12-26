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
class Command
{
public:
    virtual int execute(string *str, unordered_map<string, Command *> *input,
                        unordered_map<string, Command *> *output) = 0;
};


// *** PrintCommand Class ***
class PrintCommand : public Command
{
public:
    virtual int execute(string *str, unordered_map<string, Command *> *input,
                        unordered_map<string, Command *> *output);
};

// *** SleepCommand Class ***
class SleepCommand : public Command
{
public:
    // every 1000 ms is 1 second
    chrono::milliseconds timeSpan;

    //
    virtual int execute(string *str, unordered_map<string, Command *> *input,
                        unordered_map<string, Command *> *output);

};


// *** ConnectCommand Class ***
class ConnectCommand : public Command
{
public:
    virtual int execute(string *str, unordered_map<string, Command *> *input,
                        unordered_map<string, Command *> *output);

    static int connectClient(string *str);
};




#endif //EX3_COMMAND_H
