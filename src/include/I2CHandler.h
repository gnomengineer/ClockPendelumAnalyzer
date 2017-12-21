#ifndef I2CHANDLER_H
#define I2CHANDLER_H

#include <string>
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port

#define DEFAULTDEVICE "/dev/i2c-1"

//@deprecated
class I2CHandler {
public:
    I2CHandler(const int &address);
    I2CHandler(const std::string &device, const int &address);
    I2CHandler();
    ~I2CHandler();
    int readValue(std::string& data, const int address);
    int writeValue(std::string data, const int address);
    int getAddress() { return m_address ;}

private:
    int setErrMsg(const std::string &msg);
    int acquiringConnection();
    char* getBuffer(std::string bufferString);
    int m_address = -1;
    int m_fileI2C = 0;
};

#endif 
