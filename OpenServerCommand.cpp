//
// Created by Efraim Paley on 26/12/2019.
//

#include "OpenServerCommand.h"
#include "Var.h"
#include "Parser.h"
#include <iostream>
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

vector<string> *createSimArray();

vector<double> *createValArray(char buffer);

int isNum(const string &num);

// *** OpenServerCommand execute ***

int OpenServerCommand::execute(string *str, InputSymbolTable *inputSymbolTable,
                               OutputSymbolTable *outputSymbolTable, queue<string> *queueForUpdatingServer) {
    return 2;
}

int OpenServerCommand::openServer(string *str, bool *isConnect, InputSymbolTable *input, OutputSymbolTable* outputSymbolTable) {

    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }
    string temp = to_string(Parser::checkExpression((str + 1), outputSymbolTable));
    int port = stoi(temp);
    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (::bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        return -2;
    }
    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
        return -3;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }

    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *) &address,
                               (socklen_t *) &address);

    if (client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
        return -4;
    }

    close(socketfd); //closing the listening socket

    //reading from client and print the input
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1024);
    std::cout << buffer << std::endl;
    // the index of the var in the simArray
    int indexVar = 0;
    // create an array with the simulators keys, according to the xml order
    vector<string> *simArray = createSimArray();
    // update the SIM FIELD of every variable at input SYMBOLE TABLE
    for (int i = 0; i < simArray->size(); i++) {
        input->inputMap->at(simArray->at(i))->simName = simArray->at(i);
    }
    string val = "";
    for (char c: buffer) {
        if (c == ',') {
            input->inputMap->at(simArray->at(indexVar))->value = val;
            val = "";
            indexVar++;
        } else if (c == '\n') {
            input->inputMap->at(simArray->at(indexVar))->value = val;
            val = "";
            // end of block. reset the index to next block.
            indexVar = 0;
        } else {
            // create the value
            val += c;
        }
    }

    // let MAIN go on
    *isConnect = true;
    val = "";
    // keep get values from the simulator
    while (isConnect) {
        //buffer[1024] = {0};
        valread = read(client_socket, buffer, 1024);
        // *** here we need to put all the value into the symbol table. ***
        // we need to use the xml file the know which variable belongs to value
        std::cout << buffer << std::endl;
        indexVar = 0;
        for (char c: buffer) {
            if (c == ',') {
                input->inputMap->at(simArray->at(indexVar))->value = val;
                val = "";
                indexVar++;
            } else if (c == '\n') {
                input->inputMap->at(simArray->at(indexVar))->value = val;
                val = "";
                // end of block. reset the index to next block.
                indexVar = 0;
            } else if (c == '\000') {
                break;
            } else {
                // create the value
                val += c;
            }
        }
    }
}

vector<string> *createSimArray() {
    vector<string> *simArray = new vector<string>{};
    simArray->push_back("/instrumentation/airspeed-indicator/indicated-speed-kt");
    simArray->push_back("/sim/time/warp");
    simArray->push_back("/controls/switches/magnetos");
    simArray->push_back("/instrumentation/heading-indicator/offset-deg");
    simArray->push_back("/instrumentation/altimeter/indicated-altitude-ft");
    simArray->push_back("/instrumentation/altimeter/pressure-alt-ft");
    simArray->push_back("/instrumentation/attitude-indicator/indicated-pitch-deg");
    simArray->push_back("/instrumentation/attitude-indicator/indicated-roll-deg");
    simArray->push_back("/instrumentation/attitude-indicator/internal-pitch-deg");
    simArray->push_back("/instrumentation/attitude-indicator/internal-roll-deg");
    simArray->push_back("/instrumentation/encoder/indicated-altitude-ft");
    simArray->push_back("/instrumentation/encoder/pressure-alt-ft");
    simArray->push_back("/instrumentation/gps/indicated-altitude-ft");
    simArray->push_back("/instrumentation/gps/indicated-ground-speed-kt");
    simArray->push_back("/instrumentation/gps/indicated-vertical-speed");
    simArray->push_back("/instrumentation/heading-indicator/indicated-heading-deg");
    simArray->push_back("/instrumentation/magnetic-compass/indicated-heading-deg");
    simArray->push_back("/instrumentation/slip-skid-ball/indicated-slip-skid");
    simArray->push_back("/instrumentation/turn-indicator/indicated-turn-rate");
    simArray->push_back("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
    simArray->push_back("/controls/flight/aileron");
    simArray->push_back("/controls/flight/elevator");
    simArray->push_back("/controls/flight/rudder");
    simArray->push_back("/controls/flight/flaps");
    simArray->push_back("/controls/engines/engine/throttle");
    simArray->push_back("/controls/engines/current-engine/throttle");
    simArray->push_back("/controls/switches/master-avionics");
    simArray->push_back("/controls/switches/starter");
    simArray->push_back("/engines/active-engine/auto-start");
    simArray->push_back("/controls/flight/speedbrake");
    simArray->push_back("/sim/model/c172p/brake-parking");
    simArray->push_back("/controls/engines/engine/primer");
    simArray->push_back("/controls/engines/current-engine/mixture");
    simArray->push_back("/controls/switches/master-bat");
    simArray->push_back("/controls/switches/master-alt");
    simArray->push_back("/engines/engine/rpm");
    return simArray;
}

int isNum(const string &num) {
    int points = 0;
    for (size_t i = 0; i < num.length(); i++) {
        if (num[i] == '.') {
            points++;
        } else if (!isdigit(num[i])) {
            return false;
        }
    }
    if (points > 1) {
        return false;
    } else {
        return true;
    }
}



