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

///
//  *function for sending the message to the  client server*

/// \param queueForUpdatingServer - queue which holds the strings that we need to send to the server in order to change the values
/// \param isClientConnect -- tells us how long to connect to the client
/// \return

void *ConnectCommand::sendMessage(queue<string> *queueForUpdatingServer, bool *isClientConnect) {
    while (isClientConnect) {

        if (!queueForUpdatingServer->empty()) {
            string str = queueForUpdatingServer->front();
            //convert the string to char*
            const char *text = str.c_str();
            cout << text << endl;
            //send to the server
            int is_sent = send(ConnectCommand::client_socket, text,
                               strlen(text), 0);
            if (is_sent == -1) {
                std::cout << "Error sending message" << std::endl;
            } else {
                std::cout << "set message sent to server" << std::endl;
            }
            //pop the message we just sent
            queueForUpdatingServer->pop();
        }
    }
}

///
//  *function to connect to the client*

/// \param str - string of the commands
/// \param isClientConnect -- tells us how long to connect to the client
/// \param queueForUpdatingServer - queue which holds the strings that we need to send to the server in order to change the values
/// \param outputSymbolTable - table with all of the out info
/// \return
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

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(ConnectCommand::client_socket, (struct sockaddr *) &address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server" << std::endl;
        return -2;
    } else {
        std::cout << "Client is now connected to server\n" << std::endl;
    }

    *isClientConnect = true;

    //function for opening sending a message if here we made a connection
    ConnectCommand::sendMessage(queue, isClientConnect);

    //close the socket
    close(ConnectCommand::client_socket);

}

///
// *The execute for the ConnectCommand*

/// \param str - string of the commands
/// \param inputSymbolTable - table with all of the inputed info
/// \param outputSymbolTable - table with all of the out info
/// \param queueForUpdatingServer - queue which holds the strings that we need to send to the server in order to change the values
/// \return How many spaces need to jump in the parser

int ConnectCommand::execute(string *str, class InputSymbolTable *inputSymbolTable,
                            class OutputSymbolTable *outputSymbolTable, queue<string> *queueForUpdatingServer) {
    return 3;
}
