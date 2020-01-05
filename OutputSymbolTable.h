//
// Created by yonatan on 26/12/2019.
//

#ifndef PLEASEWORK_OUTPUTSYMBOLTABLE_H
#define PLEASEWORK_OUTPUTSYMBOLTABLE_H

#include "Var.h"

class OutputSymbolTable {
public:
    unordered_map<string, Var *> *outputMap = new unordered_map<string, Var *>{};
};


#endif //PLEASEWORK_OUTPUTSYMBOLTABLE_H

