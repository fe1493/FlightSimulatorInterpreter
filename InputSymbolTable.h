//
// Created by yonatan on 26/12/2019.
//

#ifndef PLEASEWORK_INPUTSYMBOLTABLE_H
#define PLEASEWORK_INPUTSYMBOLTABLE_H

#include "Command.h"

class InputSymbolTable {

public:
    unordered_map<string, Command *> *inputMap;
    InputSymbolTable(){
        inputMap = new unordered_map<string, Command *>{};
    }
};


#endif //PLEASEWORK_INPUTSYMBOLTABLE_H
