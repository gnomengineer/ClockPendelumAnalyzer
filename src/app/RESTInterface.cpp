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
#include <errno.h>

const std::string DATE_DELIMITER = "data=";
const std::string NAME_DELIMITER = "name=";
const std::string REFERENCE_DELIMITER = "referenz";

RESTInterface::RESTInterface(DataTransfer* dataTransfer)
    : m_running(true) {
    m_DataTransfer = dataTransfer;

    socketAddressIn_t serverAddress;

    m_ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_ServerSocket < 0 ) {
        perror("socket");
    }
    bzero(&serverAddress, sizeof(serverAddress));
    uint16_t portNr = 8080;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(portNr);

    if (bind(m_ServerSocket, reinterpret_cast<socketAddress_t*>(&serverAddress), sizeof(serverAddress)) < 0 ) {
        perror("binding");
    }

    listen(m_ServerSocket, 5);
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
    while (m_running) {
        socketAddressIn_t clientAddress;
        socklen_t clientLength = sizeof(clientAddress);
        int clientSocket = accept(m_ServerSocket, reinterpret_cast<socketAddress_t*>(&clientAddress), &clientLength);

        if (clientSocket < 0) {
            perror("accept");
        }

        requestHandler(clientSocket);

        close(clientSocket);
    }
    close(m_ServerSocket);

}

void RESTInterface::stopServer() {
    m_running = false;
}

void RESTInterface::requestHandler(const int client) {
    char buffer[1024];
    bzero(buffer,50);
    recv(client, buffer, 1024, 0);
    std::string message(buffer);
    
    if(message.size() > 0) {
        decodeMessage(message.substr(message.find("?")));
        std::string response = m_Response.dump();
        send(newSocketfd, response.c_str(), response.size(), 0);
    }
    send(client, "Hello, World!",13,0);
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
    std::cout << "Normal: bla" << std::endl;
}

void RESTInterface::generateReferenceResponse() {
    std::cout << "Referenz: 12" << std::endl;
    json reference_response = {
        {"success", true},
        {"payload",
            {"hertz", 12000000}
        }
    };

    m_Response = reference_response;
}
