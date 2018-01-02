#include "../include/UARTReceiver.hpp"
#include <string.h>
#include <ctime>
#include <iomanip>
#include <sstream>

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
			ssize_t rx_length = read(m_uart0_filestream, rx_buffer, sizeof(rx_buffer));
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
    std::time_t time = std::time(0);
    std::stringstream timeString;
	std::string pendulumTime, referenceFrequency;
    timeString << std::put_time(std::localtime(&time),"%Y%m%d%H%M%S");
	pendulumTime = message.substr(0, message.find(';'));
    auto pendTime = static_cast<uint32_t>(std::stoul(pendulumTime));
	referenceFrequency = message.substr(message.find(';') + 1);
	double corrVal = std::stoi(referenceFrequency) / 12000000.0;
	if (abs(corrVal) > 0.8 && abs(corrVal) < 1.5) {
		pendTime = static_cast<uint32_t>(pendTime * corrVal);
	}
    m_Observer->addToVector(timeString.str(), pendTime);
}

void* UARTReceiver::staticEntryPoint(void* threadId) {
    cout << "Thread UARTReceiver started" << endl;
	((UARTReceiver*)threadId)->startRecording();
	cout << "Thread UARTReceiver ended" << endl;
	pthread_exit(threadId);
}
