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

/*
 *  get string and remove the spaces at the beginning and the end of the string
 */
string removeSpace3(string str) {
    while (str.at(0) == ' ') {
        str = str.substr(1);
    }
    while (str.at(str.length() - 1) == ' ') {
        str = str.substr(0, str.length() - 1);
    }
    return str;
}