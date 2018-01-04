#include "../include/DataAssembler.h"
#include <iostream>
#include <stdexcept>

DataTupel DataAssembler::getNewDataSample(std::string clockname) {
    std::string dateString("0");
    DataTupel dataSample(clockname,dateString,0);

    m_time_list_mutex.lock();
    if ( m_time_list.size() != 0) {
        dataSample = m_time_list.front();
        m_time_list.pop_front();
    }
    m_time_list_mutex.unlock();

    if (dataSample.getClockName() != "new") {
        throw std::length_error("nothing received from counter");
    }

    dataSample.setClockName(clockname);

    return dataSample;
}

void DataAssembler::addToVector(std::string timeKey, uint32_t absoluteTime, uint32_t referenceFrequency) {
    std::string clockNameString("new");
    DataTupel dataSample(clockNameString,timeKey,absoluteTime,referenceFrequency);
    m_time_list_mutex.lock();
    m_time_list.push_back(dataSample);
    m_time_list_mutex.unlock();
}
