//
// Created by Efraim Paley on 26/12/2019.
//

#include "Var.h"
#include "ConnectCommand.h"
#include "Parser.h"

// *** Var execute ***
int Var ::execute(string *str, InputSymbolTable* inputSymbolTable,
                  OutputSymbolTable* outputSymbolTable,queue<char*> *queueForUpdatingServer)
{
    //if right- connect and send the value
    if (this->direction)
    {
        string temp = *(str + 1);
        //create the string with the sim name and value
        this->value = Parser::checkExpression(&temp, outputSymbolTable);
        this->updateInfoString += "set ";
        this->updateInfoString += this->simName;
        this->updateInfoString += " ";
        this->updateInfoString += to_string(this->value);
        this->updateInfoString +=" ";
        this->updateInfoString += "/r/n";
//        this->value = Parser::checkExpression(&temp, outputSymbolTable);
//        this->updateInfoString->append("set ");
//        this->updateInfoString->append(this->simName);
//        this->updateInfoString->append(" ");
//        this->updateInfoString->append(to_string(this->value));
//       this->updateInfoString->append(" ");
//        this->updateInfoString->append("/r/n");
        //enter into the queue. Queue is meant to hold the strings of all the sim names
        queueForUpdatingServer->push(&this->updateInfoString);

    }
    return 2;
}
