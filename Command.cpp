

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
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>

// *** Print Command ***
int PrintCommand::execute(string *str, unordered_map<string, Command *>* input,
                          unordered_map<string, Command *>* output) {
    cout << str << endl;
    return 1;
}

// *** SleepCommand execute ***
int SleepCommand::execute(string *str, unordered_map<string, Command *>* input,
                          unordered_map<string, Command *>* output) {
    this_thread::sleep_for(timeSpan);
    return 1;
}

// *** OpenServerCommand execute ***

int OpenServerCommand::execute(string *str, unordered_map<string, Command *>* input,
                               unordered_map<string, Command *>* output) {
    thread serverThread(openServer, str);
    serverThread.join();
}

int OpenServerCommand::openServer(string *str){
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }
    int port = stoi(*str);
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
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        return -2;
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr<<"Error during listening command"<<std::endl;
        return -3;
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }

    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *)&address,
                               (socklen_t*)&address);

    if (client_socket == -1) {
        std::cerr<<"Error accepting client"<<std::endl;
        return -4;
    }

}

// *** ConnectCommand execute ***
int ConnectCommand::execute(string *str, unordered_map<string, Command *>* input,
                            unordered_map<string, Command *>* output) {
    int jump = 2;
    return jump;

}

// *** DefineVarCommand execute ***
int DefineVarCommand::execute(string *str, unordered_map<string, Command *>* input,
                              unordered_map<string, Command *>* output) {
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
int Var::execute(string *str, unordered_map<string, Command *>* input,
        unordered_map<string, Command *>* output) {
    Command *var = new Var();

}


