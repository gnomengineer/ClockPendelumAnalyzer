//
// Created by tobias on 10.12.17.
//
#include "../include/RESTInterface.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <zconf.h>

RESTInterface::RESTInterface()
    : m_running(false) {
}

RESTInterface::~RESTInterface() {

}

void* RESTInterface::staticEntryPoint(void* threadId) {
    std::cout << "Thread REST started" << std::endl;
    ((RESTInterface*)threadId)->startServer();
    std::cout << "Thread REST ended" << std::endl;
    pthread_exit(threadId);
}

void RESTInterface::startServer() {
    m_running = true;
    int socketfd, newSocketfd;
    uint16_t portNr;
    socklen_t clientLength;

    sockaddressIn_t serverAddress, clientAddress;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0 ) {
        std::cout << "Error opening socket" << std::endl;
    }
    //TODO fix compiler error on line below!
    bzero(&serverAddress, sizeof(serverAddress));
    portNr = 80;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(portNr);

    if (bind(socketfd, reinterpret_cast<socketAddress_t*>(&serverAddress), sizeof(serverAddress)) < 0 ) {
        std::cout << "ERROR on binding" << std::endl;
    }

    listen(socketfd, 5);

    clientLength = sizeof(clientAddress);
    newSocketfd = accept(socketfd, reinterpret_cast<socketAddress_t*>(&clientAddress), &clientLength);

    if (newSocketfd < 0) {
        std::cout << "ERROR on accept" << std::endl;
    }

    requestHandler(newSocketfd);

    close(newSocketfd);
    close(socketfd);

}

void RESTInterface::stopServer() {
    m_running = false;
}

void RESTInterface::requestHandler(const int newSocketfd) {
    char buffer[1024];
    while (m_running) {
        bzero(buffer,50);
        recv(newSocketfd, buffer, 1024, 0);
        std::string message(buffer);

    }
}
