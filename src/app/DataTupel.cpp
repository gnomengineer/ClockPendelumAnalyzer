#include "../include/DataTupel.h"
#include <regex>

DataTupel::DataTupel(std::string name,
        std::string date,
        int difference)
    : m_ClockName(name), m_Date(date), m_TimeDifference(difference){}

void DataTupel::setClockName(std::string name){
    m_ClockName = name;
}

void DataTupel::setDate(std::string date){
    if(regex_match(date,"[0-9]{14}")){
        m_Date = date;
    }
}

void DataTupel::setTimeDifference(int difference){
    if(regex_match(difference,"[0-9]{1,}")){
        m_TimeDifference = difference;
    }
}

void DataTupel::setHeat(int heat){
    if(regex_match(heat,"[0-9]{1,2}")){
        m_Heat = heat;
    }
}

void DataTupel::setHumidity(int humidity){
    if(regex_match(humidity,"[0-9]{1,2}")){
        m_Humidity = humidity;
    }
}
