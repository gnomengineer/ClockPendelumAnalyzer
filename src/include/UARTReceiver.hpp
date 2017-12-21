#pragma once

#include "UARTHandler.hpp"
#include "IObserver.h"

using namespace std;

class UARTReceiver {
public:
	UARTReceiver(UARTHandler* handler, IObserver* controller);
	~UARTReceiver();

	void stopReading();

	static void* staticEntryPoint(void* threadId);

private:
	void readAndPlotData();
	void startRecording();
	void decodeRecievedString(std::string message);

	int m_uart0_filestream;
	bool m_active;
	IObserver* m_Observer;

};
