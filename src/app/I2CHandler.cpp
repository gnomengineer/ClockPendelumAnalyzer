#include "../include/I2CHandler.h"
#include <iostream>

//@deprecated
I2CHandler::I2CHandler(const int &address) { 
    I2CHandler(DEFAULTDEVICE, address);
}

I2CHandler::I2CHandler(const std::string &device,
        const int &address) : m_address(address) {
    if ( (m_fileI2C = open(device.c_str(), O_RDWR)) < 0)
        setErrMsg("failed to open i2c file");
}

I2CHandler::I2CHandler() {
    I2CHandler(DEFAULTDEVICE, -1);
}

I2CHandler::~I2CHandler() {
    if ( m_fileI2C ){
        close(m_fileI2C);
        m_fileI2C = 0;
    }
}

int I2CHandler::readValue(std::string& data, const int address) {
    int errorCode = 0;
    char* rxBuf = getBuffer(data);

    if ( m_fileI2C ) {
        m_address = address;
        if ( acquiringConnection() >= 0){
            if (read(m_fileI2C, rxBuf, data.size()) != data.size()){
                errorCode = setErrMsg("couldn't read from the bus");
            }
        }
    } else {
        return -1; 
    }

    std::string buffer(rxBuf);
    data = buffer;
    delete[] rxBuf;
    return errorCode;
}

int I2CHandler::setErrMsg(const std::string &msg) {
    std::cout << "ERROR: " << msg << std::endl;
    return -1;
}

int I2CHandler::writeValue(std::string data, const int address) { 
    int errorCode = 0;
    char* txBuf = getBuffer(data);

    if ( m_fileI2C ) {
        m_address = address;
        if ( acquiringConnection() >= 0) {
            if ( write(m_fileI2C, txBuf, data.size()) != data.size()) {
                errorCode = setErrMsg("couldn't write to the bus");
            }
        }
    } else {
        errorCode = -1;
    }

    delete[] txBuf;
    return errorCode;
}

char* I2CHandler::getBuffer(std::string bufferString){
    char* buffer = new char[bufferString.size() + 1];
    std::copy(bufferString.begin(), bufferString.end(), buffer);
    buffer[bufferString.size()] = '\0';

    return buffer;
}


int I2CHandler::acquiringConnection() {
    if (ioctl(m_fileI2C, I2C_SLAVE, m_address) < 0) {
        return setErrMsg("couldn't handle IO operations on file");
    }
    return 0;
}

