#ifndef CLOCKPENDULUM_H
#define CLOCKPENDULUM_H

#include <list>
#include <string>
#include <thread>
#include "DataTupel.h"
#include "DataTransfer.h"
#include "DataAssembler.h"
#include "UARTHandler.hpp"
#include "UARTReceiver.hpp"
#include "RESTInterface.h"

class ClockPendulumAnalyzer {
    public:
        ClockPendulumAnalyzer(std::string clockname,bool isAutonom);
        ~ClockPendulumAnalyzer();
        void startAnalyze();
    private:
        const int MAXDATATUPEL = 5;
        std::list<DataTupel> m_DataList;
        DataTransfer m_DataTransfer;
        std::string m_ClockName;
        bool m_AutonomousRun = true;
        DataAssembler m_DataAssembler;
        UARTHandler* m_Handler;
        UARTReceiver* m_Receiver;
        RESTInterface* m_RestService; 
};

#endif
