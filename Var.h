//
// Created by Efraim Paley on 26/12/2019.
//

#ifndef PLEASEWORK_VAR_H
#define PLEASEWORK_VAR_H

#include <string>
#include <cstring>
#include <unordered_map>
#include <chrono>
#include <mutex>
#include "Command.h"


// *** Var Class ***
class Var : public Command
{
public:
    string simName;
    string* updateInfoString;
    int direction;
    double value;

    virtual int execute(string* str, InputSymbolTable* inputSymbolTable,
                        OutputSymbolTable* outputSymbolTable,queue<string> *queueForUpdatingServer);



};



#endif //PLEASEWORK_VAR_H
