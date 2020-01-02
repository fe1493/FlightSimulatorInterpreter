#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "Command.h"
#include "OpenServerCommand.h"
#include "DefineVarCommand.h"
#include "OutputSymbolTable.h"
#include "InputSymbolTable.h"
#include "ConnectCommand.h"
#include "Parser.h"
#include "ConditionParser.h"

using namespace std;

vector<string> *Lexer(const string &file);

unordered_map<string, Command *> *firstMap();

string removeSpace(string str);

int main(int argc, char *argv[]) {
    // read from file
    // get a string array of all the words from the file
    vector<string> *finalStringVector = Lexer(argv[1]);

    // initialize the MAIN COMMAND MAP
    unordered_map<string, Command *> *firstMapCommands = firstMap();

    // initialize the Symbol table (I/O)
    auto* outputSymbolTable = new OutputSymbolTable();
    auto* inputSymbolTable = new InputSymbolTable();
    //queue for updating sim
    auto *queueForUpdatingServer = new queue<char*>;
    // create parser
    auto* parser = new Parser(finalStringVector, firstMapCommands, outputSymbolTable, inputSymbolTable,
                              queueForUpdatingServer);
    // parse
    parser->parse();
}

vector<string> *Lexer(const string &fileName) {
    //the file that we will read into
    ifstream myFile;
    myFile.open(fileName);
    if (myFile.fail()) { // error check,
        cout << "ERROR OPENING FILE" << endl;
        exit(1);
    }
    auto *finalStringVector = new vector<string>{};
    string line;
    //go over each line
    while (getline(myFile, line)) {
        //code from EX1
        unsigned long int found = line.find_first_of(" \t,()= ");
        unsigned long int lastFound = 0;
        string lastWord;

        while (found != string::npos) {
            // case 1: while. insert the condition to the next token
            if (lastWord == "while") {
                // line - 6 = all the line except the "while" and "{"
                string temp = line.substr(lastFound, line.length() - 6);
                temp = removeSpace(temp);
                finalStringVector->push_back(temp);
                break;
            }
            // case 2: Print. insert the text to the next token
            if (lastWord == "Print") {
                unsigned long int foundStart = line.find_first_of('(');
                // line - 7 = all the line except the "Print" and ")" in the end of the line
                string temp = line.substr(foundStart + 1, line.length() - (foundStart + 2));
                temp = removeSpace(temp);
                finalStringVector->push_back(temp);
                break;
            }
            if (found != lastFound) {
                lastWord = line.substr(lastFound, found - lastFound);
                lastWord = removeSpace(lastWord);
                finalStringVector->push_back(lastWord);
            } else if (line[found] == '=') {
                lastWord = line.substr(lastFound + 1);
                lastWord = removeSpace(lastWord);
                // take all the line
                finalStringVector->push_back(lastWord);
                found = line.length() - 1;
            } else if (line[found] == '(') {
                found = line.find_first_of(')', found);
                lastWord = line.substr(lastFound, found - lastFound);
                lastWord = removeSpace(lastWord);
                finalStringVector->push_back(lastWord);
            }
            found += 1;
            lastFound = found;
            found = line.find_first_of(" ,()=\t", found);
        }
        if (lastFound != (line.length()) && (lastWord != "while") && (lastWord != "Print")) {
            string temp = line.substr(lastFound, line.length());
            temp = removeSpace(temp);
            finalStringVector->push_back(temp);
        }
    }
    //return the final vector
    return finalStringVector;
}

unordered_map<string, Command *> *firstMap() {
    unordered_map<string, Command *> *firstMapCommands = new unordered_map<string, Command *>{};
    // *** OpenServerCommand ***
    OpenServerCommand *openServerCommand = new OpenServerCommand();
    firstMapCommands->insert({"openDataServer", openServerCommand});
    // *** connectControlClientCommand ***
    ConnectCommand *connectCommand = new ConnectCommand();
    firstMapCommands->insert({"connectControlClient", connectCommand});
    // *** DefineVarCommand ***
    DefineVarCommand *defineVarCommand = new DefineVarCommand();
    firstMapCommands->insert({"var", defineVarCommand});
    // *** SleepCommand ***
    SleepCommand *sleepCommand = new SleepCommand();
    firstMapCommands->insert({"Sleep", sleepCommand});
    // *** PrintCommand ***
    PrintCommand *printCommand = new PrintCommand();
    firstMapCommands->insert({"Print", printCommand});
    // *** conditionParserCommand ***
    ConditionParser *conditionParser = new ConditionParser(firstMapCommands);
    firstMapCommands->insert({"while", conditionParser});
    firstMapCommands->insert({"if", conditionParser});
    return firstMapCommands;
}

/*
 *  get string and remove the spaces at the beginning and the end of the string
 */
string removeSpace(string str){
    while (str.at(0) == ' '){
        str = str.substr(1);
    }
    while (str.at(str.length() - 1) == ' '){
        str = str.substr(0, str.length() - 1);
    }
    return str;
}

