

#include <iostream>

#include <thread>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include "Command.h"
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// *** Print Command ***
int PrintCommand::execute(string *str, unordered_map<string, Command *> *input,
                          unordered_map<string, Command *> *output) {
    cout << str << endl;
    return 1;
}

// *** SleepCommand execute ***
int SleepCommand::execute(string *str, unordered_map<string, Command *> *input,
                          unordered_map<string, Command *> *output) {
    this_thread::sleep_for(timeSpan);
    return 1;
}

// *** OpenServerCommand execute ***

int OpenServerCommand::execute(string *str, unordered_map<string, Command *> *input,
                               unordered_map<string, Command *> *output) {
    return 2;
}

int OpenServerCommand::openServer(string *str, bool* isConnect) {

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
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
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
    int valread = read( client_socket , buffer, 1024);
    std::cout<<buffer<<std::endl;

    *isConnect = true;

    while (isConnect){
        buffer[1024] = {0};
        valread = read( client_socket , buffer, 1024);

        // *** here we need to put all the value into the symbol table. ***
        // we need to use the xml file the know which variable belongs to value

        std::cout<<buffer<<std::endl;
    }
    //writing back to client
    char *hello = "Hello, I can hear you! \n";
    send(client_socket , hello , strlen(hello) , 0 );
    std::cout<<"Hello message sent\n"<<std::endl;
    return 0;
}

// *** ConnectCommand execute ***
int ConnectCommand::execute(string *str, unordered_map<string, Command *> *input,
                            unordered_map<string, Command *> *output) {
    int jump = 3;
    return jump;

}

int ConnectCommand::connectClient(string *str){
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }
    int port = stoi(*(str + 2));
    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr("127.0.0.1");  //the localhost address
    address.sin_port = htons(port);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server"<<std::endl;
        return -2;
    } else {
        std::cout<<"Client is now connected to server" <<std::endl;
    }

    //if here we made a connection
    char hello[] = "Hi from client";
    int is_sent = send(client_socket , hello , strlen(hello) , 0 );
    if (is_sent == -1) {
        std::cout<<"Error sending message"<<std::endl;
    } else {
        std::cout<<"Hello message sent to server" <<std::endl;
    }

    char buffer[1024] = {0};
    int valread = read( client_socket , buffer, 1024);
    std::cout<<buffer<<std::endl;

    close(client_socket);
}

// *** DefineVarCommand execute ***
int DefineVarCommand::execute(string *str, unordered_map<string, Command *> *input,
                              unordered_map<string, Command *> *output) {
    int jump = 5;
    const char *rightArrow = "\x04->";
    const char *leftArrow = "\x04<-";
    const char *symbol = reinterpret_cast<const char *>(str + 2);
    //put into symbol table that updates the simulator
    if (strcmp(symbol, rightArrow) == 0) {
        //working with output symbol table
        Command *var = new Var();

    }
    //
    //put into symbol table that gets updates from the simulator
    if (strcmp(symbol, leftArrow) == 0) {
        //unordered_map<string, Command*> firstMap()
        int temp = 0;


    }
    //assign the simname of the variable
    this->simName = str + 4;
    //return how much we need to jump
    return jump;
}


// *** Var execute ***
int Var::execute(string *str, unordered_map<string, Command *> *input,
                 unordered_map<string, Command *> *output) {
    Command *var = new Var();

}


