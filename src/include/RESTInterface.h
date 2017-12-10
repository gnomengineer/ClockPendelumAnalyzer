//
// Created by tobias on 10.12.17.
//
#pragma once
#include <sys/types.h>

#ifndef CLOCKPENDULUMANALYZER_RESTINTERFACE_H
#define CLOCKPENDULUMANALYZER_RESTINTERFACE_H

class RESTInterface {
public:

    RESTInterface();
    ~RESTInterface();

    void startServer();

    void stopServer();

private:

    typedef struct sockaddr_in sockaddressIn_t;
    typedef struct sockaddr socketAddress_t;

    void requestHandler(const int newSocketfd);

    bool m_running;

};

#endif //CLOCKPENDULUMANALYZER_RESTINTERFACE_H
