

#include <iostream>
#include <thread>
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include "Command.h"
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



// *** ConnectCommand execute ***
int ConnectCommand::execute(string *str, unordered_map<string, Command *> *input,
                            unordered_map<string, Command *> *output) {
    int jump = 3;
    return jump;

}

int ConnectCommand::connectClient(string *str)
{
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        //error
        std::cerr << "Could not create a socket" << std::endl;
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
    int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
    if (is_connect == -1)
    {
        std::cerr << "Could not connect to host server" << std::endl;
        return -2;
    }
    else
    {
        std::cout << "Client is now connected to server" << std::endl;
    }

    //if here we made a connection
    char hello[] = "Hi from client";
    int is_sent = send(client_socket, hello, strlen(hello), 0);
    if (is_sent == -1)
    {
        std::cout << "Error sending message" << std::endl;
    }
    else
    {
        std::cout << "Hello message sent to server" << std::endl;
    }

    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1024);
    std::cout << buffer << std::endl;

    close(client_socket);
}

