#include "../include/ClockPendulumAnalyzer.h"
#include <iostream>
#include <time.h>
#include <chrono>
#include <stdio.h>

ClockPendulumAnalyzer::ClockPendulumAnalyzer(std::string clockname, bool isAutonom) : m_ClockName(clockname), m_AutonomousRun(isAutonom) {
    m_Handler = new UARTHandler();
    m_Handler->openSerialIF("/dev/ttyACM0");
    m_Handler->setUartConfig(UARTHandler::MEDIUM);
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
        std::cout << "Error:unable to create thread," << rc << std::endl;
	}

    bool isSaved = false;
    std::chrono::milliseconds timespan(1000);
    while (m_AutonomousRun || getchar() != 'q') {
        //TODO implement a simple stop on 'q'
        if ( m_DataList.size() >= MAXDATATUPEL ) {
            isSaved = m_DataTransfer.saveDataList(m_DataList);
        }
        if (isSaved) {
            m_DataList.clear();
            isSaved = false;
        }

        try {
            DataTupel singleData = m_DataAssembler.getNewDataSample(m_ClockName);
            m_DataList.push_back(singleData);
        } catch (const std::length_error& e) {
            std::cout << e.what() << std::endl;
        }
        
        std::this_thread::sleep_for(timespan);
    }
    m_Receiver->stopReading();
}

int main( int argc, const char* argv[] ) {
    if ( argc > 1 ){
        std::cout << "clock pendulum analyzer is started" << std::endl;
        bool isAutonom = true;
        if (argc == 3) {
            std::string s(argv[2]);
            if ( s == "false") {
                isAutonom = false;
                std::cout << "test" << std::endl;
            }
        }

        ClockPendulumAnalyzer analyzer (argv[1], isAutonom);
        analyzer.startAnalyze();
    } else {
        std::cout << "this programm needs the clock name and a boolean for manual test as cli parameter" << std::endl;
    }
}
