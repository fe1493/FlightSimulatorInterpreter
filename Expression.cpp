//
// Created by Efraim Paley on 02/01/2020.
//

#include "Expression.h"
#include "Command.h"
#include "InputSymbolTable.h"
#include "OutputSymbolTable.h"

using namespace std;

//variable class
//Constructor
Variable::Variable(string vName, double vValue) {
    this->variableName = vName;
    this->variableValue = vValue;
}

Variable &Variable::operator++() {
    this->variableValue++;
    return *this;
}

Variable &Variable::operator--() {
    this->variableValue--;
    return *this;
}

Variable &Variable::operator+=(double num1) {
    this->variableValue += num1;
    return *this;
}

Variable &Variable::operator-=(double num1) {
    this->variableValue -= num1;
    return *this;
}

Variable &Variable::operator++(int) {
    this->variableValue++;
    return *this;
}

Variable &Variable::operator--(int) {
    this->variableValue--;
    return *this;
}

double Variable::calculate() {
    return this->variableValue;
}


//Binary classes
Plus::Plus(Expression *num1, Expression *num2) {
    this->left = num1;
    this->right = num2;
}

double Plus::calculate() {
    {
        double result = this->left->calculate() + this->right->calculate();
        return result;
    }
}

Minus::Minus(Expression *num1, Expression *num2) {
    this->left = num1;
    this->right = num2;
}

double Minus::calculate() {
    {
        return (this->left->calculate() - this->right->calculate());
    }
}

Mul::Mul(Expression *num1, Expression *num2) {
    this->left = num1;
    this->right = num2;
}

double Mul::calculate() {
    {
        return (this->left->calculate() * this->right->calculate());
    }
}

Div::Div(Expression *num1, Expression *num2) {
    this->left = num1;
    this->right = num2;
}

double Div::calculate() {
    {
        if (this->right->calculate() == 0) {
            throw "Cant divide by zero";
        }
        return (this->left->calculate() / this->right->calculate());
    }
}


// Unary Class
UPlus::UPlus(Expression *expression) {
    this->exp = expression;
}

double UPlus::calculate() {
    return this->exp->calculate();
}

UMinus::UMinus(Expression *expression) {
    this->exp = expression;
}

double UMinus::calculate() {
    return -(exp->calculate());

}

// Value class
Value::Value(double val) : value(val) {
}

double Value::calculate() {
    return this->value;
}

//Interpreter class

//void Interpreter::setVariables(string str, OutputSymbolTable *outputTable, InputSymbolTable *inputTable) {
//    vector<string> variableAssignments;
//
//    if (str.empty()) {
//        throw "No assignment found!!";
//    }
////    bool thereIsASemicolon = checkIfThereIsSemicolon(str);
//    if (str =  )
//    {
//       // variableAssignments = splitString(str, ';');
//        for (string assignment : variableAssignments)
//        {
//            vector<string> result = splitString(assignment, '=');
//            if (result.size() != 2)
//            {
//                throw "Invalid assignment!!";
//            }
//
//            if (!isValidVariable(result[0]) || !isANumber(result[1]))
//            {
//                throw "Invalid input";
//            }
//            double val = stod(result[1]);
//            //auto itr = variables.find(val);
//            variables.insert(pair<string, double>(result[0], val));
//        }
//    }
//    else
//    {
//        vector<string> result = splitString(str, '=');
//        for (string assignment : result)
//        {
//
//            if (result.size() != 2)
//            {
//                throw "Invalid assignment!!";
//            }
//
//            if (!isValidVariable(result[0]) || !isANumber(result[1]))
//            {
//                throw "Invalid input";
//            }
//            double val = stod(result[1]);
//            //auto itr = variables.find(val);
//            variables[result[0]] = val;
//        }
//    }
//}

//bool Interpreter::checkIfThereIsSemicolon(string str)
//{
//    for (char c : str)
//    {
//        if (c == ';')
//        {
//            return true;
//        }
//    }
//    return false;
//}

//bool Interpreter::isValidVariable(string str)
//{
//    if (str.empty() || !isCharachter(str[0]) || str[str.length() - 1] == '_')
//    {
//        return false;
//    }
//
//    for (char c : str)
//    {
//        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || (c <= '9' && c >= '0')))
//        {
//            return false;
//        }
//    }
//    return true;
//}
//
//bool Interpreter::isCharachter(char c)
//{
//    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
//
//}
//
//
//vector<string> Interpreter::splitString(string str, char delim)
//{
//    unsigned long start = 0, end;
//    vector<string> result;
//    while((end = str.find(delim, start)) != string :: npos)
//    {
//        result.push_back(str.substr(start, end - start));
//        // end plus length of delimiter
//        start = end + 1;
//    }
//    result.push_back(str.substr(start));
//    return result;
//}


Expression *Interpreter::interpret(string str, OutputSymbolTable *outputTable) {
    queue<string> myQueue;
    vector<string> stringOfOperators;
    vector<string> temp;
    stack<string> myStack;
    unsigned long last = 0;

    // Assignment of variables
    string stringWithValues = str;
    for (pair<string, Var *> pair : *outputTable->outputMap) {
        stringWithValues = regex_replace(stringWithValues, regex(pair.first), to_string(pair.second->value));
    }

    unsigned long find = stringWithValues.find_first_of("+-*/()_");
    while (find != string::npos) {
        if (find != last) {
            temp.push_back(stringWithValues.substr(last, find - last));
        }
        temp.push_back(stringWithValues.substr(find, 1));
        find++;
        last = find;
        find = stringWithValues.find_first_of("+-*/()_", find);
    }

    if (last != stringWithValues.length()) {
        temp.push_back(stringWithValues.substr(last, stringWithValues.length()));
    }
    stringOfOperators = checkIfUnary(temp);
    for (unsigned long i = 0; i < stringOfOperators.size(); i++) {
        if (stringOfOperators[i] == "#" || stringOfOperators[i] == "%") {
            myStack.push(stringOfOperators[i]);
            continue;
        }
        if (stringOfOperators[i] == "*") {
            if (myStack.empty()) {
                myStack.push(stringOfOperators[i]);
                continue;
            }
            if (myStack.top() == "%" || myStack.top() == "#") {
                myQueue.push(myStack.top());
                myStack.pop();
            }
            if (!myStack.empty()) {
                if (myStack.top() == "*" || myStack.top() == "+" || myStack.top() == "-" || myStack.top() == "/") {
                    throw "Cant Have 2 operations in a row without parentheses- Illegal Math equation";
                }
            }
            myStack.push("*");
        } else if (stringOfOperators[i] == "/") {
            if (myStack.empty()) {
                myStack.push(stringOfOperators[i]);
                continue;
            }
            if (myStack.top() == "%" || myStack.top() == "#") {
                myQueue.push(myStack.top());
                myStack.pop();
            }
            if (myStack.top() == "*" || myStack.top() == "+" || myStack.top() == "-" || myStack.top() == "/") {
                throw "Cant Have 2 operations in a row without parentheses- Illegal Math equation";
            }
            while (myStack.top() == "*") {
                if (myStack.empty()) {
                    break;
                }
                myQueue.push(myStack.top());
                myStack.pop();

            }
            myStack.push(stringOfOperators[i]);
        } else if (stringOfOperators[i] == "+") {
            if (myStack.empty()) {
                myStack.push(stringOfOperators[i]);
                continue;
            }
            if (myStack.top() == "%" || myStack.top() == "#") {
                myQueue.push(myStack.top());
                myStack.pop();
            }
            if (!myStack.empty()) {
                if (myStack.top() == "+") {
                    throw "Cant Have 2 Additions in a row- Illegal Math equation";
                }
                while (myStack.top() == "*" || myStack.top() == "/") {
                    if (myStack.empty()) {
                        break;
                    }
                    myQueue.push(myStack.top());
                    myStack.pop();
                }
            }
            myStack.push(stringOfOperators[i]);
        } else if (stringOfOperators[i] == "-") {
            if (myStack.empty()) {
                myStack.push(stringOfOperators[i]);
                continue;
            }
            if (myStack.top() == "%" || myStack.top() == "#") {
                myQueue.push(myStack.top());
                myStack.pop();
            }

            while (myStack.top() == "*" || myStack.top() == "/" || myStack.top() == "+") {
                if (myStack.empty()) {
                    break;
                }
                myQueue.push(myStack.top());
                myStack.pop();
            }
            myStack.push(stringOfOperators[i]);
        } else if (stringOfOperators[i] == "(") {
            if (myStack.empty()) {
                myStack.push(stringOfOperators[i]);
                continue;
            }
            myStack.push(stringOfOperators[i]);
            while (myStack.top() != "(") {
                if (myStack.top() == "%" || myStack.top() == "#") {
                    if (myQueue.empty()) {
                        myStack.push(stringOfOperators[i]);
                        continue;
                    }
                    myQueue.push(myStack.top());
                    myStack.pop();
                }
                if (myStack.empty()) {
                    throw "Missing Parenthesis";
                }
                if (myStack.top() == ")") {
                    myStack.pop();
                }
                myQueue.push(myStack.top());
                myStack.pop();
            }
            //               myStack.push(stringOfOperators[i]);
        } else if (stringOfOperators[i] == ")") {
            while (myStack.top() != "(") {
                if (myStack.empty()) {
                    throw "Empty stack";
                }
                if (myStack.top() == ")") {
                    myStack.pop();
                }
                myQueue.push(myStack.top());
                myStack.pop();
                continue;
            }
            myStack.pop();
        } else if (isANumber(stringOfOperators[i])) {
            myQueue.push(stringOfOperators[i]);
        } else {
            throw "Invalid Symbol";
        }
    }
    while (!myStack.empty()) {
        if (myStack.top() == "(" || myStack.top() == ")") {
            myStack.pop();
            continue;
        }
        if (!myStack.empty()) {
            myQueue.push(myStack.top());
            myStack.pop();
        }
    }
    Expression *resultOfExpression = findAnswer(myQueue);
    return resultOfExpression;
}

vector<string> Interpreter::checkIfUnary(vector<string> str) {
    if (str[0] == "+") {
        str[0] = "#";
    }
    if (str[0] == "-") {
        str[0] = "%";
    }
    for (unsigned long i = 0; i < str.size(); i++) {
        if (str[i] == "+" && !isANumber(str[i - 1])) {
            str[i] = "#";
        }
        if (str[i] == "-" && !isANumber(str[i - 1])) {
            str[i] = "%";
        }
    }
    return str;
}

Expression *Interpreter::findAnswer(queue<string> queue) {
    stack<Expression *> expStack;
    Expression *right = nullptr;
    Expression *left = nullptr;
    Expression *result = nullptr;
    //if we read a digit
    while (!queue.empty()) {
        if (isANumber(queue.front())) {
            expStack.push(new Value(stod(queue.front())));
            queue.pop();
        } else if (queue.front() == "%") {
            if (!expStack.empty()) {
                Expression *val = expStack.top();
                expStack.pop();
                expStack.push(new UMinus(val));
                queue.pop();
            } else {
                throw "Missing digit to put unary on";
            }
        } else if (queue.front() == "#") {
            Expression *val = expStack.top();
            expStack.pop();
            expStack.push(new UPlus(val));
            queue.pop();
        } else if (queue.front() == "*") {
            if (expStack.empty()) {
                throw "Error - Stack cant be empty";
            } else {
                right = expStack.top();
                expStack.pop();
                left = expStack.top();
                expStack.pop();
            }
            expStack.push(new Mul(left, right));
            queue.pop();
        } else if (queue.front() == "/") {
            if (expStack.empty()) {
                throw "Error - Stack cant be empty";
            } else {
                right = expStack.top();
                expStack.pop();
                left = expStack.top();
                expStack.pop();
            }
            expStack.push(new Div(left, right));
            queue.pop();
        } else if (queue.front() == "+") {
            if (expStack.empty()) {
                throw "Error - Stack cant be empty";
            } else {
                right = expStack.top();
                expStack.pop();
                left = expStack.top();
                expStack.pop();
            }
            expStack.push(new Plus(left, right));
            queue.pop();
        } else if (queue.front() == "-") {
            if (expStack.empty()) {
                throw "Error - Stack cant be empty";
            } else {
                right = expStack.top();
                expStack.pop();
                left = expStack.top();
                expStack.pop();
            }
            expStack.push(new Minus(left, right));
            queue.pop();
        }
    }
    result = expStack.top();
    while (!expStack.empty()) {
        expStack.pop();
    }
    return result;
}

bool Interpreter::isANumber(string str) {
    for (char c : str) {
        if (!isdigit(c) && c != '.') {
            return false;
        }
    }
    return true;
}