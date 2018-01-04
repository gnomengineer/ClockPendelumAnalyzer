//
// Created by tobias on 10.12.17.
//
#pragma once
#include <sys/types.h>
#include <string>
#include "DataTransfer.h"
#include "json.hpp"

#ifndef CLOCKPENDULUMANALYZER_RESTINTERFACE_H
#define CLOCKPENDULUMANALYZER_RESTINTERFACE_H

using json = nlohmann::json;

class RESTInterface {
public:

    RESTInterface(DataTransfer* dataTransfer);
    ~RESTInterface();

    static void* staticEntryPoint(void* threadId);

    void stopServer();

private:

    typedef struct sockaddr_in socketAddressIn_t;
    typedef struct sockaddr socketAddress_t;

    void startServer();
    void requestHandler(const int clientSocket);
    void decodeMessage(const std::string& parameters);
    std::string getParam(const std::string& parameters, const int pos);
    void generateReferenceResponse();
    void generateNormalResponse();
    std::string getHeaderInformation(std::string::size_type length, bool isSuccess);

    bool m_running;
    int m_ServerSocket;
    DataTransfer* m_DataTransfer;
    std::string m_DateParam;
    std::string m_NameParam;
    std::string m_Response;

};

#endif //CLOCKPENDULUMANALYZER_RESTINTERFACE_H
