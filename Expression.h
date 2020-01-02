//
// Created by Efraim Paley on 02/01/2020.
//

#ifndef PLEASEWORK_EXPRESSION_H
#define PLEASEWORK_EXPRESSION_H

#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <map>
#include <utility>
#include <regex>
#include "Command.h"

using namespace std;
class Expression
{

public:
    virtual double calculate() = 0;
    virtual ~Expression() {}
};

//Variable class
class Variable : public Expression{
private:
    string variableName;
    double variableValue;
public:
    //constructor
    Variable (string vName, double vValue);
    Variable& operator++();
    Variable& operator--();
    Variable& operator+=(double num);
    Variable& operator-=(double num);
    Variable& operator++(int num);
    Variable& operator--(int num);
    double calculate();
    ~Variable () {}
};

//binary class
class BinaryOperator : public Expression
{
protected:
    Expression *right;
    Expression *left;
public:
    virtual ~BinaryOperator()
    {
        delete right;
        delete left;
    }
};

class Plus : public BinaryOperator{
public:
    //constructor
    Plus (Expression* num1, Expression* num2);
    double calculate();
    ~Plus() {}


};

class Minus : public BinaryOperator{
public:
    //constructor
    Minus (Expression* num1, Expression* num2);
    double calculate();
    ~Minus() {}
};

class Mul : public BinaryOperator{
public:
    //constructor
    Mul (Expression* num1, Expression* num2);
    double calculate();
    ~Mul() {}

};

class Div : public BinaryOperator{
public:
    //constructor
    Div (Expression* num1, Expression* num2);
    double calculate();
    ~Div() {}

};

//Value Class
class Value : public Expression{
private:
    const double value;
public:
    Value (double val);
    double calculate();
    ~Value() {}

};

//Unary Classes

class UnaryOperator : public Expression {
protected:
    Expression *exp;
public:
    virtual ~UnaryOperator() {
        delete exp;
    }
};

class UPlus : public UnaryOperator {
public:
    UPlus (Expression* expression);
    double calculate();
    ~UPlus() {}



};

class UMinus : public UnaryOperator {
public:
    UMinus (Expression* expression);
    double calculate();
    ~UMinus() {}

};


//Interpreter class
class Interpreter {
private:
    map<string, double> variables;
//    map<string, double> temp;
    vector<string> splitString (string str, char delim);
    bool isANumber(string str);
    bool isValidVariable(string str);
    bool isCharachter(char c);
public:
    void setVariables (string variableToConvert, OutputSymbolTable* outputTable, InputSymbolTable* inputTable);
    Expression* interpret(string str,OutputSymbolTable* outputTable);
    vector<string> checkIfUnary(vector<string> str);
    bool checkIfThereIsSemicolon (string str);
    Expression* findAnswer(queue<string> q);
};



#endif //PLEASEWORK_EXPRESSION_H
