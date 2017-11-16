#include "../include/I2CHandler.h"

I2CHandler::I2CHandler(const int &address) : m_address(address) { 
    if ( (m_fileI2C = open(DEFAULTDEVICE, O_RDWR)) < 0)
        setErrMsg("failed to open i2c file");
}

I2CHandler::I2CHandler(const std::string &device,
        const int &address) : m_address(address) {
    if ( (m_fileI2C = open(device.c_str(), O_RDWR)) < 0)
        setErrMsg("failed to open i2c file");
}

I2CHandler::I2CHandler() {
    if ( (m_fileI2C = open(DEFAULTDEVICE, O_RDWR)) < 0)
        setErrMsg("failed to open i2c file");
}

I2CHandler::~I2CHandler() {
    if ( m_fileI2C ){
        close(m_fileI2C);
        m_fileI2C = 0;
    }
}

int I2CHandler::readValue(char *rxBuf, const int &address) {
    if ( m_fileI2C ) {
        m_address = address;
        if ( ioctl(m_fileI2C, I2C_SLAVE, m_address) < 0) {
            return setErrMsg("couldn't handle IO operations on file");
        }
        if (read(m_fileI2C, rxBuf, m_address) < 0){
            return setErrMsg("couldn't read from the bus");
        }
        return 0;
    }
    return -1; 
}

int I2CHandler::setErrMsg(const std::string &msg) {
    err_msg = "ERROR: ";
    err_msg += msg;
    return -1;
}

//int I2CHandler::writeValue(const double &value, const int &address) { }
