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
        std::string dummy = "dummy";
        std::string dummyDate = "20170101";
        std::string exit = "exit";
        timePair = std::make_pair(exit, DataTupel(dummy, dummyDate, 0, 0));
    }
    m_time_list_mutex.unlock();

    if (timePair.first.find("exit") != -1) {
        throw std::length_error("nothing received from counter");
    }

    DataTupel dataSample(timePair.second);
    return dataSample;
}

void DataAssembler::addToVector(std::string timeKey, uint32_t absoluteTime, uint32_t referenceFrequency) {
    std::string name = ("sampleClock");
    DataTupel tupel(name, timeKey, absoluteTime, referenceFrequency);
    m_time_list_mutex.lock();
    m_time_list.push_back(std::make_pair(timeKey, tupel));
    m_time_list_mutex.unlock();
}
