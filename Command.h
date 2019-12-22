//
// Created by yonatan on 15/12/2019.
//

#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H

#include <string>

using namespace std;

// Command Interface
class Command {
public:
    virtual int execute(string* str) = 0;
    //
};


#endif //EX3_COMMAND_H
