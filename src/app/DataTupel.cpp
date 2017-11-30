#include "../include/DataTupel.h"
#include <regex>

DataTupel::DataTupel(std::string name,
        std::string date,
        int absoluteTime) : m_ClockName(name) { 
    setDate(date);
    setAbsoluteTime(absoluteTime);
}

void DataTupel::setClockName(std::string name){
    m_ClockName = name;
}

void DataTupel::setDate(std::string date){
    if(std::regex_match(date,std::regex("[0-9]{8}"))){
        m_Date = date;
    }
}

void DataTupel::setAbsoluteTime(int absoluteTime){
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
