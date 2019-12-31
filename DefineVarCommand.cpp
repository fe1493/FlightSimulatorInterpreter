//
// Created by Efraim Paley on 26/12/2019.
//


#include "DefineVarCommand.h"
#include "Var.h"
#include "OutputSymbolTable.h"
#include "InputSymbolTable.h"


// *** DefineVarCommand execute  ***
int DefineVarCommand::execute(string *str, InputSymbolTable *inputSymbolTable,
                              OutputSymbolTable *outputSymbolTable,queue<char*> *queueForUpdatingServer) {
    int jump = 5;
    const char *rightArrow = "\x04->";
    const char *leftArrow = "\x04<-";
    const char *symbol = reinterpret_cast<const char *>(str + 2);
    //working with output symbol table
    Var *var = new Var();
    //assign variable name
    var->varName = *(str + 1);
    //direction
    var->direction = 0;
    //assign sim name
    var->simName = *(str + 4);
    //value
    var->value = 0;
    //put into symbol table that updates the simulator
    if (strcmp(symbol, rightArrow) == 0) {
        var->direction = 1;
        //put the new var in the output map according to its sim name
        outputSymbolTable->outputMap->insert({var->varName, inputSymbolTable->inputMap->at(var->simName)});
    }
    //left arrow direction
    if (strcmp(symbol, leftArrow) == 0) {

    }
    //assign the sim name of the variable
    //return how much we need to jump
    return jump;
}