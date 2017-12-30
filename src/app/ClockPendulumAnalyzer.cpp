#include "../include/ClockPendulumAnalyzer.h"
#include <iostream>
#include <time.h>
#include <chrono>
#include <stdio.h>

ClockPendulumAnalyzer::ClockPendulumAnalyzer(std::string clockname) : m_ClockName(clockname) {
    m_Handler = new UARTHandler();
    m_Receiver = new UARTReceiver(m_Handler, &m_DataAssembler);
}

ClockPendulumAnalyzer::~ClockPendulumAnalyzer() {
    delete m_Receiver;
    delete m_Handler;
}

void ClockPendulumAnalyzer::startAnalyze() {
    pthread_t thread;
    int rc = pthread_create(&thread, NULL, UARTReceiver::staticEntryPoint, m_Receiver);
	if (rc) {
		cout << "Error:unable to create thread," << rc << endl;
	}

    bool isSaved = false;
    std::chrono::milliseconds timespan(1000);
    while (getchar() != 'q') {
        //TODO implement a simple stop on 'q'
        if ( m_DataList.size() >= MAXDATATUPEL ) {
            isSaved = m_DataTransfer.saveDataList(m_DataList);
        }
        if (isSaved) {
            m_DataList.clear();
            isSaved = false;
        }
        DataTupel singleData = m_DataAssembler.getNewDataSample(m_ClockName);
        m_DataList.push_back(singleData);
        
        std::this_thread::sleep_for(timespan);
    }
    m_Receiver->stopReading();
}

int main( int argc, const char* argv[] ) {
    if ( argc == 2 ){
        std::cout << "clock pendulum analyzer is started" << std::endl;
        ClockPendulumAnalyzer analyzer (argv[1]);
        analyzer.startAnalyze();
    } else {
        std::cout << "this programm needs the clock name as cli parameter" << std::endl;
    }
}
