//
// Created by Efraim Paley on 26/12/2019.
//

#include "Var.h"
#include "ConnectCommand.h"
#include "Parser.h"

string removeSpace3(string str);

// *** Var execute ***
int Var ::execute(string *str, InputSymbolTable* inputSymbolTable,
                  OutputSymbolTable* outputSymbolTable,queue<string> *queueForUpdatingServer)
{
    //if right- connect and send the value
    if (this->direction)
    {
        string temp = *(str + 1);
        //temp = removeSpace3(temp);
        //create the string with the sim name and value
        this->value = to_string(Parser::checkExpression(&temp, outputSymbolTable));
        string str = "set " + this->simName + " " + this->value + "\r\n";
        //enter into the queue. Queue is meant to hold the strings of all the sim names
        queueForUpdatingServer->push(str);
    }
    return 2;
}