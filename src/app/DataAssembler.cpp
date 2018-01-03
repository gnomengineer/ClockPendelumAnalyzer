#include "../include/DataAssembler.h"
#include <iostream>
#include <stdexcept>

DataTupel DataAssembler::getNewDataSample(std::string clockname) {
    std::pair<std::string, DataTupel> timePair;
    m_time_list_mutex.lock();
    if ( m_time_list.size() != 0) {
        timePair = m_time_list.front();
        m_time_list.pop_front();
    } else {
        timePair = std::make_pair("exit", DataTupel("", 0,0,0));
    }
    m_time_list_mutex.unlock();

    if (std::get<0>(timePair) == "exit") {
        throw std::length_error("nothing received from counter");
    }

    DataTupel dataSample(clockname);
    return dataSample;
}

void DataAssembler::addToVector(std::string timeKey, uint32_t absoluteTime, uint32_t referenceFrequency) {
    std::pair<std::string, std::pair<uint32_t, uint32_t>> pair(timeKey, std::make_pair(absoluteTime, referenceFrequency));
    m_time_list_mutex.lock();
    m_time_list.push_back(pair);
    m_time_list_mutex.unlock();
}
