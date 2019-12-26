//
// Created by Efraim Paley on 26/12/2019.
//

#include "DefineVarCommand.h"
#include "Var.h"

// *** DefineVarCommand execute ***
int DefineVarCommand ::execute(string *str, unordered_map<string, Command *> *input,
                               unordered_map<string, Command *>* output)
{
    int jump = 5;
    const char *rightArrow = "\x04->";
    const char *leftArrow = "\x04<-";
    const char *symbol = reinterpret_cast<const char *>(str + 2);
    //put into symbol table that updates the simulator
    if (strcmp(symbol, rightArrow) == 0)
    {
        int right = 1;
        //working with output symbol table
        Var *var = new Var();
        //assign variable name
        var->varName = *(str + 1);
        //direction
        var->direction = right;
        //assign sim name
        var->simName = *(str + 4);
        //value
        var->value = 0;
        output->insert({var->varName, input->at(var->simName)});
    }

    //left arrow direction
    if (strcmp(symbol, leftArrow) == 0)
    {
        int left = 1;
        Var *var = new Var();
        var->direction = left;
    }
    //assign the sim name of the variable
    //return how much we need to jump
    return jump;
}