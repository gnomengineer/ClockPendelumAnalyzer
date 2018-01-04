#include "../include/DataTupel.h"
#include <regex>

DataTupel::DataTupel(const std::string& name,
        const std::string& date,
        uint32_t absoluteTime) : m_ClockName(name) {
    setDate(date);
    setAbsoluteTime(absoluteTime);
}

DataTupel::DataTupel(const std::string& name,
        const std::string& date,
        const std::string& time) : m_ClockName(name){
    setDate(date);
    setAbsoluteTime(static_cast<uint32_t>(std::stoul(time)));
}

DataTupel::DataTupel(const std::string& name,
                     const std::string& date,
                     uint32_t absoluteTime,
                     uint32_t referenceFrequency)
        : m_ClockName(name) {
    setDate(date);
    setReferenceFrequency(referenceFrequency);
    setAbsoluteTime(absoluteTime);
}

void DataTupel::setClockName(const std::string& name){
    m_ClockName = name;
}

void DataTupel::setDate(const std::string date){
    if(std::regex_match(date,std::regex("[0-9]{8}"))){
        m_Date = date;
    }
}

void DataTupel::setAbsoluteTime(uint32_t absoluteTime){
    if(absoluteTime >= 0){
        m_AbsoluteTime = absoluteTime;
    }
}

void DataTupel::setHeat(int heat){
    if(heat < 100 && heat > 0){
        m_Heat = heat;
    }
}

void DataTupel::setHumidity(int humidity){
    if(humidity > 0 && humidity < 100){
        m_Humidity = humidity;
    }
}

void DataTupel::setReferenceFrequency(uint32_t frequency) {
    m_ReferenceFrequency = frequency;
}
