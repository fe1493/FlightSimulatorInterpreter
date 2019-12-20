#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <unordered_map>
#include "Command.cpp"
using namespace std;

vector<string> Lexer(const string& file);
//unordered_map<string, Command> Parser(vector<string> vector);

int main(int argc, char *argv[]) {
    // read from file
    // get a string array of all the words from the file
    // parser
    // make new objects
    //
    vector<string> finalStringVector;
//    map<string, Command>  stringToCommands;
    finalStringVector = Lexer(argv[1]);
//    stringToCommands = Parser(finalStringVector);
    auto *test = new DefineVarCommand;
    test->execute(&finalStringVector[5]) ;
}

vector<string> Lexer(const string& fileName)
{
    //the file that we will read into
    ifstream myFile;
    myFile.open(fileName);
    if (myFile.fail())
    { // error check,
        cout << "ERROR OPENING FILE" << endl;
        exit(1);
    }

    vector<string> finalStringVector;
    string line;
    //go over each line
    while (getline(myFile, line))
    {
        //code from EX1
        unsigned long int found = line.find_first_of(" ,()=\t");
        unsigned long int lastFound = 0;
        string lastWord;

        while (found != string::npos)
        {
            // case 1: while. insert the condition to the next token
            if (lastWord == "while")
            {
                // line - 6 = all the line except the "while" and "{"
                finalStringVector.push_back(line.substr(lastFound, line.length() - 6));
                break;
            }
            // case 2: Print. insert the text to the next token
            if (lastWord == "Print")
            {
                // line - 7 = all the line except the "Print" and ")" in the end of the line
                finalStringVector.push_back(line.substr(lastFound, line.length() - 7));
                break;
            }
            if (found != lastFound)
            {
                lastWord = line.substr(lastFound, found - lastFound);
                finalStringVector.push_back(lastWord);
            }
            else if (line[found] == '=')
            {
                lastWord = line.substr(lastFound + 1);
                // take all the line
                finalStringVector.push_back(lastWord);
                found = line.length() - 1;
            }
            else if (line[found] == '(')
            {
                found = line.find_first_of(')', found);
                lastWord = line.substr(lastFound, found - lastFound);
                finalStringVector.push_back(lastWord);
            }
            found += 1;
            lastFound = found;
            found = line.find_first_of(" ,()=\t", found);
        }
        if (lastFound != (line.length()) && (lastWord != "while") && (lastWord != "Print"))
        {
            finalStringVector.push_back(line.substr(lastFound, line.length()));
        }
    }
//return the final vector
    return finalStringVector;
}

unordered_map<string, Command*> firstMap()
{
    unordered_map<string, Command*> map{};




}


