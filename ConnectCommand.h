//
// Created by yonatan on 26/12/2019.
//

#ifndef PLEASEWORK_CONNECTCOMMAND_H
#define PLEASEWORK_CONNECTCOMMAND_H

#include "Command.h"
#include "OutputSymbolTable.h"
#include "InputSymbolTable.h"


// *** ConnectCommand Class ***
class ConnectCommand : public Command {
public:
    static int client_socket;

    virtual int execute(string *str, InputSymbolTable* inputSymbolTable,
                        OutputSymbolTable* outputSymbolTable,queue<char*> *queueForUpdatingServer);

    static int connectClient(string *str, bool *isClientConnect, queue<char*> *queue);
    static void* sendMessage(queue<char*> *queueForUpdatingServer, bool *isClientConnect);
    //

};


#endif //PLEASEWORK_CONNECTCOMMAND_H