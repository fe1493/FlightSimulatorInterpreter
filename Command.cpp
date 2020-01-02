

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
                          OutputSymbolTable* outputSymbolTable,  queue<char*>* queueForUpdatingServer)
{
    // check if the text is string (like "text")
    string text = *(str + 1);
    if (text.at(0) == '"')
    {
        cout << *(str + 1) << endl;
    }
        // if the text is var, so we print his value.
    else
    {
        if (outputSymbolTable->outputMap->find(text) != outputSymbolTable->outputMap->end())
        {
            double value = outputSymbolTable->outputMap->at(text)->value;
            cout << value << endl;
        }
    }
    return 2;
}

// *** SleepCommand execute ***
int SleepCommand::execute(string *str, InputSymbolTable* inputSymbolTable,
                          OutputSymbolTable* outputSymbolTable, queue<char*> *queueForUpdatingServer)
{
    int milliseconds = stoi(*(str + 1));
    this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    return 2;
}