//
// Created by Efraim Paley on 02/01/2020.
//

#include "Expression.h"
#include "Command.h"
#include "InputSymbolTable.h"
#include "OutputSymbolTable.h"

using namespace std;

string removeSpaces(string str);

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
///
//*Calcualtes the variable*
/// \return
double Variable::calculate() {
    return this->variableValue;
}


//Binary classes
//Plus Constructor
Plus::Plus(Expression *num1, Expression *num2) {
    this->left = num1;
    this->right = num2;
}


///
//*Calcualtes the plus expression*
/// \return
double Plus::calculate() {
    {
        double result = this->left->calculate() + this->right->calculate();
        return result;
    }
}


//Minus Constructor

Minus::Minus(Expression *num1, Expression *num2) {
    this->left = num1;
    this->right = num2;
}


///
//*Calcualtes the minus expression*
/// \return
double Minus::calculate() {
    {
        return (this->left->calculate() - this->right->calculate());
    }
}

//Mul Constructor

Mul::Mul(Expression *num1, Expression *num2) {
    this->left = num1;
    this->right = num2;
}


///
//*Calcualtes the Mul expression*
/// \return
double Mul::calculate() {
    {
        return (this->left->calculate() * this->right->calculate());
    }
}

//Div Constructor

Div::Div(Expression *num1, Expression *num2) {
    this->left = num1;
    this->right = num2;
}


///
//*Calcualtes the Div expression*
/// \return
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
/// *erases the spaces in a string*
/// \param input- the string to remove the spaces
/// \return the string without spaces
string removeSpaces(string input)
{
    for (int i = input.size()-1; i >= 0; --i) {
        if(input[i] == ' ')
            input.erase(i, 1);
    }
    return input;
}

/// *the function interprets the expression we get using the shunting yard algorithm*
/// \param str - the string that we need to interpret
/// \param outputTable -- the values in the output table we are working with
/// \return the interperted expression
Expression *Interpreter::interpret(string str, OutputSymbolTable *outputTable)
{
    queue<string> myQueue;
    vector<string> stringOfOperators;
    vector<string> temp;
    stack<string> myStack;
    unsigned long last = 0;

    // Assignment of variables
    string stringWithValues = str;
    for (pair<string, Var *> pair : *outputTable->outputMap)
    {
        stringWithValues = regex_replace(stringWithValues, regex(pair.first), pair.second->value);
    }
    // remove spaces
    stringWithValues = removeSpaces(stringWithValues);
    unsigned long find = stringWithValues.find_first_of("+-*/()_");
    //organize the string
    while (find != string::npos)
    {
        if (find != last)
        {
            temp.push_back(stringWithValues.substr(last, find - last));
        }
        temp.push_back(stringWithValues.substr(find, 1));
        find++;
        last = find;
        find = stringWithValues.find_first_of("+-*/()_", find);
    }

    if (last != stringWithValues.length())
    {
        temp.push_back(stringWithValues.substr(last, stringWithValues.length()));
    }
    //check if there are any unary operators in the string
    stringOfOperators = checkIfUnary(temp);

    //shunting yard algorithm
    for (unsigned long i = 0; i < stringOfOperators.size(); i++)
    {
        //unary operators
        if (stringOfOperators[i] == "#" || stringOfOperators[i] == "%")
        {
            myStack.push(stringOfOperators[i]);
            continue;
        }
        //multiplication
        if (stringOfOperators[i] == "*")
        {
            if (myStack.empty())
            {
                myStack.push(stringOfOperators[i]);
                continue;
            }
            if (myStack.top() == "%" || myStack.top() == "#")
            {
                myQueue.push(myStack.top());
                myStack.pop();
            }
            if (!myStack.empty())
            {
                if (myStack.top() == "*" || myStack.top() == "+" || myStack.top() == "-" || myStack.top() == "/")
                {
                    throw "Cant Have 2 operations in a row without parentheses- Illegal Math equation";
                }
            }
            myStack.push("*");
        }
        //division
        else if (stringOfOperators[i] == "/")
        {
            if (myStack.empty())
            {
                myStack.push(stringOfOperators[i]);
                continue;
            }
            if (myStack.top() == "%" || myStack.top() == "#")
            {
                myQueue.push(myStack.top());
                myStack.pop();
            }
            if (myStack.top() == "*" || myStack.top() == "+" || myStack.top() == "-" || myStack.top() == "/")
            {
                throw "Cant Have 2 operations in a row without parentheses- Illegal Math equation";
            }
            while (myStack.top() == "*")
            {
                if (myStack.empty())
                {
                    break;
                }
                myQueue.push(myStack.top());
                myStack.pop();

            }
            myStack.push(stringOfOperators[i]);
        }
        //addition
        else if (stringOfOperators[i] == "+")
        {
            if (myStack.empty())
            {
                myStack.push(stringOfOperators[i]);
                continue;
            }
            //take out unary operators and put in queue
            if (myStack.top() == "%" || myStack.top() == "#")
            {
                myQueue.push(myStack.top());
                myStack.pop();
            }
            if (!myStack.empty())
            {

                //take out stronger operators and put in queue
                while (myStack.top() == "*" || myStack.top() == "/" || myStack.top() == "-")
                {
                    if (myStack.empty())
                    {
                        break;
                    }
                    myQueue.push(myStack.top());
                    myStack.pop();

                    if (myStack.empty())
                    {
                        break;
                    }
                }
            }
            //push into stack
            myStack.push(stringOfOperators[i]);
        }
        //subtraction
        else if (stringOfOperators[i] == "-")
        {
            if (myStack.empty())
            {
                myStack.push(stringOfOperators[i]);
                continue;
            }
            //take out unary operators and put in queue
            if (myStack.top() == "%" || myStack.top() == "#")
            {
                myQueue.push(myStack.top());
                myStack.pop();
            }
            //take out stronger operators and put in queue
            while ((myStack.top() == "*" || myStack.top() == "/" ||  myStack.top() == "+"))
            {
                if (myStack.empty())
                {
                    break;
                }
                myQueue.push(myStack.top());
                myStack.pop();
                if (myStack.empty())
                {
                    break;
                }
            }
            //push into stack
            myStack.push(stringOfOperators[i]);
        }
        //left parentheses
        else if (stringOfOperators[i] == "(")
        {
            if (myStack.empty())
            {
                myStack.push(stringOfOperators[i]);
                continue;
            }
            myStack.push(stringOfOperators[i]);
            while (myStack.top() != "(")
            {
                if (myStack.top() == "%" || myStack.top() == "#")
                {
                    if (myQueue.empty())
                    {
                        myStack.push(stringOfOperators[i]);
                        continue;
                    }
                    myQueue.push(myStack.top());
                    myStack.pop();
                }
                if (myStack.empty())
                {
                    throw "Missing Parenthesis";
                }
                if (myStack.top() == ")")
                {
                    myStack.pop();
                }
                myQueue.push(myStack.top());
                myStack.pop();
            }
        }
        //right parentheses
        else if (stringOfOperators[i] == ")")
        {
            while (myStack.top() != "(")
            {
                if (myStack.empty())
                {
                    throw "Empty stack";
                }
                if (myStack.top() == ")")
                {
                    myStack.pop();
                }
                myQueue.push(myStack.top());
                myStack.pop();
                continue;
            }
            myStack.pop();
        }
        //if we read a number
        else if (isANumber(stringOfOperators[i]))
        {
            myQueue.push(stringOfOperators[i]);
        }
        else
        {
            throw "Invalid Symbol";
        }
    }
    //empty the stack
    while (!myStack.empty())
    {
        if (myStack.top() == "(" || myStack.top() == ")")
        {
            myStack.pop();
            continue;
        }
        if (!myStack.empty())
        {
            myQueue.push(myStack.top());
            myStack.pop();
        }
    }
    //get expression
    Expression *resultOfExpression = findAnswer(myQueue);
    return resultOfExpression;
}

/// *checks if there are unary operators*
/// \param str -string of operators which we check if there are any unary operators
/// \return -- the string with the unary operators
vector<string> Interpreter::checkIfUnary(vector<string> str)
{
    //if unary plus
    if (str[0] == "+")
    {
        str[0] = "#";
    }
    //if unary minus
    if (str[0] == "-")
    {
        str[0] = "%";
    }
    for (unsigned long i = 0; i < str.size(); i++)
    {
        //check for unary plus
        if (str[i] == "+" && !isANumber(str[i - 1]))
        {
            str[i] = "#";
        }
        //check for unary minus
        if (str[i] == "-" && !isANumber(str[i - 1]))
        {
            str[i] = "%";
        }
    }
    return str;
}

/// *the function that calcualtes the expression of the answer to our equation*
/// \param queue --the queue that holds the equation after the shunting yard algorithm
/// \return --the answer of the equatiomn which is an expression
Expression *Interpreter::findAnswer(queue<string> queue)
{
    stack<Expression *> expStack;
    Expression *right = nullptr;
    Expression *left = nullptr;
    Expression *result = nullptr;
    //if we read a digit
    while (!queue.empty())
    {
        if (isANumber(queue.front()))
        {
            expStack.push(new Value(stod(queue.front())));
            queue.pop();
        }
        //if unary mimus
        else if (queue.front() == "%")
        {
            if (!expStack.empty())
            {
                Expression *val = expStack.top();
                expStack.pop();
                expStack.push(new UMinus(val));
                queue.pop();
            }
            else
            {
                throw "Missing digit to put unary on";
            }
        }
        //if unary plus
        else if (queue.front() == "#")
        {
            Expression *val = expStack.top();
            expStack.pop();
            expStack.push(new UPlus(val));
            queue.pop();
        }
        //if mult
        else if (queue.front() == "*")
        {
            if (expStack.empty())
            {
                throw "Error - Stack cant be empty";
            }
            else
            {
                right = expStack.top();
                expStack.pop();
                left = expStack.top();
                expStack.pop();
            }
            expStack.push(new Mul(left, right));
            queue.pop();
        }
        //if div
        else if (queue.front() == "/")
        {
            if (expStack.empty())
            {
                throw "Error - Stack cant be empty";
            }
            else
            {
                right = expStack.top();
                expStack.pop();
                left = expStack.top();
                expStack.pop();
            }
            expStack.push(new Div(left, right));
            queue.pop();
        }
        //if plus
        else if (queue.front() == "+")
        {
            if (expStack.empty())
            {
                throw "Error - Stack cant be empty";
            }
            else
            {
                right = expStack.top();
                expStack.pop();
                left = expStack.top();
                expStack.pop();
            }
            expStack.push(new Plus(left, right));
            queue.pop();
        }
        //if minus
        else if (queue.front() == "-")
        {
            if (expStack.empty())
            {
                throw "Error - Stack cant be empty";
            }
            else
            {
                right = expStack.top();
                expStack.pop();
                left = expStack.top();
                expStack.pop();
            }
            expStack.push(new Minus(left, right));
            queue.pop();
        }
    }
    //the result
    result = expStack.top();
    //empty stack
    while (!expStack.empty())
    {
        expStack.pop();
    }
    return result;
}
/// *checks if the string is a number*
/// \param str --the string which we check if it is a number
/// \return
bool Interpreter::isANumber(string str) {
    for (char c : str) {
        if (!isdigit(c) && c != '.') {
            return false;
        }
    }
    return true;
}