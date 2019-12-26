//
// Created by Efraim Paley on 26/12/2019.
//

#ifndef PLEASEWORK_OPENSERVERCOMMAND_H
#define PLEASEWORK_OPENSERVERCOMMAND_H
#include "Command.h"
    // *** OpenServerCommand Class ***
    class OpenServerCommand : public Command
{
    public:
        virtual int execute(string* str, unordered_map<string, Command*>* input,
                            unordered_map<string, Command*>* output);
        static int openServer(string *str, bool* isConnect, unordered_map<string, Command *> *input);
        static void insertToInput(unordered_map<string, Command*>* input);
    };


#endif //PLEASEWORK_OPENSERVERCOMMAND_H
