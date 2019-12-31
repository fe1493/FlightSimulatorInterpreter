//
// Created by yonatan on 26/12/2019.
//

#ifndef PLEASEWORK_PARSER_H
#define PLEASEWORK_PARSER_H

#include "Command.h"
#include "OutputSymbolTable.h"
#include "InputSymbolTable.h"
#include <vector>

class Parser {
public:
    vector<string> *finalStringVector;
    unordered_map<string, Command *> *firstMapCommands;
    OutputSymbolTable* outputSymbolTable;
    InputSymbolTable* inputSymbolTable;
    queue<char*> *queueForUpdatingServer;


    Parser(vector<string> *stringVector,unordered_map<string, Command *> *firstMap,
            OutputSymbolTable* outputTable, InputSymbolTable* inputTable, queue<char*>* queue)
            {
        this->finalStringVector = stringVector;
        this->firstMapCommands = firstMap;
        this->outputSymbolTable = outputTable;
        this->inputSymbolTable = inputTable;
        this->queueForUpdatingServer = queue;
    }
    void parse();
};


#endif //PLEASEWORK_PARSER_H
