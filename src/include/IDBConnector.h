#ifndef IDBCONNECTOR_H
#define IDBCONNECTOR_H

#include <string>

class IDBConnector {
    public:
        virtual void connect(std::string uri) =0;
        virtual void disconnect() = 0;
};

#endif 
