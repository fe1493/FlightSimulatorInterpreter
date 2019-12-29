//
// Created by yonatan on 26/12/2019.
//

#ifndef PLEASEWORK_INPUTSYMBOLTABLE_H
#define PLEASEWORK_INPUTSYMBOLTABLE_H

#include "Var.h"

class InputSymbolTable {

public:
    InputSymbolTable();
    unordered_map<string, Var *> *inputMap = new unordered_map<string, Var *>{};
};


#endif //PLEASEWORK_INPUTSYMBOLTABLE_H
