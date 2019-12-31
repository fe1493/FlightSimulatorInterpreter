//
// Created by yonatan on 15/12/2019.
//

#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_map>
#include <thread>
#include <cstring>
#include <string>
#include <chrono>
#include <queue>


using namespace std;
class InputSymbolTable;
class OutputSymbolTable;

// Command Interface
class Command
{
public:
    virtual int execute(string *str, InputSymbolTable* inputSymbolTable,
                        OutputSymbolTable* outputSymbolTable, queue<char*> *queueForUpdatingServer) = 0;
};


// *** PrintCommand Class ***
class PrintCommand : public Command
{
public:
    virtual int execute(string *str, InputSymbolTable* inputSymbolTable,
                        OutputSymbolTable* outputSymbolTable, queue<char*> *gqueueForUpdatingServer);
};

// *** SleepCommand Class ***
class SleepCommand : public Command
{
public:
    // every 1000 ms is 1 second
    chrono::milliseconds timeSpan;

    //
    virtual int execute(string *str, InputSymbolTable* inputSymbolTable,
                        OutputSymbolTable* outputSymbolTable, queue<char*> *queueForUpdatingServer);

};



#endif //EX3_COMMAND_H
