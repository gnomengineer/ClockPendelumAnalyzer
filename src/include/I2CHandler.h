#ifndef I2CHANDLER_H
#define I2CHANDLER_H

#include <string>
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port

#define DEFAULTDEVICE "/dev/i2c-1"

class I2CHandler {
public:
    I2CHandler(const int &address);
    I2CHandler(const std::string &device, const int &address);
    I2CHandler();
    ~I2CHandler();
    int readValue(char* rxBuf, const int &address);
    //int writeValue(const double &value, const int &address);
    int getAddress() { return m_address };
private:
    int setErrMsg(const std::string &msg)
    int m_address = -1;
    int m_fileI2C = 0;
    std::string err_msg = "";
};

#endif 
