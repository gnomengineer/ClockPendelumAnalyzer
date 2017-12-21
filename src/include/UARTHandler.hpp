#pragma once

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <memory>
#include <stdint.h>
#include <cstdlib>

using namespace std;

class UARTHandler {
public:

	enum BaudRateE {
		SLOW = B9600,
		MEDIUM = B57600,
		FULL_SPEED = B115200
	};

	UARTHandler();
	~UARTHandler();

	int getFileStream();

	bool openSerialIF(const char* ifName);

	bool setUartConfig(BaudRateE baudRate);

private:

	int m_uart0_filestream;
	int m_waitFlag;
};
