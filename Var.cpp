//
// Created by Efraim Paley on 26/12/2019.
//

#include "Var.h"
#include "ConnectCommand.h"
#include "Parser.h"

// *** Var execute ***
int Var ::execute(string *str, InputSymbolTable* inputSymbolTable,
                  OutputSymbolTable* outputSymbolTable,queue<string> *queueForUpdatingServer)
{
    //if right- connect and send the value
    if (this->direction)
    {
        string temp = *(str + 1);
        //create the string with the sim name and value
        this->value = Parser::checkExpression(&temp, outputSymbolTable);
        string val = to_string(this->value);
        string str = "set " + this->simName + " " + val + "\r\n";
        //enter into the queue. Queue is meant to hold the strings of all the sim names
        queueForUpdatingServer->push(str);
    }
    return 2;
}
