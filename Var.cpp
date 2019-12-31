//
// Created by Efraim Paley on 26/12/2019.
//

#include "Var.h"
#include "ConnectCommand.h"

// *** Var execute ***
int Var ::execute(string *str, InputSymbolTable* inputSymbolTable,
                  OutputSymbolTable* outputSymbolTable,queue<char*> *queueForUpdatingServer)
{
    //if right- connefct to connect and send the value
    const char *rightArrow = "\x04->";
    const char *symbol = reinterpret_cast<const char *>(str + 2);
    this->simName = *(str + 4);

    if (strcmp(symbol, rightArrow) == 0)
    {
        this->value = stod(*(str + 1));
        this->updateInfoString->append("set");
        this->updateInfoString->append(this->simName);
        this->updateInfoString->append(to_string(this->value));
        this->updateInfoString->append((" "));
        this->updateInfoString->append("/r/n");
//        outputSymbolTable->outputMap->insert(this->updateInfoString, );
        //enter into the queue. Queue is meant to hold the strings of all the sim names
        queueForUpdatingServer->push((char*)(this->updateInfoString));
    }
    return 0;
}
//
//char* getString(char* str)
//{
//    return str;
//}