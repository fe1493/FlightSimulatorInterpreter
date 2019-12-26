//
// Created by yonatan on 26/12/2019.
//

#ifndef PLEASEWORK_OUTPUTSYMBOLTABLE_H
#define PLEASEWORK_OUTPUTSYMBOLTABLE_H

#include "Command.h"

class OutputSymbolTable {
public:
    unordered_map<string, Command *> *outputMap = new unordered_map<string, Command *>{};
};


#endif //PLEASEWORK_OUTPUTSYMBOLTABLE_H
