#include "../include/ClockPendulumAnalyzer.h"
#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>
#include <stdio.h>

ClockPendulumAnalyzer::ClockPendulumAnalyzer(std::string clockname) : m_ClockName(clockname) {
    //m_DataAssembler = new DataAssembler();//TODO implement DataAssembler
}

void ClockPendulumAnalyzer::startAnalyze() {
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
        DataTupel singleData(m_ClockName, "20171123080808", 15);
        m_DataList.push_back(singleData);
        //TODO use DataAssembler.getNewDataSample and print it to cout
        std::cout << "clock name :" << m_ClockName << std::endl;
        //std::cout << m_DataList.back().getClockName << " in DataTupel" << std::endl;
        std::this_thread::sleep_for(timespan);
    }
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
