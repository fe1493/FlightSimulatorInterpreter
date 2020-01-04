//
// Created by yonatan on 26/12/2019.
//

#include "ConnectCommand.h"
#include "Var.h"
#include "Parser.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>

//declare static member
int ConnectCommand::client_socket;

// *** ConnectCommand execute ***
//function for sending the message
void *ConnectCommand::sendMessage(queue<string> *queueForUpdatingServer, bool *isClientConnect) {
    while (isClientConnect) {
        if (!queueForUpdatingServer->empty()) {
            string str = queueForUpdatingServer->front();
            const char *text = str.c_str();
            cout << text << endl;
            int is_sent = send(ConnectCommand::client_socket, text,
                               strlen(text), 0);
            if (is_sent == -1) {
                std::cout << "Error sending message" << std::endl;
            } else {
                std::cout << "set message sent to server" << std::endl;
            }
            queueForUpdatingServer->pop();
        }
    }
}

int ConnectCommand::connectClient(string *str, bool *isClientConnect, queue<string> *queue, OutputSymbolTable* outputSymbolTable) {
    //create socket
    ConnectCommand::client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (ConnectCommand::client_socket == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }
    string temp = to_string(Parser::checkExpression((str + 2), outputSymbolTable));
    int port = stoi(temp);
    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr("127.0.0.1");  //the localhost address
    address.sin_port = htons(port);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(ConnectCommand::client_socket, (struct sockaddr *) &address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server" << std::endl;
        return -2;
    } else {
        std::cout << "Client is now connected to server\n" << std::endl;
    }

    *isClientConnect = true;

    //function for opening a thread
    //if here we made a connection
    //make a function to send a message to the client, needs to get a socket, the queue which holds the simnames,
    ConnectCommand::sendMessage(queue, isClientConnect);

    close(ConnectCommand::client_socket);

}

int ConnectCommand::execute(string *str, class InputSymbolTable *inputSymbolTable,
                            class OutputSymbolTable *outputSymbolTable, queue<string> *queueForUpdatingServer) {
    return 3;
}
