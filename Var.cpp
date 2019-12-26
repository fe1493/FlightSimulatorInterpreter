//
// Created by Efraim Paley on 26/12/2019.
//

#include "Var.h"
// *** Var execute ***
int Var ::execute(string *str, unordered_map<string, Command *> *input,unordered_map<string, Command *>* output)
{
    //if right- connefct to connect and send the value
    const char *rightArrow = "\x04->";
    const char *symbol = reinterpret_cast<const char *>(str + 2);
    if (strcmp(symbol, rightArrow) == 0)
    {

    }
}