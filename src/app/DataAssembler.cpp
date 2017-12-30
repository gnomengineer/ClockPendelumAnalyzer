#include "../include/DataAssembler.h"
#include <iostream>
#include <stdexcept>

DataTupel DataAssembler::getNewDataSample(std::string clockname) {
    std::pair<std::string, int> timePair;
    m_time_list_mutex.lock();
    if ( m_time_list.size() != 0) {
        timePair = m_time_list.front();
        m_time_list.pop_front();
    } else {
        timePair = std::pair<std::string, int>("exit",1);
    }
    m_time_list_mutex.unlock();

    if (std::get<0>(timePair) == "exit") {
        throw std::length_error("nothing received from counter");
    }

    DataTupel dataSample(clockname,std::get<0>(timePair),std::get<1>(timePair));
    return dataSample;
}

void DataAssembler::addToVector(std::string timeKey, int absoluteTimeValue) {
    std::pair<std::string, int> pair(timeKey, absoluteTimeValue);
    m_time_list_mutex.lock();
    m_time_list.push_back(pair);
    m_time_list_mutex.unlock();
}
