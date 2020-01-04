

#include <iostream>
#include <thread>
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include "Command.h"
#include "OutputSymbolTable.h"
#include "Parser.h"
#include <arpa/inet.h>

// *** Print Command ***
int PrintCommand::execute(string *str, InputSymbolTable* inputSymbolTable,
                          OutputSymbolTable* outputSymbolTable,  queue<string>* queueForUpdatingServer)
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
            string value = to_string(Parser::checkExpression(&outputSymbolTable->outputMap->at(text)->value, outputSymbolTable));
            cout << value << endl;
        }
    }
    return 2;
}

// *** SleepCommand execute ***
int SleepCommand::execute(string *str, InputSymbolTable* inputSymbolTable,
                          OutputSymbolTable* outputSymbolTable, queue<string> *queueForUpdatingServer)
{
    string temp = to_string(Parser::checkExpression((str + 1), outputSymbolTable));
    int milliseconds = stoi(temp);
    this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    return 2;
}