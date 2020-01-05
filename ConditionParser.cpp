//
// Created by yonatan on 02/01/2020.
//

#include <algorithm>
#include "ConditionParser.h"
#include "Parser.h"

vector<string> *copyCommands(string *str, int *index);
bool checkCondition(string str, OutputSymbolTable outputSymbolTable);
string removeSpace2(string str);

int ConditionParser::execute(string *str, InputSymbolTable *inputSymbolTable,
                             OutputSymbolTable *outputSymbolTable, queue<string> *queueForUpdatingServer) {
    // we calculate the jump at conditionVector function
    int jump = 3;
    // copy all lines of the block (until you get '}')
    vector<string> *conditionVector = copyCommands(str + 2, &jump);
    if (*str == "while") {
        // check the condition, if true - start a new Parser for that while
        while (checkCondition(*(str + 1), *outputSymbolTable)) {
            int index = 0;
            string commandName = conditionVector->at(index);
            Command* c = nullptr;
            while(index < conditionVector->size()){
                if (firstMapCommands->find(conditionVector->at(index)) != firstMapCommands->end())
                {
                    c = firstMapCommands->at(conditionVector->at(index));
                }
                    // check if the key is a Var in the output Map
                else if (outputSymbolTable->outputMap->find(conditionVector->at(index)) != outputSymbolTable->outputMap->end())
                {
                    c = outputSymbolTable->outputMap->at(conditionVector->at(index));
                }
                try{
                    index += c->execute(&conditionVector->at(index), inputSymbolTable,
                                        outputSymbolTable, queueForUpdatingServer);
                }
                catch(const char* e){
                    throw ("unknown Command");
                }
            }
        }
    } else if (*str == "if") {
        // check the condition, if true - start a new Parser for that 'if'
        if (checkCondition(*(str + 1), *outputSymbolTable)){
            int index = 0;
            string commandName = conditionVector->at(index);
            Command* c = nullptr;
            while(index < conditionVector->size()){
                if (firstMapCommands->find(conditionVector->at(index)) != firstMapCommands->end())
                {
                    c = firstMapCommands->at(conditionVector->at(index));
                }
                    // check if the key is a Var in the output Map
                else if (outputSymbolTable->outputMap->find(conditionVector->at(index)) != outputSymbolTable->outputMap->end())
                {
                    c = outputSymbolTable->outputMap->at(conditionVector->at(index));
                }
                try{
                    index += c->execute(&conditionVector->at(index), inputSymbolTable,
                                        outputSymbolTable, queueForUpdatingServer);
                }
                catch(const char* e){
                    throw ("unknown Command");
                }
            }
        }
    }
    return jump;
}

vector<string> *copyCommands(string *str, int *jump) {
    auto *conditionVector = new vector<string>{};
    while (*str != "}") {
        conditionVector->push_back(*str);
        *jump = *jump + 1;
        str++;
    }
    return conditionVector;
}

/*
 * checkCondition - check the condition of the while/if
 */
bool checkCondition(string str, OutputSymbolTable outputSymbolTable){
    // find the first char of the operator
    unsigned long int found = str.find_first_of("><=!");
    // assignment of the first value (left in the condition)
    string val1 = str.substr(0, found);
    string val2;
    // assignment of the operator (middle in the condition)
    string oper = "";
    oper += str.at(found);
    // check if the operator consist 2 char
    found++;
    unsigned long int found2 = str.find_first_of("<>=!", found);
    // if the operator consist 2 char, update the operator
    if (found2 != string::npos){
        oper += str.at(found2);
        val2 = str.substr(found2 + 1);
    } else {
        found2 = str.find_first_of("<>=!");
        val2 = str.substr(found2 + 1);
    }
    val2 = val2.substr(0, val2.length() - 1);
    // remove the spaces at the strings
    val1 = removeSpace2(val1);
    val2 = removeSpace2(val2);
    oper = removeSpace2(oper);
    // calculate evary val
    double final1 = Parser::checkExpression(&val1, &outputSymbolTable);
    double final2 = Parser::checkExpression(&val2, &outputSymbolTable);;
    // switch according to the oper
    if (oper == "=="){
        if (final1 == final2){
            return true;
        }
        return false;
    }
    if (oper == ">"){
        if (final1 > final2){
            return true;
        }
        return false;
    }
    if (oper == "<"){
        if (final1 < final2){
            return true;
        }
        return false;
    }
    if (oper == ">="){
        if (final1 >= final2){
            return true;
        }
        return false;
    }
    if (oper == "<="){
        if (final1 <= final2){
            return true;
        }
        return false;
    }
    if (oper == "!="){
        if (final1 != final2){
            return true;
        }
        return false;
    }
}
/*
 *  get string and remove the spaces at the beginning and the end of the string
 */
string removeSpace2(string str){
    while (str.at(0) == ' '){
        str = str.substr(1);
    }
    while (str.at(str.length() - 1) == ' '){
        str = str.substr(0, str.length() - 1);
    }
    return str;
}