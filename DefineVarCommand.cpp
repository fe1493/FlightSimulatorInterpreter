//
// Created by Efraim Paley on 26/12/2019.
//


#include "DefineVarCommand.h"
#include "Var.h"
#include "OutputSymbolTable.h"
#include "InputSymbolTable.h"
#include "Parser.h"


// *** DefineVarCommand execute ***
int DefineVarCommand::execute(string *str, InputSymbolTable *inputSymbolTable,
                              OutputSymbolTable *outputSymbolTable, queue<string> *queueForUpdatingServer) {
    int jump;
    if (*(str + 3) == "sim"){
        jump = 5;
        // const char *symbol = reinterpret_cast<const char *>(str + 2);
        string varName = *(str + 1);
        string varSim = *(str + 4);
        varSim = varSim.substr(1, varSim.length() - 2);
        string varDirection = *(str + 2);
        // connect this var to the same var in the output symbol table
        outputSymbolTable->outputMap->insert({varName, inputSymbolTable->inputMap->at(varSim)});
        // update the direction of the var
        if (varDirection == "->"){
            inputSymbolTable->inputMap->at(varSim)->direction = 1;
        }
    }
    else
    {
        jump = 2;
        Var *var = new Var();
        // var value can be ONE option:
        // 1. value of var from the input symbol table
        // 2. Expression
        string temp = *(str + 2);
        var->value = Parser::checkExpression(&temp, outputSymbolTable);
        outputSymbolTable->outputMap->insert({*(str + 1), var});
    }




//    //put into symbol table that updates the simulator
//    if (strcmp(symbol, rightArrow) == 0) {
//        int right = 1;
//        //working with output symbol table
//        Var *var = new Var();
//        //assign variable name
//        var->varName = *(str + 1);
//        //direction
//        var->direction = right;
//        //assign sim name
//        var->simName = *(str + 4);
//        //value
//        var->value = 0;
//        outputSymbolTable->outputMap->insert({var->varName, inputSymbolTable->inputMap->at(var->simName)});
//    }
//
//    //left arrow direction
//    if (strcmp(symbol, leftArrow) == 0) {
//        int left = 1;
//        Var *var = new Var();
//        var->direction = left;
//    }
    //return how much we need to jump
    return jump;
}
