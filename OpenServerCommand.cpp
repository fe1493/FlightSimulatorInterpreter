//
// Created by Efraim Paley on 26/12/2019.
//

#include "OpenServerCommand.h"
#include "Var.h"
#include <iostream>
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

// *** OpenServerCommand execute ***

int OpenServerCommand::execute(string *str, InputSymbolTable* inputSymbolTable,
                               OutputSymbolTable* outputSymbolTable) {
    return 2;
}

int OpenServerCommand::openServer(string *str, bool *isConnect, InputSymbolTable *input) {

    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }
    int port = stoi(*(str + 1));
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

    //reading from client
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1024);
    std::cout << buffer << std::endl;

    *isConnect = true;

    while (isConnect) {
        buffer[1024] = {0};
        valread = read(client_socket, buffer, 1024);
        // *** here we need to put all the value into the symbol table. ***
        // we need to use the xml file the know which variable belongs to value
        std::cout << buffer << std::endl;
    }
}

