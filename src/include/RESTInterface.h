//
// Created by tobias on 10.12.17.
//
#pragma once
#include <sys/types.h>
#include <string>
#include "DataTransfer.h"

#ifndef CLOCKPENDULUMANALYZER_RESTINTERFACE_H
#define CLOCKPENDULUMANALYZER_RESTINTERFACE_H

class RESTInterface {
public:

    RESTInterface();
    ~RESTInterface();

    static void* staticEntryPoint(void* threadId);

    void stopServer();

private:

    typedef struct sockaddr_in sockaddressIn_t;
    typedef struct sockaddr socketAddress_t;

    void startServer();
    void requestHandler(const int newSocketfd);

    bool m_running;

};

#endif //CLOCKPENDULUMANALYZER_RESTINTERFACE_H
