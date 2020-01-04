//
// Created by Efraim Paley on 26/12/2019.
//

#ifndef PLEASEWORK_OPENSERVERCOMMAND_H
#define PLEASEWORK_OPENSERVERCOMMAND_H
#include "Command.h"
#include "InputSymbolTable.h"
#include "OutputSymbolTable.h"

// *** OpenServerCommand Class ***
    class OpenServerCommand : public Command
{
    public:
        virtual int execute(string* str, InputSymbolTable* inputSymbolTable,
                            OutputSymbolTable* outputSymbolTable,queue<string> *queueForUpdatingServer);
        static int openServer(string *str, bool* isConnect, InputSymbolTable *input, OutputSymbolTable* outputSymbolTable);
    };


#endif //PLEASEWORK_OPENSERVERCOMMAND_H
