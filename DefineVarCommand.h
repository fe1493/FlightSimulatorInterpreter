//
// Created by Efraim Paley on 26/12/2019.
//

#ifndef PLEASEWORK_DEFINEVARCOMMAND_H
#define PLEASEWORK_DEFINEVARCOMMAND_H

#include <string>
#include <unordered_map>
#include <chrono>
#include <mutex>
#include "Command.h"
#include "OutputSymbolTable.h"

// *** DefineVarCommand Class ***
class DefineVarCommand : public Command
{
public:
    string* varName;
    string *simName;
    double value;
//
    virtual int execute(string *str, InputSymbolTable* inputSymbolTable,
                        OutputSymbolTable* outputSymbolTable,queue<char*> *queueForUpdatingServer);
};

#endif //PLEASEWORK_DEFINEVARCOMMAND_H
