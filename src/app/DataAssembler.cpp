#include "../include/DataAssembler.h"
#include <ctime>
#include <iostream>

DataTupel DataAssembler::getNewDataSample(std::string clockname) {
    std::pair<std::string, int> timePair;
    m_time_list_mutex.lock();
    if ( m_time_list.size() != 0) {
        timePair = m_time_list.front();
        m_time_list.pop_front();
    }
    m_time_list_mutex.unlock();

    std::cout << std::get<0>(timePair) << ":" << std::get<1>(timePair) << std::endl;

    DataTupel dataSample(clockname,"00000000",1);
    return dataSample;
}

void DataAssembler::addToVector(std::string timeKey, int absoluteTimeValue) {
    std::pair<std::string, int> pair(timeKey, absoluteTimeValue);
    m_time_list_mutex.lock();
    m_time_list.push_back(pair);
    m_time_list_mutex.unlock();
}
