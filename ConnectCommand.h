//
// Created by yonatan on 26/12/2019.
//

#ifndef PLEASEWORK_CONNECTCOMMAND_H
#define PLEASEWORK_CONNECTCOMMAND_H

#include "Command.h"

// *** ConnectCommand Class ***
class ConnectCommand : public Command {
public:
    virtual int execute(string *str, unordered_map<string, Command *> *input,
                        unordered_map<string, Command *> *output);

    static int connectClient(string *str);
};


#endif //PLEASEWORK_CONNECTCOMMAND_H
