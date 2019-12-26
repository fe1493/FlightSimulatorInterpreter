//
// Created by yonatan on 26/12/2019.
//

#ifndef PLEASEWORK_INPUTSYMBOLTABLE_H
#define PLEASEWORK_INPUTSYMBOLTABLE_H

#include "Command.h"

class InputSymbolTable {

public:
    InputSymbolTable();
    unordered_map<string, Command *> *inputMap = new unordered_map<string, Command *>{};
};


#endif //PLEASEWORK_INPUTSYMBOLTABLE_H
