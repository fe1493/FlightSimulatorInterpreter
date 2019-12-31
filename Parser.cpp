//
// Created by yonatan on 26/12/2019.
//

#include <thread>
#include "Parser.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"

void Parser::parse() {
    int index = 0;
    bool isConnect = false;
    //parser
    while (index < finalStringVector->size()) {
        Command *c = firstMapCommands->at(finalStringVector->at(index));
        string commandName = finalStringVector->at(index);
        // if the current Command is OpenDataServer
        if (commandName == "openDataServer"){
            // open new thread, that create a new socket and wait to a client.
            // this thread stop the program, until the client connect and print the first line
            thread serverThread(OpenServerCommand::openServer, &finalStringVector->at(index), &isConnect,
                    this->inputSymbolTable);
            // while the client don't connect, stop the program
            while(!isConnect){
                serverThread.join();
            }
        }
        if (commandName == "connectControlClient"){
           // thread clientThread(ConnectCommand::connectClient, &finalStringVector->at(index));
            thread clientThread(ConnectCommand::connectClient, &finalStringVector->at(index),this->inputSymbolTable,
                                this->queueForUpdatingServer);
            clientThread.join();
        }
       // index += c->execute(&finalStringVector->at(index), this->inputSymbolTable, outputSymbolTable);
        index += c->execute(&finalStringVector->at(index), this->inputSymbolTable,
                            outputSymbolTable,this->queueForUpdatingServer);
    }
}
