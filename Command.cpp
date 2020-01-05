

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
///
// *The execute for the printCommand, prints the information*
/// \param str - string of the commands
/// \param inputSymbolTable - table with all of the inputed info
/// \param outputSymbolTable - table with all of the out info
/// \param queueForUpdatingServer - queue which holds the strings that we need to send to the server in order to change the values
/// \return - How many spaces to jump in the parser

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

///
// *The execute for the SleepCommand, pauses the program*
/// \param str - string of the commands
/// \param inputSymbolTable - table with all of the inputed info
/// \param outputSymbolTable - table with all of the out info
/// \param queueForUpdatingServer - queue which holds the strings that we need to send to the server in order to change the values
/// \return How many spaces need to jump in the parser

// *** SleepCommand  ***
int SleepCommand::execute(string *str, InputSymbolTable* inputSymbolTable,
                          OutputSymbolTable* outputSymbolTable, queue<string> *queueForUpdatingServer)
{
    string temp = to_string(Parser::checkExpression((str + 1), outputSymbolTable));
    int milliseconds = stoi(temp);
    this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    return 2;
}