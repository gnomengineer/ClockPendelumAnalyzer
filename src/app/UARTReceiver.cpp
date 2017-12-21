#include "../include/UARTReceiver.hpp"
#include <string.h>

UARTReceiver::UARTReceiver(UARTHandler* handler, IObserver* observer) {
	m_uart0_filestream = handler->getFileStream();
	m_active = false;
	m_Observer = observer;
}

UARTReceiver::~UARTReceiver() {
}

void UARTReceiver::startRecording() {
	m_active = true;
	readAndPlotData();
}

void UARTReceiver::stopReading() {
	m_active = false;
	cout << "Stop command received" << endl;
}

void UARTReceiver::readAndPlotData() {

	unsigned char rx_buffer[512];
	while(m_active) {
			//----- CHECK FOR ANY RX BYTES -----
		if (m_uart0_filestream != -1) {
			bzero(rx_buffer,sizeof(rx_buffer));
			int rx_length = read(m_uart0_filestream, rx_buffer, sizeof(rx_buffer));
			if (rx_length > 0 ) {
				string str(reinterpret_cast<const char*>(rx_buffer));
				if (str.length() > 0) {
					decodeRecievedString(str);
				}
			}
		}
	}
}

void UARTReceiver::decodeRecievedString(std::string message) {
    //TODO change this to call observers addTime metho	
}

void* UARTReceiver::staticEntryPoint(void* threadId) {
	((UARTReceiver*)threadId)->startRecording();
	cout << "Thread UARTReceiver ended" << endl;
	pthread_exit(threadId);
}