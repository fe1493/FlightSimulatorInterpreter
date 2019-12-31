

#include <iostream>
#include <thread>
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include "Command.h"
#include "OutputSymbolTable.h"
#include <arpa/inet.h>

// *** Print Command ***
int PrintCommand::execute(string *str, InputSymbolTable* inputSymbolTable,
                          OutputSymbolTable* outputSymbolTable,  queue<char*>* queueForUpdatingServer) {
    cout << str << endl;
    return 1;
}

// *** SleepCommand execute ***
int SleepCommand::execute(string *str, InputSymbolTable* inputSymbolTable,
                          OutputSymbolTable* outputSymbolTable, queue<char*> *queueForUpdatingServer) {
    this_thread::sleep_for(timeSpan);
    return 1;
}