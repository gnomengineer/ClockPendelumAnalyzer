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

const std::string DATE_DELIMITER = "data=";
const std::string NAME_DELIMITER = "name=";
const std::string REFERENCE_DELIMITER = "referenz";

RESTInterface::RESTInterface(DataTransfer* dataTransfer)
    : m_running(false) {
    m_DataTransfer = dataTransfer;
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

        decodeMessage(message.substr(message.find("?")));
    }
}

void RESTInterface::decodeMessage(const std::string& parameters){
    if ( parameters.find(REFERENCE_DELIMITER) != std::string::npos) {
        generateReferenceResponse();
    } else {
        int pos;
        if ( (pos = parameters.find(DATE_DELIMITER)) != std::string::npos) {
            m_DateParam = getParam(parameters, pos);
        }
        if ( (pos = parameters.find(NAME_DELIMITER)) != std::string::npos) {
            m_NameParam = getParam(parameters, pos); 
        }
        generateNormalResponse();
    }
}

std::string RESTInterface::getParam(const std::string& parameters, const int pos) {
    std::string first_param = parameters.substr(pos,parameters.find("&"));
    return first_param.substr(first_param.find("=")+1);
}

void RESTInterface::generateNormalResponse() {

}

void RESTInterface::generateReferenceResponse() {

}
