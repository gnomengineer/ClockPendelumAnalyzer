#include "../include/UARTHandler.hpp"

	UARTHandler::UARTHandler() {
		m_uart0_filestream =-1;
		m_waitFlag = 0;	
	}

	UARTHandler::~UARTHandler() {
		close(m_uart0_filestream);
	}

	int UARTHandler::getFileStream() {
		return m_uart0_filestream;
	}

	bool UARTHandler::openSerialIF(const char* ifName) {
		m_uart0_filestream = open(ifName, O_RDWR);	//Open in (non) blocking read/write mode
		if (m_uart0_filestream == -1)
		{
			usleep(1000000);
			return false;
		}
		return true;
	}

	bool UARTHandler::setUartConfig(BaudRateE baudRate) {
		struct termios options;

		if (tcgetattr(m_uart0_filestream, &options) !=0) {
			return false;
		}
	    cfsetospeed(&options,baudRate);
	    cfsetispeed(&options,baudRate);

		options.c_cflag = CREAD | CS8;
		options.c_iflag = IGNPAR;
		options.c_oflag = 0;
		options.c_lflag = 0;
		options.c_cc[VMIN] = 0;
		options.c_cc[VTIME] = 5;

		if (tcsetattr(m_uart0_filestream, TCSANOW, &options) != 0 ) {	
			close(m_uart0_filestream);
			return false;
		}
		tcsetattr(m_uart0_filestream, TCSAFLUSH, &options);
		return true;
	}
