//
// Created by yonatan on 02/01/2020.
//

#ifndef PLEASEWORK_CONDITIONPARSER_H
#define PLEASEWORK_CONDITIONPARSER_H

#include "Command.h"

class ConditionParser: public Command {
private:
    unordered_map<string, Command *> *firstMapCommands;
public:
    ConditionParser(unordered_map<string, Command *> *firstMap){
        this->firstMapCommands = firstMap;
    }
    int execute(string *str, InputSymbolTable* inputSymbolTable,
                OutputSymbolTable* outputSymbolTable, queue<char*> *queueForUpdatingServer);
};


#endif //PLEASEWORK_CONDITIONPARSER_H
