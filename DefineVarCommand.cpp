//
// Created by Efraim Paley on 26/12/2019.
//


#include "DefineVarCommand.h"
#include "Var.h"
#include "OutputSymbolTable.h"
#include "InputSymbolTable.h"
#include "Parser.h"


///
// *** DefineVarCommand execute - updates the information of the server and our values, depending on the
// direction of the arrow ***

/// \param str - string of the commands
/// \param inputSymbolTable - table with all of the inputed info
/// \param outputSymbolTable - table with all of the out info
/// \param queueForUpdatingServer - queue which holds the strings that we need to send to the server in order to change the values
/// \return - How many spaces to jump in the parser

int DefineVarCommand::execute(string *str, InputSymbolTable *inputSymbolTable,
                              OutputSymbolTable *outputSymbolTable, queue<string> *queueForUpdatingServer) {
    int jump;
    if (*(str + 3) == "sim"){
        jump = 5;
        //get var name
        string varName = *(str + 1);
        //get var sim
        string varSim = *(str + 4);
        //get rid of slashes
        varSim = varSim.substr(1, varSim.length() - 2);
        //get var direction
        string varDirection = *(str + 2);
        // connect this var to the same var in the output symbol table
        outputSymbolTable->outputMap->insert({varName, inputSymbolTable->inputMap->at(varSim)});
        // update the direction of the var
        if (varDirection == "->")
        {
            inputSymbolTable->inputMap->at(varSim)->direction = 1;
        }
    }
    else
    {
        jump = 3;
        Var *var = new Var();
        // var value can be ONE option:
        // 1. value of var from the input symbol table
        // 2. Expression
        string temp = *(str + 2);
        var->value = to_string(Parser::checkExpression(&temp, outputSymbolTable));
        outputSymbolTable->outputMap->insert({*(str + 1), var});
    }

    return jump;
}
