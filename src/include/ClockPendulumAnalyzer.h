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

class ClockPendulumAnalyzer {
    public:
        ClockPendulumAnalyzer(std::string clockname);
        ~ClockPendulumAnalyzer();
        void startAnalyze();
    private:
        const int MAXDATATUPEL = 5;
        std::list<DataTupel> m_DataList;
        DataTransfer m_DataTransfer;
        std::string m_ClockName;
        DataAssembler m_DataAssembler;
        UARTHandler* m_Handler;
        UARTReceiver* m_Receiver;
        //IRESTService m_RestService; //TODO implement REST Service
};

#endif
