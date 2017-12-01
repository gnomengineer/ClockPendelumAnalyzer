#include "../include/DataAssembler.h"
#include <ctime>
#include <iostream>

DataTupel DataAssembler::getNewDataSample(std::string clockname) {
    int absoluteTime = m_Analyzer.getTimeDifference_ns();
    time_t now = time(0);
    struct tm* localTime = localtime(&now);
    //TODO fix time return values
    std::cout << "Day: " << localTime->tm_mday << std::endl;
    std::cout << "Month: " << localTime->tm_mon << std::endl;
    std::cout << "Year: " << localTime->tm_year << std::endl;

    DataTupel dataSample(clockname,"00000000",absoluteTime);
    return dataSample;
}
