#ifndef CLOCKPENDULUM_H
#define CLOCKPENDULUM_H

#include <list>
#include <string>
#include "DataTupel.h"
#include "DataTransfer.h"

class ClockPendulumAnalyzer {
    public:
        ClockPendulumAnalyzer(std::string clockname);
        void startAnalyze();
    private:
        const int MAXDATATUPEL = 0;
        std::list<DataTupel> m_DataList;
        DataTransfer m_DataTransfer;
        std::string m_ClockName;
        //DataAssembler m_DataAssembler; //TODO implement DataAssembler
        //IRESTService m_RestService; //TODO implement REST Service
};

#endif
