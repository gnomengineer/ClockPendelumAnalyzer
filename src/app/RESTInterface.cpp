//
// Created by tobias on 10.12.17.
//
#include "../include/RESTInterface.h"
#include "../include/DataTupel.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <zconf.h>
#include <errno.h>

const std::string DATE_DELIMITER = "date=";
const std::string NAME_DELIMITER = "name=";
const std::string REFERENCE_DELIMITER = "referenz";

RESTInterface::RESTInterface(DataTransfer* dataTransfer)
    : m_running(true) , m_NameParam(""), m_DateParam(""){
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
    if(m_ServerSocket > 0){
        close(m_ServerSocket);
    }
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
        decodeMessage(message.substr(message.find("?")+1));
        send(client, m_Response.c_str(), m_Response.size(), 0);
    }
}

void RESTInterface::decodeMessage(const std::string& parameters){
    if ( parameters.find(REFERENCE_DELIMITER) != std::string::npos) {
        generateReferenceResponse();
    } else {
        int pos;
        if ( (pos = parameters.find(DATE_DELIMITER)) != std::string::npos) {
            m_DateParam = getParam(parameters, pos);
        } else {
            m_DateParam = "";
        }
        if ( (pos = parameters.find(NAME_DELIMITER)) != std::string::npos) {
            m_NameParam = getParam(parameters, pos); 
        } else {
            m_NameParam = "";
        }
        generateNormalResponse();
    }
}

std::string RESTInterface::getParam(const std::string& parameters, const int pos) {
    int length;
    if ((length = parameters.find("&")) == std::string::npos) {
        length = parameters.find(" HTTP");
    }
    std::string first_param = parameters.substr(pos,length);
    return first_param.substr(first_param.find("=")+1);
}

void RESTInterface::generateNormalResponse() {
    std::list<DataTupel> results;
    std::cout << "Parameters: " << m_DateParam << "|" << m_NameParam << ";" << std::endl;
    bool isSuccess = true;
    bool commandKnown = true;

    if( m_DateParam != "" && m_NameParam != "") {
        results = m_DataTransfer->getDataListByNameAndDate(m_NameParam,m_DateParam);
    } else if( m_DateParam != "") {
        results = m_DataTransfer->getDataListByDate(m_DateParam);
    } else if( m_NameParam != "") {
        results = m_DataTransfer->getDataListByName(m_NameParam);
    } else {
        commandKnown = false;
    }

    results.size();

    json normal_response;

    if(results.size() != 0){
        isSuccess = true;
    } else {
        isSuccess = false;
    }
    
    normal_response["success"] = isSuccess;
    json payloadContentArray;
    for(int counter = 0; counter < results.size(); counter++) {
        json jsonDataTupel;
        DataTupel dataTupel = results.front();
        results.pop_front();
        jsonDataTupel["name"] = dataTupel.getClockName();
        jsonDataTupel["time"] = dataTupel.getAbsoluteTime();
        jsonDataTupel["date"] = dataTupel.getDate();
        jsonDataTupel["referenz"] = dataTupel.getReferenceFrequency();

        payloadContentArray[counter] = jsonDataTupel;
    }
    normal_response["payload"] = payloadContentArray;

    std::string response = normal_response.dump();
    if(!commandKnown) {
        m_Response = getHeaderInformation(0,isSuccess);
    } else {
        m_Response = getHeaderInformation(response.size(),isSuccess);
    }
    m_Response += response;
        // transform data to json and append to header if successfull
}

void RESTInterface::generateReferenceResponse() {
    json reference_response = {
        {"success", true},
        {"payload",{
            {"hertz", 12000000}
                   }
        }
    };

    std::string response = reference_response.dump();
    m_Response = getHeaderInformation(response.size(),true);
    m_Response += response;
}

std::string RESTInterface::getHeaderInformation(std::string::size_type length, bool isSuccess) {
    std::time_t time = std::time(0);
    std::stringstream timeString;
    timeString << std::put_time(std::localtime(&time),"%Y%m%d%H%M%S");

    std::string ret_type;
    if(isSuccess) {
        ret_type = "200 OK";
    } else if (length == 0) {
        ret_type = "501 NOT IMPLEMENTED";
    } else {
        ret_type = "500 INTERNAL SERVER ERROR";
    }

    std::stringstream header;
    header << "HTTP/1.1 " << ret_type << "\n"
        << "Date: " << timeString.str() 
        << "GMT + 1 (CET)\n"
        << "Server: REST Service - Clock Pendulum Analyzer\n"
        << "Content-Type: text/plain; charset=utf-8\n Content-Length: " 
        << length << "\n\n";

    return header.str();
}
