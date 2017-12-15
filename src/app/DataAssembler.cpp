#include "../include/DataAssembler.h"
#include <ctime>
#include <iostream>

DataTupel DataAssembler::getNewDataSample(std::string clockname) {
    

    m_time_list_mutex.lock();
    m_time_list.front();
    m_time_list.pop_front();
    m_time_list_mutex.unlock();

    int absoluteTime = 1; //TODO get absolute time from list
    time_t now = time(0);
    struct tm* localTime = localtime(&now);
    //TODO fix time return values
    std::cout << "Day: " << localTime->tm_mday << std::endl;
    std::cout << "Month: " << localTime->tm_mon << std::endl;
    std::cout << "Year: " << localTime->tm_year << std::endl;

    DataTupel dataSample(clockname,"00000000",absoluteTime);
    return dataSample;
}

void DataAssembler::addToVector(std::string timeKey, int absoluteTimeValue) {
    std::pair<std::string, int> pair(timeKey, absoluteTimeValue);
    m_time_list_mutex.lock();
    m_time_list.push_back(pair);
    m_time_list_mutex.unlock();
}
